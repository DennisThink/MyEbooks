# 1. MemEnvTest
1. 类作用： 用来MemEnv的类
2. 所在文件:../helpers/memenv/memenv_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 2. MemTable
1. 类作用： 使用跳表来保存key的查找关系的一个类
2. 所在文件:../db/memtable.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*增加引用计数*
```cpp
void Ref()
```

*减少引用计数*
```cpp
void Unref() 
```

*获取内存使用量*
```cpp
size_t ApproximateMemoryUsage();
```

*返回迭代器*
```cpp
Iterator* NewIterator();
```

*增加或者删除key,由ValueType的类型决定*
```cpp
void Add(SequenceNumber seq, ValueType type,
           const Slice& key,
           const Slice& value);
```

*查找key*
```cpp
bool Get(const LookupKey& key, std::string* value, Status* s);
```

# 3. MemTableConstructor
1. 类作用： 用来测试MemTable的类
2. 所在文件:../table/table_test.cc
3. 基类: Constructor
4. 继承类: 无
5. 主要函数:

*根据options和data构造MemTable*
```cpp
virtual Status FinishImpl(const Options& options, const KVMap& data);
```

*返回MemTable的迭代器*
```cpp
virtual Iterator* NewIterator() const 
```


# 4. MemTableInserter
1. 类作用： 用来测试读写的类
2. 所在文件:../db/write_batch.cc
3. 基类: WriteBatch::Handler
4. 继承类: 无
5. 主要函数:
  
*重载基类的Put函数，用于添加key和value*
```cpp
virtual void Put(const Slice& key, const Slice& value) 
```

*重载基类的Delete函数，用于删除数据*
```cpp
virtual void Delete(const Slice& key) 
```

# 5. MemTableIterator
1. 类作用： MemTable的迭代器，继承自Iterator
2. 所在文件:../db/memtable.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:

与Iterator的相同


# 6.MemTableTest
1. 类作用： 用来测试MemTable的类
2. 所在文件:../table/table_test.cc
3. 基类: Constructor
4. 继承类: 无
5. 主要函数:

# 7.MergingIterator
1. 类作用： 迭代器的集合，包含遍历顺序
2. 所在文件:../table/merger.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:

# 8. ModelDB
1. 类作用： DB的一个实现类，数据的保存采用KVMap
2. 所在文件:../db/db_test.cc
3. 基类: DB
4. 继承类: 无
5. 主要函数:

# 9. Mutex
1. 类作用： 互斥锁
2. 所在文件:../port/port_example.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*加锁*
```cpp
void Lock() EXCLUSIVE_LOCK_FUNCTION() 
```

*释放锁*
```cpp
void Unlock() UNLOCK_FUNCTION()

*判定已经加锁*
```cpp
void AssertHeld() ASSERT_EXCLUSIVE_LOCK() { }
```


# 10. MutexLock
1. 类作用： 作用域锁,通过变量的生命周期，来控制锁的范围
2. 所在文件:../util/mutexlock.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 11. ModelIter
1. 类作用： 作用域锁,通过变量的生命周期，来控制锁的范围
2. 所在文件:../db/db_test.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数: