# 1. Limiter
1. 类作用：用作资源限制的类，防止过量使用系统资源
2. 所在文件:../util/env_posix.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
//对于有限资源，使用前先调用Acquire获取，使用后调用Release释放
bool Acquire()
//使用完资源以后，调用Release释放
void Release() 

# 1. Logger
1. 类作用： 写日志的接口类
2. 所在文件:../include/leveldb/env.h
3. 基类: 无
4. 继承类: NoOpLogger，PosixLogger
5. 主要函数:
//根据format的格式输出日志
void Logv(const char* format, va_list arguments)

# 1. Logging
1. 类作用： 用来测试Log的相关函数的类
2. 所在文件:../util/logging_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 1. LogTest
1. 类作用： 用来测试读写的类
2. 所在文件:../db/log_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 1. LookupKey
1. 类作用： 根据user_key和sequence来解析memtable_key,internal_key和user_key的工具类
2. 所在文件:../db/dbformat.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
获取内存key
Slice memtable_key() const 

获取internal_key  
Slice internal_key() const 
获取用户key
Slice user_key() const 
  
# 1. LRUCache
1. 类作用： 用来测试读写的类
2. 所在文件:../util/cache.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
设置大小
  void SetCapacity(size_t capacity) 
  插入数据
  Cache::Handle* Insert(const Slice& key, uint32_t hash,
                        void* value, size_t charge,
                        void (*deleter)(const Slice& key, void* value));
  查找数据
  Cache::Handle* Lookup(const Slice& key, uint32_t hash);
  释放Handle
  void Release(Cache::Handle* handle);
  删除数据
  void Erase(const Slice& key, uint32_t hash);
  void Prune();
  获取总数
  size_t TotalCharge() const {
    MutexLock l(&mutex_);
    return usage_;
  }



# 1. LRUCache
1. 类作用： 用来测试读写的类
2. 所在文件:../db/log_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数: