# 1. Limiter
1. 类作用：用作资源限制的类，防止过量使用系统资源
2. 所在文件:../util/env_posix.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*对于有限资源，使用前先调用Acquire获取，使用后调用Release释放*
```cpp
bool Acquire()
```

*使用完资源以后，调用Release释放*
```cpp
void Release() 
```

# 2. Logger
1. 类作用： 写日志的接口类
2. 所在文件:../include/leveldb/env.h
3. 基类: 无
4. 继承类: NoOpLogger，PosixLogger
5. 主要函数:

*根据format的格式输出日志*
```cpp
void Logv(const char* format, va_list arguments)
```

# 3. Logging
1. 类作用： 用来测试Log的相关函数的类
2. 所在文件:../util/logging_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 4. LogTest
1. 类作用： 用来测试读写的类
2. 所在文件:../db/log_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 5. LookupKey
1. 类作用： 根据user_key和sequence来解析memtable_key,internal_key和user_key的工具类
2. 所在文件:../db/dbformat.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*获取内存key*
```cpp
Slice memtable_key() const 
```

*获取internal_key*
```cpp  
Slice internal_key() const 
```
*获取用户key*
```cpp
Slice user_key() const 
```

# 6. LRUCache
1. 类作用： 用来测试读写的类
2. 所在文件:../util/cache.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*设置大小*
```cpp
void SetCapacity(size_t capacity) 
```

*插入数据*
```cpp
Cache::Handle* Insert(const Slice& key, uint32_t hash,
                        void* value, size_t charge,
                        void (*deleter)(const Slice& key, void* value));
```

*查找数据*
```cpp
Cache::Handle* Lookup(const Slice& key, uint32_t hash);
```

*释放Handle*
```cpp
void Release(Cache::Handle* handle);
```

*删除数据*
```cpp
void Erase(const Slice& key, uint32_t hash);
```

*压缩内存*
```cpp
void Prune();
```
  
*获取总数*
```cpp
size_t TotalCharge() const 
```


# 7.leveldb_comparator_t
1. 类作用： 用作C语言的接口
2. 所在文件:../db/c.cc
3. 基类: Comparator
4. 继承类: 无
5. 主要函数:
*参考Comparator*