# 1. Cache   
1. 类作用：用作类`BloomFilterPolicy`的自动化测试
2. 所在文件../include/leveldb/cache.h
3. 基类: 无
4. 继承类: ShardedLRUCache
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


# 1. CacheTest   
1. 类作用：用作类`Cache`的自动化测试
2. 所在文件../util/cache_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

定义Deleter
> static void Deleter(const Slice& key, void* v)

> int Lookup(int key) 

>void Insert(int key, int value, int charge = 1) 

>   Cache::Handle* InsertAndReturnHandle(int key, int value, int charge = 1)

> void Erase(int key) 


# 3. Coding  
1. 类作用：对coding.h中的函数进行测试
2. 所在文件../util/coding_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 4. Compaction
1. 类作用：用作类`BloomFilterPolicy`的自动化测试
2. 所在文件../db/version_set.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
/ Return the level that is being compacted.  Inputs from "level"
  // and "level+1" will be merged to produce a set of "level+1" files.
  int level() const { return level_; }

  // Return the object that holds the edits to the descriptor done
  // by this compaction.
  VersionEdit* edit() { return &edit_; }

  // "which" must be either 0 or 1
  int num_input_files(int which) const { return inputs_[which].size(); }

  // Return the ith input file at "level()+which" ("which" must be 0 or 1).
  FileMetaData* input(int which, int i) const { return inputs_[which][i]; }

  // Maximum size of files to build during this compaction.
  uint64_t MaxOutputFileSize() const { return max_output_file_size_; }

  // Is this a trivial compaction that can be implemented by just
  // moving a single input file to the next level (no merging or splitting)
  bool IsTrivialMove() const;

  // Add all inputs to this compaction as delete operations to *edit.
  void AddInputDeletions(VersionEdit* edit);

  // Returns true if the information we have available guarantees that
  // the compaction is producing data in "level+1" for which no data exists
  // in levels greater than "level+1".
  bool IsBaseLevelForKey(const Slice& user_key);

  // Returns true iff we should stop building the current output
  // before processing "internal_key".
  bool ShouldStopBefore(const Slice& internal_key);

  // Release the input version for the compaction, once the compaction
  // is successful.
  void ReleaseInputs();


# 5. Comparator   
1. 类作用：比较器，用来对Slice进行比较
2. 所在文件../include/leveldb/comparator.h
3. 基类: 无
4. 继承类: NewComparator，NewComparator，InternalKeyComparator，ReverseKeyComparator，
BytewiseComparatorImpl，
ReverseKeyComparator
5. 主要函数:

  // 比较a和b的大小
  virtual int Compare(const Slice& a, const Slice& b) const = 0;
//获取比较器的名称
    virtual const char* Name() const = 0;

//延伸功能两个：主要的目标是减少内存的占用
      virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const = 0;

  virtual void FindShortSuccessor(std::string* key) const = 0;

# 1. ConcurrentTest   
1. 类作用： 对Reader和Writer进行并行测试
2. 所在文件../db/skiplist_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 1. CondVar   
1. 类作用： 用于多线程同步
2. 所在文件../port/port_stdcxx.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

void Wait() 
void Signal()
void SignalAll() 

# 8. Constructor   
1. 类作用： 对Table进行测试
2. 所在文件../table/table_test.cc
3. 基类: 无
4. 继承类: BlockConstructor，
TableConstructor，
MemTableConstructor，
DBConstructor
5. 主要函数:
> 添加Key和Value
void Add(const std::string& key, const Slice& value) {
    data_[key] = value.ToString();
  }
//将数据保存到 keys和kvmap
  void Finish(const Options& options,
              std::vector<std::string>* keys,
              KVMap* kvmap)

// 从data中构建数据，子类实现
  virtual Status FinishImpl(const Options& options, const KVMap& data) = 0;

// 获取迭代器
  virtual Iterator* NewIterator() const = 0;

//获取具体的数据
  virtual const KVMap& data() { return data_; }

  virtual DB* db() const { return nullptr; }  // Overridden in DBConstructor


# 1. ConcurrentTest   
1. 类作用： 对Reader和Writer进行并行测试
2. 所在文件../db/skiplist_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 1. CRC   
1. 类作用： 对CRC相关函数进行测试
2. 所在文件:../util/crc32c_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
