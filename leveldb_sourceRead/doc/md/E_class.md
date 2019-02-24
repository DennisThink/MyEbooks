# 1. EmptyIterator   
1. 类作用： 对CRC相关函数进行测试
2. 所在文件:../table/iterator.cc
3. 基类: Iterator
4. 继承类: 无
5. 主要函数:
bool Valid() const override { return false; }
void Seek(const Slice& target) override { }
void SeekToFirst() override { }
void SeekToLast() override { }
void Next() override { assert(false); }
void Prev() override { assert(false); }
Slice key() const override { assert(false); return Slice(); }
Slice value() const override { assert(false); return Slice(); }
Status status() const override { return status_; }

# 1. Env   
1. 类作用： 对操作系统的相关功能进行封装，提供一个统一的接口
2. 所在文件:../include/leveldb/env.h
3. 基类: 无
4. 继承类: PosixDefaultEnv,
5. 主要函数:
获取默认的Env
static Env* Default();

// 根据特定的名称创建一个序列化的读取文件类，
virtual Status NewSequentialFile(const std::string& fname,
                                   SequentialFile** result) = 0;
// 创建随机读文件
virtual Status NewRandomAccessFile(const std::string& fname,
                                     RandomAccessFile** result) = 0;

创建可写文件
virtual Status NewWritableFile(const std::string& fname,
                                 WritableFile** result) = 0;

创建可追加文件
virtual Status NewAppendableFile(const std::string& fname,
                                   WritableFile** result);

//获取当前目录的子目录和文件
virtual Status GetChildren(const std::string& dir,
                             std::vector<std::string>* result) = 0;

  //  删除文件
  virtual Status DeleteFile(const std::string& fname) = 0;

  创建目录
  virtual Status CreateDir(const std::string& dirname) = 0;

  删除目录
  virtual Status DeleteDir(const std::string& dirname) = 0;

  获取文件大小
  virtual Status GetFileSize(const std::string& fname, uint64_t* file_size) = 0;

  重命名文件
  virtual Status RenameFile(const std::string& src,
                            const std::string& target) = 0;

  锁定文件，返回锁定结果以及文件锁
  virtual Status LockFile(const std::string& fname, FileLock** lock) = 0;

  解锁文件
  virtual Status UnlockFile(FileLock* lock) = 0;

  调度函数
  virtual void Schedule(
      void (*function)(void* arg),
      void* arg) = 0;

开启线程
  virtual void StartThread(void (*function)(void* arg), void* arg) = 0;

//获取测试目录
  virtual Status GetTestDirectory(std::string* path) = 0;

//创建新日志
  virtual Status NewLogger(const std::string& fname, Logger** result) = 0;

//获取毫秒数，只能用于获取时间差
  virtual uint64_t NowMicros() = 0;

//sleep若干毫秒
  virtual void SleepForMicroseconds(int micros) = 0;

# 1. EnvPosixTest   
1. 类作用： 用作对EnvPosix测试
2. 所在文件:../util/env_posix_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 1. EnvTest
1. 类作用：  A helper for the POSIX Env to facilitate testing
2. 所在文件:../util/env_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 1. EnvPosixTestHelper
1. 类作用：  A helper for the POSIX Env to facilitate testing
2. 所在文件:../util/env_posix_test_helper.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:


# 1. EnvWrapper
1. 类作用： 对Env的所有调用进行转发，用户可以继承此类，以便对部分函数进行重写
2. 所在文件:../include/leveldb/env.h
3. 基类: Env
4. 继承类: 无
5. 主要函数:
 // The following text is boilerplate that forwards all methods to target().
  Status NewSequentialFile(const std::string& f, SequentialFile** r) override {
    return target_->NewSequentialFile(f, r);
  }
  Status NewRandomAccessFile(const std::string& f,
                             RandomAccessFile** r) override {
    return target_->NewRandomAccessFile(f, r);
  }
  Status NewWritableFile(const std::string& f, WritableFile** r) override {
    return target_->NewWritableFile(f, r);
  }
  Status NewAppendableFile(const std::string& f, WritableFile** r) override {
    return target_->NewAppendableFile(f, r);
  }
  bool FileExists(const std::string& f) override {
    return target_->FileExists(f);
  }
  Status GetChildren(const std::string& dir,
                     std::vector<std::string>* r) override {
    return target_->GetChildren(dir, r);
  }
  Status DeleteFile(const std::string& f) override {
    return target_->DeleteFile(f);
  }
  Status CreateDir(const std::string& d) override {
    return target_->CreateDir(d);
  }
  Status DeleteDir(const std::string& d) override {
    return target_->DeleteDir(d);
  }
  Status GetFileSize(const std::string& f, uint64_t* s) override {
    return target_->GetFileSize(f, s);
  }
  Status RenameFile(const std::string& s, const std::string& t) override {
    return target_->RenameFile(s, t);
  }
  Status LockFile(const std::string& f, FileLock** l) override {
    return target_->LockFile(f, l);
  }
  Status UnlockFile(FileLock* l) override { return target_->UnlockFile(l); }
  void Schedule(void (*f)(void*), void* a) override {
    return target_->Schedule(f, a);
  }
  void StartThread(void (*f)(void*), void* a) override {
    return target_->StartThread(f, a);
  }
  Status GetTestDirectory(std::string* path) override {
    return target_->GetTestDirectory(path);
  }
  Status NewLogger(const std::string& fname, Logger** result) override {
    return target_->NewLogger(fname, result);
  }
  uint64_t NowMicros() override {
    return target_->NowMicros();
  }
  void SleepForMicroseconds(int micros) override {
    target_->SleepForMicroseconds(micros);
  }

# 1. ErrorEnv
1. 类作用：  A helper for the POSIX Env to facilitate testing
2. 所在文件:../util/env_posix_test_helper.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:



# 1. ErrorEnv
1. 类作用：  对Env的一个封装，允许注入错误，也是继承EnvWraper的一个例子
2. 所在文件:../util/testutil.h
3. 基类: EnvWrapper
4. 继承类: 无
5. 主要函数:
virtual Status NewWritableFile(const std::string& fname,
                                 WritableFile** result) 

  virtual Status NewAppendableFile(const std::string& fname,
                                   WritableFile** result)