# 1. Random
1. 类作用： 简单的随机数发生器
2. 所在文件:../util/random.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
*获取下一个随机数*
```cpp
uint32_t Next()
```

*返回 [0,n-1] 之间的随机数*
```cpp
uint32_t Uniform(int n)
```

```cpp
bool OneIn(int n) 
uint32_t Skewed(int max_log) 
```

# 2. RandomAccessFile
1. 类作用： 随机读取文件接口
2. 所在文件:../include/leveldb/env.h
3. 基类: 无
4. 继承类: PosixMmapReadableFile,PosixRandomAccessFile,RandomAccessFileImpl,leveldb::SpecialEnv::NewRandomAccessFile::CountingFile,
leveldb::StringSource,

5. 主要函数:

*从文件中读取数据*
```cpp
virtual Status Read(uint64_t offset, size_t n, Slice* result,
                      char* scratch) const = 0
```

# 3. RandomAccessFileImpl
1. 类作用： 实现文件的随机读取
2. 所在文件:../helpers/memenv/memenv.cc
3. 基类: leveldb::RandomAccessFile
4. 继承类: 无
5. 主要函数:

*从文件中读取数据*
```cpp
virtual Status Read(uint64_t offset, size_t n, Slice* result,
                      char* scratch) const
```

# 4. RandomGenerator
1. 类作用： 快速生成随机数据
2. 所在文件: ../doc/bench/db_bench_tree_db.cc
../doc/bench/db_bench_sqlite3.cc
../db/db_bench.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*返回随机字符串*
```cpp
Slice Generate(int len)
```

# 5. Reader
1. 类作用： 日志的读取类，与日志的写入类对应
2. 所在文件:../db/log_reader.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
实际数据保存在scratch中，读取的结果保存在record中
用于读取一条记录
bool ReadRecord(Slice* record, std::string* scratch);

*获取最后一条数据的偏移*
```cpp
uint64_t LastRecordOffset();
```

# 6. RecoveryTest
1. 类作用： 用作恢复测试
2. 所在文件:../db/recovery_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 7. Repairer
1. 类作用： 用作数据库恢复
2. 所在文件:../db/repair.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*运行*
```cpp
Status Run()
```

# 8. ReverseKeyComparator
1. 类作用： 逆序key的比较器
2. 所在文件:../table/table_test.cc
3. 基类: Comparator
4. 继承类: 无
5. 主要函数:


```cpp
virtual int Compare(const Slice& a, const Slice& b) const;

virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const;

virtual void FindShortSuccessor(std::string* key) const; 
```


