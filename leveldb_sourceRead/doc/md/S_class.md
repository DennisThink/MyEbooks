# SequentialFile
1. 类作用： 序列化读取文件的抽象接口
2. 所在文件: ../include/leveldb/env.h
3. 基类: 无
4. 继承类: StringSource，PosixSequentialFile，SequentialFileImpl
5. 主要函数:
// 最多读取n个字节的数据，放入到scratch中，并且这些数据会包装在result里面
virtual Status Read(size_t n, Slice* result, char* scratch) = 0

跳过一些数据
virtual Status Skip(uint64_t n) = 0;

# SequentialFileImpl
1. 类作用： 序列化读取文件的一个实现类
2. 所在文件:../helpers/memenv/memenv.cc
3. 基类: SequentialFile
4. 继承类: 无
5. 主要函数:
// 最多读取n个字节的数据，放入到scratch中，并且这些数据会包装在result里面
virtual Status Read(size_t n, Slice* result, char* scratch) = 0

跳过一些数据
virtual Status Skip(uint64_t n) = 0;

# ShardedLRUCache
1. 类作用： 共享的LRU缓存
2. 所在文件:../util/cache.cc
3. 基类: Cache
4. 继承类: 无
5. 主要函数:
virtual Handle* Insert(const Slice& key, void* value, size_t charge,
                         void (*deleter)(const Slice& key, void* value))   
  virtual Handle* Lookup(const Slice& key) {
    const uint32_t hash = HashSlice(key);
    return shard_[Shard(hash)].Lookup(key, hash);
  }

 virtual void Release(Handle* handle) 

virtual void Erase(const Slice& key) 

virtual void* Value(Handle* handle)

# SingletonEnv<typename EnvType>
1. 类作用： 单例环境类模板
2. 所在文件:../util/env_posix.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
获取环境类
Env* env() 


# SkipList<typename Key, class Comparator>
1. 类作用： 跳表的模板类
2. 所在文件:../db/skiplist.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
//将key插入到跳表中
void Insert(const Key& key);

判断key是否在跳表中
bool Contains(const Key& key) const;

# SkipTest
1. 类作用： 对跳表进行测试
2. 所在文件:../db/skiplist_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:




# Slice
1. 类作用： 返回字符串的一个视图，类似于c++17中的string_view
2. 所在文件:../include/leveldb/slice.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
返回引用的数据
const char* data() const { return data_; }

返回引用的数据的大小 
size_t size() const { return size_; }

判断Slice是否为空
bool empty() const { return size_ == 0; }

获取第n个字符
char operator[](size_t n) const 

清空Slice中的数据
  void clear() { data_ = ""; size_ = 0; }

移除Slice的前n个字符
  void remove_prefix(size_t n) 
将Slice转为std::string
std::string ToString() const { return std::string(data_, size_); }

与b进行比较,
< 0,this < b
== 0 ,this == b
> 0 this > b
  int compare(const Slice& b) const;

是否以x为起始字符
  bool starts_with(const Slice& x) const


# Snapshot
1. 类作用： 数据库特定状态的抽象句柄
2. 所在文件:../include/leveldb/db.h
3. 基类: 无
4. 继承类: ModelSnapshot，SnapshotImpl 
5. 主要函数:



# SnapshotImpl
1. 类作用： 是一个双向链表
2. 所在文件:../db/snapshot.h
3. 基类: Snapshot
4. 继承类: 无
5. 主要函数:
SequenceNumber sequence_number() 


# SnapshotList
1. 类作用： 以SnapshotImpl为Node的双向链表类
2. 所在文件:../db/snapshot.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
链表是否为空
bool empty() 
返回最老的一个节点
SnapshotImpl* oldest() const 
返回最新的节点
SnapshotImpl* newest() const
新建一个SnapshotImpl节点
SnapshotImpl* New(SequenceNumber sequence_number)
删除一个snapshot节点
void Delete(const SnapshotImpl* snapshot) 

# SpecialEnv
1. 类作用： 用来推迟后台任务的Env
2. 所在文件:../db/db_test.cc
3. 基类: EnvWrapper
4. 继承类: 无
5. 主要函数:

# Stats
1. 类作用： 用作对bench的数据进行统计
2. 所在文件:../db/db_bench.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# Status
1. 类作用： 表示函数调用成功或者失败的返回值
2. 所在文件:../include/leveldb/status.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

//构造固定的Status  
static Status OK() { return Status(); }

//没有找到的Status 
static Status NotFound(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kNotFound, msg, msg2);
  }
  //没有找到的Status
  static Status Corruption(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kCorruption, msg, msg2);
  }
  //不支持的Status
  static Status NotSupported(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kNotSupported, msg, msg2);
  }
    //不支持的Status
  static Status InvalidArgument(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kInvalidArgument, msg, msg2);
  }
    //不支持的Status
  static Status IOError(const Slice& msg, const Slice& msg2 = Slice()) {
    return Status(kIOError, msg, msg2);
  }

   // Returns true iff the status indicates success.
  bool ok() const { return (state_ == nullptr); }

  // Returns true iff the status indicates a NotFound error.
  bool IsNotFound() const { return code() == kNotFound; }

  // Returns true iff the status indicates a Corruption error.
  bool IsCorruption() const { return code() == kCorruption; }

  // Returns true iff the status indicates an IOError.
  bool IsIOError() const { return code() == kIOError; }

  // Returns true iff the status indicates a NotSupportedError.
  bool IsNotSupportedError() const { return code() == kNotSupported; }

  // Returns true iff the status indicates an InvalidArgument.
  bool IsInvalidArgument() const { return code() == kInvalidArgument; }

  // Return a string representation of this status suitable for printing.
  // Returns the string "OK" for success.
  std::string ToString() const;
# StdoutPrinter
1. 类作用： 将数据写到控制台输出
2. 所在文件:../db/leveldbutil.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
virtual Status Append(const Slice& data) 
virtual Status Close() { return Status::OK(); }
virtual Status Flush() { return Status::OK(); }
virtual Status Sync() { return Status::OK(); }




# StringSink
1. 类作用： 将数据写到string中
2. 所在文件:../table/table_test.cc
3. 基类: WriteableFile
4. 继承类: 无
5. 主要函数:
virtual Status Close() { return Status::OK(); }
virtual Status Flush() { return Status::OK(); }
virtual Status Sync() { return Status::OK(); }

virtual Status Append(const Slice& data) 


# StringSource
1. 类作用： RandomAccessFile的String实现
2. 所在文件:../table/table_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
  uint64_t Size() const { return contents_.size(); }

  virtual Status Read(uint64_t offset, size_t n, Slice* result,
                       char* scratch) const 

