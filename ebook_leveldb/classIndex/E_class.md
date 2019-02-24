# 1. EmptyIterator   
1. 类作用： 一个空的迭代器
2. 所在文件:../table/iterator.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:

```cpp
bool Valid() const override { return false; }
void Seek(const Slice& target) override { }
void SeekToFirst() override { }
void SeekToLast() override { }
void Next() override { assert(false); }
void Prev() override { assert(false); }
Slice key() const override { assert(false); return Slice(); }
Slice value() const override { assert(false); return Slice(); }
Status status() const override { return status_; }
```

# 2. Env   
1. 类作用： 对操作系统的相关功能进行封装，提供一个统一的接口
2. 所在文件:../include/leveldb/env.h
3. 基类: 无
4. 继承类: PosixDefaultEnv,
5. 主要函数:

*获取默认的Env*
```cpp
static Env* Default();
```

*根据特定的名称创建一个序列化的读取文件类*
```cpp
virtual Status NewSequentialFile(const std::string& fname,
                                   SequentialFile** result) = 0;
```
*创建随机读文件*
```cpp
virtual Status NewRandomAccessFile(const std::string& fname,
                                     RandomAccessFile** result) = 0;
```

*创建可写文件*
```cpp
virtual Status NewWritableFile(const std::string& fname,
                                 WritableFile** result) = 0;
```

*创建可追加文件*
```cpp
virtual Status NewAppendableFile(const std::string& fname,
                                   WritableFile** result);
```
*获取当前目录的子目录和文件*
```cpp
virtual Status GetChildren(const std::string& dir,
                             std::vector<std::string>* result) = 0;
```
*删除文件*
```cpp
virtual Status DeleteFile(const std::string& fname) = 0;
```

*创建目录*
```cpp
virtual Status CreateDir(const std::string& dirname) = 0;
```

*删除目录*
```cpp
virtual Status DeleteDir(const std::string& dirname) = 0;
```
  
*获取文件大小*
```cpp  
virtual Status GetFileSize(const std::string& fname, uint64_t* file_size) = 0;
```
  
*重命名文件*
```cpp
virtual Status RenameFile(const std::string& src,
                            const std::string& target) = 0;
```

*锁定文件，返回锁定结果以及文件锁*
```cpp
virtual Status LockFile(const std::string& fname, FileLock** lock) = 0;
```

*解锁文件*
```cpp
virtual Status UnlockFile(FileLock* lock) = 0;
```

*调度函数*
```cpp
virtual void Schedule(
      void (*function)(void* arg),
      void* arg) = 0;
```

*开启线程*
```cpp
virtual void StartThread(void (*function)(void* arg), void* arg) = 0;
```

*获取测试目录*
```cpp
virtual Status GetTestDirectory(std::string* path) = 0;
```

*创建新日志*
```cpp
virtual Status NewLogger(const std::string& fname, Logger** result) = 0;
```

*获取毫秒数，只能用于获取时间差*
```cpp
virtual uint64_t NowMicros() = 0;
```

*sleep若干毫秒*
```cpp
virtual void SleepForMicroseconds(int micros) = 0;
```

# 3. EnvPosixTest   
1. 类作用： 用作对EnvPosix测试
2. 所在文件:../util/env_posix_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 4. EnvTest
1. 类作用：  A helper for the POSIX Env to facilitate testing
2. 所在文件:../util/env_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 5. EnvPosixTestHelper
1. 类作用：  A helper for the POSIX Env to facilitate testing
2. 所在文件:../util/env_posix_test_helper.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 6. EnvWrapper
1. 类作用： 对Env的所有调用进行转发，用户可以继承此类，以便对部分函数进行重写
2. 所在文件:../include/leveldb/env.h
3. 基类: Env
4. 继承类: 无
5. 主要函数:
参照Env

# 7. ErrorEnv
1. 类作用：  对Env的一个封装，允许注入错误，也是继承EnvWraper的一个例子
2. 所在文件:../util/testutil.h
3. 基类: EnvWrapper
4. 继承类: 无
5. 主要函数:
参照Env