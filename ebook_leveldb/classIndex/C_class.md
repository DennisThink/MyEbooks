# 1. Cache   
1. 类作用：key与value的映射接口
2. 所在文件../include/leveldb/cache.h
3. 基类: 无
4. 继承类: ShardedLRUCache
5. 主要函数:

*将一个Key与Value的映射关系插入到Cache，返回一个与映射一致的句柄*
```cpp 
virtual Handle* Insert(const Slice& key, void* value, size_t charge,
                         void (*deleter)(const Slice& key, void* value));
```

*根据Key，查找对应的Handle*
```cpp
virtual Handle* Lookup(const Slice& key) 
```

*释放LookUp返回的Handle*
```cpp
virtual void Release(Handle* handle) 
```

*返回Handler对应的值*
```cpp
virtual void Erase(const Slice& key) 
```

*如果该Cache中有这个Key，则删除它*
```cpp
virtual void* Value(Handle* handle)
```

# 2. CacheTest   
1. 类作用：用作类`Cache`的自动化测试
2. 所在文件../util/cache_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*定义Deleter*
```cpp
static void Deleter(const Slice& key, void* v)
```

*根据Key查找对应的Value*
```cpp
int Lookup(int key) 
```

*将key和value插入到Cache*
```cpp
void Insert(int key, int value, int charge = 1) 
```

*将Key和Value插入到Cache中，同时返回Handle*
```cpp
Cache::Handle* InsertAndReturnHandle(int key, int value, int charge = 1)
```

*删除这个Key*
```cpp
void Erase(int key) 
```

# 3. Coding  
1. 类作用：对coding.h中的函数进行测试
2. 所在文件../util/coding_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 4. Compaction
1. 类作用：一个封装了Compaction的类
2. 所在文件../db/version_set.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

**
```cpp  
int level() const { return level_; }
```
  
```cpp
VersionEdit* edit() { return &edit_; }
```

```cpp
int num_input_files(int which) const
```

**
```cpp  
FileMetaData* input(int which, int i) const 
```

```cpp
uint64_t MaxOutputFileSize() const 
```

**
```cpp 
bool IsTrivialMove() const;
```

```cpp
void AddInputDeletions(VersionEdit* edit);
```

```cpp 
bool IsBaseLevelForKey(const Slice& user_key);
```

```cpp
bool ShouldStopBefore(const Slice& internal_key);
```

```cpp
void ReleaseInputs();
```

# 5. Comparator   
1. 类作用：比较器，用来对Slice进行比较
2. 所在文件../include/leveldb/comparator.h
3. 基类: 无
4. 继承类: NewComparator，NewComparator，InternalKeyComparator，ReverseKeyComparator，
BytewiseComparatorImpl，
ReverseKeyComparator
5. 主要函数:

*比较a和b的大小*
```cpp
virtual int Compare(const Slice& a, const Slice& b) const = 0;
```

*获取比较器的名称*
```cpp
virtual const char* Name() const = 0;
```

延伸功能两个：主要的目标是减少内存的占用
```cpp
virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const = 0;
```

```cpp
virtual void FindShortSuccessor(std::string* key) const = 0;
```

# 6. ConcurrentTest   
1. 类作用： 对Reader和Writer进行并行测试
2. 所在文件../db/skiplist_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 7. CondVar   
1. 类作用： 用于多线程同步
2. 所在文件../port/port_stdcxx.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

```cpp
void Wait()
```

```cpp
void Signal()
```

```cpp
void SignalAll() 
```

# 8. Constructor   
1. 类作用： 对Table进行测试
2. 所在文件../table/table_test.cc
3. 基类: 无
4. 继承类: BlockConstructor，
TableConstructor，
MemTableConstructor，
DBConstructor
5. 主要函数:

*添加Key和Value*
```cpp
void Add(const std::string& key, const Slice& value)
```

  
*将数据保存到 keys和kvmap*
```cpp
void Finish(const Options& options,
              std::vector<std::string>* keys,
              KVMap* kvmap)
```

*从data中构建数据，子类实现*
```cpp
virtual Status FinishImpl(const Options& options, const KVMap& data) = 0;
```

*获取迭代器*
```cpp
virtual Iterator* NewIterator() const = 0;
```

*获取具体的数据*
```cpp
virtual const KVMap& data();
```

*返回一个DB，在DBConstructor实现*
```cpp
virtual DB* db() const 
```

# 9. ConcurrentTest   
1. 类作用： 对Reader和Writer进行并行测试
2. 所在文件../db/skiplist_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 10. CRC   
1. 类作用： 对CRC相关函数进行测试
2. 所在文件:../util/crc32c_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
