# 1. Table
1. 类作用： 是一个string的映射关系，通过返回迭代器被访问
2. 所在文件:../include/leveldb/table.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*打开一个Table*
```cpp
static Status Open(const Options& options,
                     RandomAccessFile* file,
                     uint64_t file_size,
                     Table** table);
```

*返回Table对应的迭代器*
```cpp
Iterator* NewIterator(const ReadOptions&) const;
```

# 2. TableBuilder
1. 类作用： 用于创建Table
2. 所在文件:../include/leveldb/table_builder.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*将Key和Value加入到TableBuilder中*
```cpp
void Add(const Slice& key, const Slice& value);
```

# 3. TableCache
1. 类作用： 
2. 所在文件:../db/table_cache.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*返回迭代器*
```cpp  
Iterator* NewIterator(const ReadOptions& options,
                        uint64_t file_number,
                        uint64_t file_size,
                        Table** tableptr = nullptr);
```

```cpp
Status Get(const ReadOptions& options,
             uint64_t file_number,
             uint64_t file_size,
             const Slice& k,
             void* arg,
             void (*handle_result)(void*, const Slice&, const Slice&));
```



# 4. TableConstructor
1. 类作用： 
2. 所在文件:../table/table_test.cc
3. 基类: Constructor
4. 继承类: 无
5. 主要函数:

```cpp
virtual Status FinishImpl(const Options& options, const KVMap& data)

virtual Iterator* NewIterator() const
```

# 5. TableTest
1. 类作用： 用来对Table进行测试
2. 所在文件:../table/table_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 6. TestEnv
1. 类作用： 测试使用的Env，主要提供了GetChildren函数
2. 所在文件:../db/db_test.cc
3. 基类: EnvWrapper
4. 继承类: 无
5. 主要函数:



# 7. Tester
1. 类作用： leveldb自带的测试框架
2. 所在文件:../util/testharness.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 8.TestHashFilter
1. 类作用： 为每个Key生成一个HashValue，作为过滤器
2. 所在文件:../table/filter_block_test.cc
3. 基类: FilterPolicy
4. 继承类: 无
5. 主要函数:

**
```cpp
virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const; 
virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const
```


# 9.TestState 
1. 类作用： 并行测试使用的一个类
2. 所在文件:../db/skiplist_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 10. TestWritableFile
1. 类作用： 对WritableFile的一个包装，当文件被写或同步的时候，可以通知另一个Env
2. 所在文件:../db/fault_injection_test.cc
3. 基类: WritableFile
4. 继承类: 无
5. 主要函数:

```cpp
virtual Status Append(const Slice& data);
virtual Status Close();
virtual Status Flush();
virtual Status Sync();
```


# 11. TwoLevelIterator
1. 类作用： 两级迭代器
2. 所在文件:../table/two_level_iterator.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:
