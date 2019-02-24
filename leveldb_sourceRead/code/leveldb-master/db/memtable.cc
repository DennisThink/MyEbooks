// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "db/memtable.h"
#include "db/dbformat.h"
#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"
#include "util/coding.h"

namespace leveldb {

/**
 * @brief 从data中解析出Slice
 * @param data 带有前置长度的Slice的内存
 * @return  解析出的Slice
 */
static Slice GetLengthPrefixedSlice(const char* data) {
  uint32_t len;
  const char* p = data;
  p = GetVarint32Ptr(p, p + 5, &len);  // +5: we assume "p" is not corrupted
  return Slice(p, len);
}

MemTable::MemTable(const InternalKeyComparator& cmp)
    : comparator_(cmp),
      refs_(0),
      table_(comparator_, &arena_) {
}

MemTable::~MemTable() {
  assert(refs_ == 0);
}

size_t MemTable::ApproximateMemoryUsage() { return arena_.MemoryUsage(); }

int MemTable::KeyComparator::operator()(const char* aptr, const char* bptr)
    const {
  // Internal keys are encoded as length-prefixed strings.
  Slice a = GetLengthPrefixedSlice(aptr);
  Slice b = GetLengthPrefixedSlice(bptr);
  return comparator.Compare(a, b);
}

// Encode a suitable internal key target for "target" and return it.
// Uses *scratch as scratch space, and the returned pointer will point
// into this scratch space.
/**
 * @brief 将target的长度放到数据之前，作为结果返回
 * @param scratch 保存结果数据
 * @param target 待编码的数据
 * @return 
 */
static const char* EncodeKey(std::string* scratch, const Slice& target) {
  scratch->clear();
  PutVarint32(scratch, target.size());
  scratch->append(target.data(), target.size());
  return scratch->data();
}
/**
 * @class MemTableIterator
 * @author dennis
 * @date 14/11/18
 * @file memtable.cc
 * @brief skiplist的迭代器
 */

class MemTableIterator: public Iterator {
 public:
  explicit MemTableIterator(MemTable::Table* table) : iter_(table) { }

  virtual bool Valid() const { return iter_.Valid(); }
  /**
   * @brief 将Key转换以后再做查找
   * @param k
   */
  virtual void Seek(const Slice& k) { iter_.Seek(EncodeKey(&tmp_, k)); }
  virtual void SeekToFirst() { iter_.SeekToFirst(); }
  virtual void SeekToLast() { iter_.SeekToLast(); }
  virtual void Next() { iter_.Next(); }
  virtual void Prev() { iter_.Prev(); }
  
  /**
   * @brief 返回转换以后的Key
   * @return 
   */
  virtual Slice key() const { return GetLengthPrefixedSlice(iter_.key()); }
  /**
   * @brief 返回转换以后的Value
   * @return 
   */
  virtual Slice value() const {
    Slice key_slice = GetLengthPrefixedSlice(iter_.key());
    return GetLengthPrefixedSlice(key_slice.data() + key_slice.size());
  }

  virtual Status status() const { return Status::OK(); }

 private:
  MemTable::Table::Iterator iter_;
  std::string tmp_;       // For passing to EncodeKey

  // No copying allowed
  MemTableIterator(const MemTableIterator&);
  void operator=(const MemTableIterator&);
};

Iterator* MemTable::NewIterator() {
  return new MemTableIterator(&table_);
}
/**
 * @brief 将key，value以及type添加到MemTable中
 * @param s 序列号
 * @param type 数值类型
 * @param key 
 * @param value
 */

void MemTable::Add(SequenceNumber s, ValueType type,
                   const Slice& key,
                   const Slice& value) {
  // Format of an entry is concatenation of:
  //  key_size     : varint32 of internal_key.size()
  //  key bytes    : char[internal_key.size()]
  //  value_size   : varint32 of value.size()
  //  value bytes  : char[value.size()]
  size_t key_size = key.size();
  size_t val_size = value.size();
  size_t internal_key_size = key_size + 8;
  //计算总大小
  const size_t encoded_len =
      VarintLength(internal_key_size) + internal_key_size +
      VarintLength(val_size) + val_size;
  
  //分配内存
  char* buf = arena_.Allocate(encoded_len);
  
  // 保存key_size
  char* p = EncodeVarint32(buf, internal_key_size);
  // 保存key_value
  memcpy(p, key.data(), key_size);
  
  //移动指针
  p += key_size;
  //保存sequenceNumber(左移8bit)和Type
  EncodeFixed64(p, (s << 8) | type);
  
  //保存value的长度
  p += 8;
  p = EncodeVarint32(p, val_size);
  
  //保存value的值
  memcpy(p, value.data(), val_size);
  assert(p + val_size == buf + encoded_len);
  //将这段内存保存到table
  table_.Insert(buf);
}

/**
 * @brief 从MemTable中查找key对应的value
 * @param key 被查找的key
 * @param value 生成的value
 * @param s 查找结果
 * @return 是否找到了
 */

bool MemTable::Get(const LookupKey& key, std::string* value, Status* s) {
  Slice memkey = key.memtable_key();
  Table::Iterator iter(&table_);
  //模糊查找
  iter.Seek(memkey.data());
  
  //找到了精确判断
  if (iter.Valid()) {
    // entry format is:
    //    klength  varint32
    //    userkey  char[klength]
    //    tag      uint64
    //    vlength  varint32
    //    value    char[vlength]
    // Check that it belongs to same user key.  We do not check the
    // sequence number since the Seek() call above should have skipped
    // all entries with overly large sequence numbers.
    const char* entry = iter.key();
    uint32_t key_length;
    const char* key_ptr = GetVarint32Ptr(entry, entry+5, &key_length);
    if (comparator_.comparator.user_comparator()->Compare(
            Slice(key_ptr, key_length - 8),
            key.user_key()) == 0) {
      // Correct user key
      const uint64_t tag = DecodeFixed64(key_ptr + key_length - 8);
      switch (static_cast<ValueType>(tag & 0xff)) {
        //值类型，说明数据存在 
		case kTypeValue: {
          Slice v = GetLengthPrefixedSlice(key_ptr + key_length);
          value->assign(v.data(), v.size());
          return true;
        }
		//被删除的类型，说米数据不存在
        case kTypeDeletion:
          *s = Status::NotFound(Slice());
          return true;
      }
    }
  }
  return false;
}

}  // namespace leveldb
