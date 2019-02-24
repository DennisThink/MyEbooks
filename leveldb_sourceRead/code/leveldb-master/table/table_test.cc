// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "leveldb/table.h"

#include <map>
#include <string>
#include "db/dbformat.h"
#include "db/memtable.h"
#include "db/write_batch_internal.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "leveldb/table_builder.h"
#include "table/block.h"
#include "table/block_builder.h"
#include "table/format.h"
#include "util/random.h"
#include "util/testharness.h"
#include "util/testutil.h"

namespace leveldb {

// Return reverse of "key".
// Used to test non-lexicographic comparators.

/**
 * @brief 返回Key的逆序，在测试non-lexicographic比较器的时候使用
 * @param key 待逆序的key
 * @return  逆序后的key
 */
static std::string Reverse(const Slice& key) {
  std::string str(key.ToString());
  std::string rev("");
  for (std::string::reverse_iterator rit = str.rbegin();
       rit != str.rend(); ++rit) {
    rev.push_back(*rit);
  }
  return rev;
}

namespace {
	
/**
 * @class ReverseKeyComparator
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 逆序的Key比较器
 */

class ReverseKeyComparator : public Comparator {
public:
 
 
  /**
   * @brief 获取比较器的文件名
   * @return 比较器文件名
   */
  virtual const char* Name() const {
    return "leveldb.ReverseBytewiseComparator";
  }


  /**
   * @brief 比较两个Slice
   * @param a 
   * @param b
   * @return a > b ; 结果> 0  a==b 结果为0 a < b 结果小于0
   */
  virtual int Compare(const Slice& a, const Slice& b) const {
    return BytewiseComparator()->Compare(Reverse(a), Reverse(b));
  }

  /**
   * @brief 找到start和limit，最短分割器
   * @param start 传入传出参数
   * @param limit 
   */
  virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const {
    std::string s = Reverse(*start);
    std::string l = Reverse(limit);
    BytewiseComparator()->FindShortestSeparator(&s, l);
    *start = Reverse(s);
  }

  
  /**
   * @brief 获取最短的后继者
   * @param key
   */
  virtual void FindShortSuccessor(std::string* key) const {
    std::string s = Reverse(*key);
    BytewiseComparator()->FindShortSuccessor(&s);
    *key = Reverse(s);
  }
};
}  // namespace
static ReverseKeyComparator reverse_key_comparator;


/**
 * @brief 根据比较器的类型，在key之后添加“\0"
 * @param cmp 比较器类型
 * @param key 待修改的key
 */
static void Increment(const Comparator* cmp, std::string* key) {
  if (cmp == BytewiseComparator()) {
    key->push_back('\0');
  } else {
    assert(cmp == &reverse_key_comparator);
    std::string rev = Reverse(*key);
    rev.push_back('\0');
    *key = Reverse(rev);
  }
}

// An STL comparator that uses a Comparator
namespace {
/**
 * @class STLLessThan
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 使用Comparator生成的stlComparator
 */

struct STLLessThan {
  const Comparator* cmp;

  STLLessThan() : cmp(BytewiseComparator()) { }
  STLLessThan(const Comparator* c) : cmp(c) { }
  
  /**
   * @brief 重载（）操作符，来实现字符串的比较
   * @param a 待比较的字符串1
   * @param b 待比较的字符串2
   * @return a和b的比较结果
   */
  bool operator()(const std::string& a, const std::string& b) const {
    return cmp->Compare(Slice(a), Slice(b)) < 0;
  }
};
}  // namespace

/**
 * @class StringSink
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 继承WritableFile,主要将内容放入字符串
 */

class StringSink: public WritableFile {
 public:
  ~StringSink() { }

  const std::string& contents() const { return contents_; }

  virtual Status Close() { return Status::OK(); }
  virtual Status Flush() { return Status::OK(); }
  virtual Status Sync() { return Status::OK(); }

  
  /**
   * @brief 重载Append，将内容放入contents_
   * @param data,待添加的内容
   * @return 返回添加的Status
   */
  virtual Status Append(const Slice& data) {
    contents_.append(data.data(), data.size());
    return Status::OK();
  }

 private:
  std::string contents_;
};

/**
 * @class StringSource
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 继承自RandomAccessFile，实际的内容保存在字符串中
 */

class StringSource: public RandomAccessFile {
 public:
  StringSource(const Slice& contents)
      : contents_(contents.data(), contents.size()) {
  }

  virtual ~StringSource() { }

  uint64_t Size() const { return contents_.size(); }

  /**
   * @brief 重载RandomAccessFile的Read函数，将[offset，offset+n]的内容保存到result中，内存由scratch保持
   * @param offset 读取的起始位置
   * @param n 读取的长度
   * @param result 读取的结果
   * @param scratch 传入的内存
   * @return 读取的结果
   */
  virtual Status Read(uint64_t offset, size_t n, Slice* result,
                       char* scratch) const {
    if (offset > contents_.size()) {
      return Status::InvalidArgument("invalid Read offset");
    }
    if (offset + n > contents_.size()) {
      n = contents_.size() - offset;
    }
    memcpy(scratch, &contents_[offset], n);
    *result = Slice(scratch, n);
    return Status::OK();
  }

 private:
  std::string contents_;
};

typedef std::map<std::string, std::string, STLLessThan> KVMap;

// Helper class for tests to unify the interface between
// BlockBuilder/TableBuilder and Block/Table.
/**
 * @class Constructor
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 为测试而写的帮助类，为了统一BlockBuilder和Block 以及TableBuilder以及Table接口
 */

class Constructor {
 public:
  explicit Constructor(const Comparator* cmp) : data_(STLLessThan(cmp)) { }
  virtual ~Constructor() { }

  /**
   * @brief 将key和对应的value添加到data中
   * @param key 
   * @param value
   */
  
  void Add(const std::string& key, const Slice& value) {
    data_[key] = value.ToString();
  }

  // Finish constructing the data structure with all the keys that have
  // been added so far.  Returns the keys in sorted order in "*keys"
  // and stores the key/value pairs in "*kvmap"
  /**
   * @brief 根据options将Constructor中的key保存到keys，key和value保存到kvmap
   * @param options 选项
   * @param keys 所有key的vector
   * @param kvmap 所有key和value的集合
   */
  
  void Finish(const Options& options,
              std::vector<std::string>* keys,
              KVMap* kvmap) {
    *kvmap = data_;
    keys->clear();
    for (KVMap::const_iterator it = data_.begin();
         it != data_.end();
         ++it) {
      keys->push_back(it->first);
    }
    data_.clear();
    Status s = FinishImpl(options, *kvmap);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  // Construct the data structure from the data in "data"
  /**
   * @brief 根据选项，将data中的数据保存到子类
   * @param options 选项
   * @param data 从super class 传下来的数据
   */
  
  virtual Status FinishImpl(const Options& options, const KVMap& data) = 0;

  /**
   * @brief 返回迭代器
   */
  
  virtual Iterator* NewIterator() const = 0;

  /**
   * @brief 返回保存的数据
   * @return 
   */
  
  virtual const KVMap& data() { return data_; }

  
  
  virtual DB* db() const { return nullptr; }  // Overridden in DBConstructor

 private:
  KVMap data_;
};

/**
 * @class BlockConstructor
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 完成BlockBuilder与Block之间的接口
 */

class BlockConstructor: public Constructor {
 public:
  explicit BlockConstructor(const Comparator* cmp)
      : Constructor(cmp),
        comparator_(cmp),
        block_(nullptr) { }
  ~BlockConstructor() {
    delete block_;
  }
  /**
   * @brief 根据options和data完成Block的构建
   * @param options 构建选项
   * @param data 需要被加入的数据
   * @return 返回构建的结果
   */
  
  virtual Status FinishImpl(const Options& options, const KVMap& data) {
    delete block_;
    block_ = nullptr;
    BlockBuilder builder(&options);

    for (KVMap::const_iterator it = data.begin();
         it != data.end();
         ++it) {
      builder.Add(it->first, it->second);
    }
    // Open the block
    data_ = builder.Finish().ToString();
    BlockContents contents;
    contents.data = data_;
    contents.cachable = false;
    contents.heap_allocated = false;
    block_ = new Block(contents);
    return Status::OK();
  }
  /**
   * @brief 返回Block对应的迭代器
   * @return BlockIter
   */
  
  virtual Iterator* NewIterator() const {
    return block_->NewIterator(comparator_);
  }

 private:
  const Comparator* comparator_;
  std::string data_;
  Block* block_;

  BlockConstructor();
};

/**
 * @class TableConstructor
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 完成Table和TableBuilder的接口
 */

class TableConstructor: public Constructor {
 public:
  TableConstructor(const Comparator* cmp)
      : Constructor(cmp),
        source_(nullptr), table_(nullptr) {
  }
  ~TableConstructor() {
    Reset();
  }
  
  
  /**
   * @brief 根据options和data完成table的构建
   * @param options Option的选项
   * @param data 用于构造table的数据
   * @return 构造的结果
   */
  virtual Status FinishImpl(const Options& options, const KVMap& data) {
    Reset();
    StringSink sink;
    TableBuilder builder(options, &sink);

    for (KVMap::const_iterator it = data.begin();
         it != data.end();
         ++it) {
      builder.Add(it->first, it->second);
      ASSERT_TRUE(builder.status().ok());
    }
    Status s = builder.Finish();
    ASSERT_TRUE(s.ok()) << s.ToString();

    ASSERT_EQ(sink.contents().size(), builder.FileSize());

    // Open the table
    source_ = new StringSource(sink.contents());
    Options table_options;
    table_options.comparator = options.comparator;
    return Table::Open(table_options, source_, sink.contents().size(), &table_);
  }

  virtual Iterator* NewIterator() const {
    return table_->NewIterator(ReadOptions());
  }

  uint64_t ApproximateOffsetOf(const Slice& key) const {
    return table_->ApproximateOffsetOf(key);
  }

 private:
  void Reset() {
    delete table_;
    delete source_;
    table_ = nullptr;
    source_ = nullptr;
  }

  StringSource* source_;
  Table* table_;

  TableConstructor();
};

// A helper class that converts internal format keys into user keys
/**
 * @class KeyConvertingIterator
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 一个将InternalKey转为UserKey的迭代器
 */

class KeyConvertingIterator: public Iterator {
 public:
  explicit KeyConvertingIterator(Iterator* iter) : iter_(iter) { }
  virtual ~KeyConvertingIterator() { delete iter_; }
  virtual bool Valid() const { return iter_->Valid(); }
  
  /**
   * @brief 在查找的时候，先将UserKey转为InternalKey，再查找
   * @param target 待查找的Userkey
   */
  
  virtual void Seek(const Slice& target) {
    ParsedInternalKey ikey(target, kMaxSequenceNumber, kTypeValue);
    std::string encoded;
    AppendInternalKey(&encoded, ikey);
    iter_->Seek(encoded);
  }
  virtual void SeekToFirst() { iter_->SeekToFirst(); }
  virtual void SeekToLast() { iter_->SeekToLast(); }
  virtual void Next() { iter_->Next(); }
  virtual void Prev() { iter_->Prev(); }

  /**
   * @brief 将InternalKey转为UserKey返回
   * @return UserKey
   */
  
  virtual Slice key() const {
    assert(Valid());
    ParsedInternalKey key;
    if (!ParseInternalKey(iter_->key(), &key)) {
      status_ = Status::Corruption("malformed internal key");
      return Slice("corrupted key");
    }
    return key.user_key;
  }

  virtual Slice value() const { return iter_->value(); }
  virtual Status status() const {
    return status_.ok() ? iter_->status() : status_;
  }

 private:
  mutable Status status_;
  Iterator* iter_;

  // No copying allowed
  KeyConvertingIterator(const KeyConvertingIterator&);
  void operator=(const KeyConvertingIterator&);
};

/**
 * @class MemTableConstructor
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 数据和Memtable之间的接口
 */

class MemTableConstructor: public Constructor {
 public:
  explicit MemTableConstructor(const Comparator* cmp)
      : Constructor(cmp),
        internal_comparator_(cmp) {
    memtable_ = new MemTable(internal_comparator_);
    memtable_->Ref();
  }
  ~MemTableConstructor() {
    memtable_->Unref();
  }
  
  /**
   * @brief 根据选项和数据构造MemTable
   * @param options 选项
   * @param data 数据
   * @return 构造结果
   */
  virtual Status FinishImpl(const Options& options, const KVMap& data) {
    memtable_->Unref();
    memtable_ = new MemTable(internal_comparator_);
    memtable_->Ref();
    int seq = 1;
    for (KVMap::const_iterator it = data.begin();
         it != data.end();
         ++it) {
      memtable_->Add(seq, kTypeValue, it->first, it->second);
      seq++;
    }
    return Status::OK();
  }
  
  virtual Iterator* NewIterator() const {
    return new KeyConvertingIterator(memtable_->NewIterator());
  }

 private:
  InternalKeyComparator internal_comparator_;
  MemTable* memtable_;
};
/**
 * @class DBConstructor
 * @author dennis
 * @date 24/11/18
 * @file table_test.cc
 * @brief 数据和DB之间的接口
 */

class DBConstructor: public Constructor {
 public:
  explicit DBConstructor(const Comparator* cmp)
      : Constructor(cmp),
        comparator_(cmp) {
    db_ = nullptr;
    NewDB();
  }
  ~DBConstructor() {
    delete db_;
  }
  /**
   * @brief 根据选项和数据生成DB
   * @param options
   * @param data
   * @return 
   */
  
  virtual Status FinishImpl(const Options& options, const KVMap& data) {
    delete db_;
    db_ = nullptr;
    NewDB();
    for (KVMap::const_iterator it = data.begin();
         it != data.end();
         ++it) {
      WriteBatch batch;
      batch.Put(it->first, it->second);
      ASSERT_TRUE(db_->Write(WriteOptions(), &batch).ok());
    }
    return Status::OK();
  }
  
  virtual Iterator* NewIterator() const {
    return db_->NewIterator(ReadOptions());
  }

  virtual DB* db() const { return db_; }

 private:
  void NewDB() {
    std::string name = test::TmpDir() + "/table_testdb";

    Options options;
    options.comparator = comparator_;
    Status status = DestroyDB(name, options);
    ASSERT_TRUE(status.ok()) << status.ToString();

    options.create_if_missing = true;
    options.error_if_exists = true;
    options.write_buffer_size = 10000;  // Something small to force merging
    status = DB::Open(options, name, &db_);
    ASSERT_TRUE(status.ok()) << status.ToString();
  }

  const Comparator* comparator_;
  DB* db_;
};

enum TestType {
  TABLE_TEST,
  BLOCK_TEST,
  MEMTABLE_TEST,
  DB_TEST
};

struct TestArgs {
  TestType type;
  bool reverse_compare;
  int restart_interval;
};

// 构造测试选项
static const TestArgs kTestArgList[] = {
  { TABLE_TEST, false, 16 },
  { TABLE_TEST, false, 1 },
  { TABLE_TEST, false, 1024 },
  { TABLE_TEST, true, 16 },
  { TABLE_TEST, true, 1 },
  { TABLE_TEST, true, 1024 },

  { BLOCK_TEST, false, 16 },
  { BLOCK_TEST, false, 1 },
  { BLOCK_TEST, false, 1024 },
  { BLOCK_TEST, true, 16 },
  { BLOCK_TEST, true, 1 },
  { BLOCK_TEST, true, 1024 },

  // Restart interval does not matter for memtables
  { MEMTABLE_TEST, false, 16 },
  { MEMTABLE_TEST, true, 16 },

  // Do not bother with restart interval variations for DB
  { DB_TEST, false, 16 },
  { DB_TEST, true, 16 },
};
static const int kNumTestArgs = sizeof(kTestArgList) / sizeof(kTestArgList[0]);

class Harness {
 public:
  Harness() : constructor_(nullptr) { }

  void Init(const TestArgs& args) {
    delete constructor_;
    constructor_ = nullptr;
    options_ = Options();

    options_.block_restart_interval = args.restart_interval;
    // Use shorter block size for tests to exercise block boundary
    // conditions more.
    options_.block_size = 256;
    if (args.reverse_compare) {
      options_.comparator = &reverse_key_comparator;
    }
    switch (args.type) {
      case TABLE_TEST:
        constructor_ = new TableConstructor(options_.comparator);
        break;
      case BLOCK_TEST:
        constructor_ = new BlockConstructor(options_.comparator);
        break;
      case MEMTABLE_TEST:
        constructor_ = new MemTableConstructor(options_.comparator);
        break;
      case DB_TEST:
        constructor_ = new DBConstructor(options_.comparator);
        break;
    }
  }

  ~Harness() {
    delete constructor_;
  }

  void Add(const std::string& key, const std::string& value) {
    constructor_->Add(key, value);
  }

  void Test(Random* rnd) {
    std::vector<std::string> keys;
    KVMap data;
    constructor_->Finish(options_, &keys, &data);

    TestForwardScan(keys, data);
    TestBackwardScan(keys, data);
    TestRandomAccess(rnd, keys, data);
  }

  void TestForwardScan(const std::vector<std::string>& keys,
                       const KVMap& data) {
    Iterator* iter = constructor_->NewIterator();
    ASSERT_TRUE(!iter->Valid());
    iter->SeekToFirst();
    for (KVMap::const_iterator model_iter = data.begin();
         model_iter != data.end();
         ++model_iter) {
      ASSERT_EQ(ToString(data, model_iter), ToString(iter));
      iter->Next();
    }
    ASSERT_TRUE(!iter->Valid());
    delete iter;
  }

  void TestBackwardScan(const std::vector<std::string>& keys,
                        const KVMap& data) {
    Iterator* iter = constructor_->NewIterator();
    ASSERT_TRUE(!iter->Valid());
    iter->SeekToLast();
    for (KVMap::const_reverse_iterator model_iter = data.rbegin();
         model_iter != data.rend();
         ++model_iter) {
      ASSERT_EQ(ToString(data, model_iter), ToString(iter));
      iter->Prev();
    }
    ASSERT_TRUE(!iter->Valid());
    delete iter;
  }

  void TestRandomAccess(Random* rnd,
                        const std::vector<std::string>& keys,
                        const KVMap& data) {
    static const bool kVerbose = false;
    Iterator* iter = constructor_->NewIterator();
    ASSERT_TRUE(!iter->Valid());
    KVMap::const_iterator model_iter = data.begin();
    if (kVerbose) fprintf(stderr, "---\n");
    for (int i = 0; i < 200; i++) {
      const int toss = rnd->Uniform(5);
      switch (toss) {
        case 0: {
          if (iter->Valid()) {
            if (kVerbose) fprintf(stderr, "Next\n");
            iter->Next();
            ++model_iter;
            ASSERT_EQ(ToString(data, model_iter), ToString(iter));
          }
          break;
        }

        case 1: {
          if (kVerbose) fprintf(stderr, "SeekToFirst\n");
          iter->SeekToFirst();
          model_iter = data.begin();
          ASSERT_EQ(ToString(data, model_iter), ToString(iter));
          break;
        }

        case 2: {
          std::string key = PickRandomKey(rnd, keys);
          model_iter = data.lower_bound(key);
          if (kVerbose) fprintf(stderr, "Seek '%s'\n",
                                EscapeString(key).c_str());
          iter->Seek(Slice(key));
          ASSERT_EQ(ToString(data, model_iter), ToString(iter));
          break;
        }

        case 3: {
          if (iter->Valid()) {
            if (kVerbose) fprintf(stderr, "Prev\n");
            iter->Prev();
            if (model_iter == data.begin()) {
              model_iter = data.end();   // Wrap around to invalid value
            } else {
              --model_iter;
            }
            ASSERT_EQ(ToString(data, model_iter), ToString(iter));
          }
          break;
        }

        case 4: {
          if (kVerbose) fprintf(stderr, "SeekToLast\n");
          iter->SeekToLast();
          if (keys.empty()) {
            model_iter = data.end();
          } else {
            std::string last = data.rbegin()->first;
            model_iter = data.lower_bound(last);
          }
          ASSERT_EQ(ToString(data, model_iter), ToString(iter));
          break;
        }
      }
    }
    delete iter;
  }

  std::string ToString(const KVMap& data, const KVMap::const_iterator& it) {
    if (it == data.end()) {
      return "END";
    } else {
      return "'" + it->first + "->" + it->second + "'";
    }
  }

  std::string ToString(const KVMap& data,
                       const KVMap::const_reverse_iterator& it) {
    if (it == data.rend()) {
      return "END";
    } else {
      return "'" + it->first + "->" + it->second + "'";
    }
  }

  std::string ToString(const Iterator* it) {
    if (!it->Valid()) {
      return "END";
    } else {
      return "'" + it->key().ToString() + "->" + it->value().ToString() + "'";
    }
  }

  std::string PickRandomKey(Random* rnd, const std::vector<std::string>& keys) {
    if (keys.empty()) {
      return "foo";
    } else {
      const int index = rnd->Uniform(keys.size());
      std::string result = keys[index];
      switch (rnd->Uniform(3)) {
        case 0:
          // Return an existing key
          break;
        case 1: {
          // Attempt to return something smaller than an existing key
          if (result.size() > 0 && result[result.size()-1] > '\0') {
            result[result.size()-1]--;
          }
          break;
        }
        case 2: {
          // Return something larger than an existing key
          Increment(options_.comparator, &result);
          break;
        }
      }
      return result;
    }
  }

  // Returns nullptr if not running against a DB
  DB* db() const { return constructor_->db(); }

 private:
  Options options_;
  Constructor* constructor_;
};

// Test empty table/block.
TEST(Harness, Empty) {
  for (int i = 0; i < kNumTestArgs; i++) {
    Init(kTestArgList[i]);
    Random rnd(test::RandomSeed() + 1);
    Test(&rnd);
  }
}

// Special test for a block with no restart entries.  The C++ leveldb
// code never generates such blocks, but the Java version of leveldb
// seems to.
TEST(Harness, ZeroRestartPointsInBlock) {
  char data[sizeof(uint32_t)];
  memset(data, 0, sizeof(data));
  BlockContents contents;
  contents.data = Slice(data, sizeof(data));
  contents.cachable = false;
  contents.heap_allocated = false;
  Block block(contents);
  Iterator* iter = block.NewIterator(BytewiseComparator());
  iter->SeekToFirst();
  ASSERT_TRUE(!iter->Valid());
  iter->SeekToLast();
  ASSERT_TRUE(!iter->Valid());
  iter->Seek("foo");
  ASSERT_TRUE(!iter->Valid());
  delete iter;
}

// Test the empty key
TEST(Harness, SimpleEmptyKey) {
  for (int i = 0; i < kNumTestArgs; i++) {
    Init(kTestArgList[i]);
    Random rnd(test::RandomSeed() + 1);
    Add("", "v");
    Test(&rnd);
  }
}

TEST(Harness, SimpleSingle) {
  for (int i = 0; i < kNumTestArgs; i++) {
    Init(kTestArgList[i]);
    Random rnd(test::RandomSeed() + 2);
    Add("abc", "v");
    Test(&rnd);
  }
}

TEST(Harness, SimpleMulti) {
  for (int i = 0; i < kNumTestArgs; i++) {
    Init(kTestArgList[i]);
    Random rnd(test::RandomSeed() + 3);
    Add("abc", "v");
    Add("abcd", "v");
    Add("ac", "v2");
    Test(&rnd);
  }
}

TEST(Harness, SimpleSpecialKey) {
  for (int i = 0; i < kNumTestArgs; i++) {
    Init(kTestArgList[i]);
    Random rnd(test::RandomSeed() + 4);
    Add("\xff\xff", "v3");
    Test(&rnd);
  }
}

TEST(Harness, Randomized) {
  for (int i = 0; i < kNumTestArgs; i++) {
    Init(kTestArgList[i]);
    Random rnd(test::RandomSeed() + 5);
    for (int num_entries = 0; num_entries < 2000;
         num_entries += (num_entries < 50 ? 1 : 200)) {
      if ((num_entries % 10) == 0) {
        fprintf(stderr, "case %d of %d: num_entries = %d\n",
                (i + 1), int(kNumTestArgs), num_entries);
      }
      for (int e = 0; e < num_entries; e++) {
        std::string v;
        Add(test::RandomKey(&rnd, rnd.Skewed(4)),
            test::RandomString(&rnd, rnd.Skewed(5), &v).ToString());
      }
      Test(&rnd);
    }
  }
}

TEST(Harness, RandomizedLongDB) {
  Random rnd(test::RandomSeed());
  TestArgs args = { DB_TEST, false, 16 };
  Init(args);
  int num_entries = 100000;
  for (int e = 0; e < num_entries; e++) {
    std::string v;
    Add(test::RandomKey(&rnd, rnd.Skewed(4)),
        test::RandomString(&rnd, rnd.Skewed(5), &v).ToString());
  }
  Test(&rnd);

  // We must have created enough data to force merging
  int files = 0;
  for (int level = 0; level < config::kNumLevels; level++) {
    std::string value;
    char name[100];
    snprintf(name, sizeof(name), "leveldb.num-files-at-level%d", level);
    ASSERT_TRUE(db()->GetProperty(name, &value));
    files += atoi(value.c_str());
  }
  ASSERT_GT(files, 0);
}

class MemTableTest { };

TEST(MemTableTest, Simple) {
  InternalKeyComparator cmp(BytewiseComparator());
  MemTable* memtable = new MemTable(cmp);
  memtable->Ref();
  WriteBatch batch;
  WriteBatchInternal::SetSequence(&batch, 100);
  batch.Put(std::string("k1"), std::string("v1"));
  batch.Put(std::string("k2"), std::string("v2"));
  batch.Put(std::string("k3"), std::string("v3"));
  batch.Put(std::string("largekey"), std::string("vlarge"));
  ASSERT_TRUE(WriteBatchInternal::InsertInto(&batch, memtable).ok());

  Iterator* iter = memtable->NewIterator();
  iter->SeekToFirst();
  while (iter->Valid()) {
    fprintf(stderr, "key: '%s' -> '%s'\n",
            iter->key().ToString().c_str(),
            iter->value().ToString().c_str());
    iter->Next();
  }

  delete iter;
  memtable->Unref();
}

static bool Between(uint64_t val, uint64_t low, uint64_t high) {
  bool result = (val >= low) && (val <= high);
  if (!result) {
    fprintf(stderr, "Value %llu is not in range [%llu, %llu]\n",
            (unsigned long long)(val),
            (unsigned long long)(low),
            (unsigned long long)(high));
  }
  return result;
}

class TableTest { };

TEST(TableTest, ApproximateOffsetOfPlain) {
  TableConstructor c(BytewiseComparator());
  c.Add("k01", "hello");
  c.Add("k02", "hello2");
  c.Add("k03", std::string(10000, 'x'));
  c.Add("k04", std::string(200000, 'x'));
  c.Add("k05", std::string(300000, 'x'));
  c.Add("k06", "hello3");
  c.Add("k07", std::string(100000, 'x'));
  std::vector<std::string> keys;
  KVMap kvmap;
  Options options;
  options.block_size = 1024;
  options.compression = kNoCompression;
  c.Finish(options, &keys, &kvmap);

  ASSERT_TRUE(Between(c.ApproximateOffsetOf("abc"),       0,      0));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k01"),       0,      0));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k01a"),      0,      0));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k02"),       0,      0));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k03"),       0,      0));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k04"),   10000,  11000));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k04a"), 210000, 211000));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k05"),  210000, 211000));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k06"),  510000, 511000));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k07"),  510000, 511000));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("xyz"),  610000, 612000));

}

static bool SnappyCompressionSupported() {
  std::string out;
  Slice in = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  return port::Snappy_Compress(in.data(), in.size(), &out);
}

TEST(TableTest, ApproximateOffsetOfCompressed) {
  if (!SnappyCompressionSupported()) {
    fprintf(stderr, "skipping compression tests\n");
    return;
  }

  Random rnd(301);
  TableConstructor c(BytewiseComparator());
  std::string tmp;
  c.Add("k01", "hello");
  c.Add("k02", test::CompressibleString(&rnd, 0.25, 10000, &tmp));
  c.Add("k03", "hello3");
  c.Add("k04", test::CompressibleString(&rnd, 0.25, 10000, &tmp));
  std::vector<std::string> keys;
  KVMap kvmap;
  Options options;
  options.block_size = 1024;
  options.compression = kSnappyCompression;
  c.Finish(options, &keys, &kvmap);

  // Expected upper and lower bounds of space used by compressible strings.
  static const int kSlop = 1000;  // Compressor effectiveness varies.
  const int expected = 2500;  // 10000 * compression ratio (0.25)
  const int min_z = expected - kSlop;
  const int max_z = expected + kSlop;

  ASSERT_TRUE(Between(c.ApproximateOffsetOf("abc"), 0, kSlop));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k01"), 0, kSlop));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k02"), 0, kSlop));
  // Have now emitted a large compressible string, so adjust expected offset.
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k03"), min_z, max_z));
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("k04"), min_z, max_z));
  // Have now emitted two large compressible strings, so adjust expected offset.
  ASSERT_TRUE(Between(c.ApproximateOffsetOf("xyz"), 2 * min_z, 2 * max_z));
}

}  // namespace leveldb

int main(int argc, char** argv) {
  return leveldb::test::RunAllTests();
}
