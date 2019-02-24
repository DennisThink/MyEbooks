# 1. PosixEnv
1. 类作用： 继承自Env实现对Posix的环境的封装
2. 所在文件:../util/env_posix.cc
3. 基类: Env
4. 继承类: 无
5. 主要函数: 同Env



# 1. PosixFileLock
1. 类作用： Posix的文件锁类
2. 所在文件:../util/env_posix.cc
3. 基类: FileLock
4. 继承类: 无
5. 主要函数:
获取文件描述
int fd() const { return fd_; }
获取文件名
const std::string& filename() const { return filename_; }

# 1. PosixLockTable
1. 类作用： 追踪被PosixEnv::LockFile()加锁的文件
2. 所在文件:../util/env_posix.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
插入文件名
bool Insert(const std::string& fname)
删除文件名
void Remove(const std::string& fname)

# 1. PosixLogger
1. 类作用： Posix的日志类
2. 所在文件:../util/posix_logger.h
3. 基类: Logger
4. 继承类: 无
5. 主要函数:chuanru
构造函数，将文件传入
explicit PosixLogger(std::FILE* fp)
//日志写入函数
void Logv(const char* format, va_list arguments) override 

# 1. PosixMmapReadableFile
1. 类作用： 通过mmap映射来实现文件可读
2. 所在文件:../util/env_posix.cc
3. 基类: RandomAccessFile
4. 继承类: 无
5. 主要函数:
Status Read(uint64_t offset, size_t n, Slice* result,
              char* scratch) const override



# 1. PosixRandomAccessFile
1. 类作用： 随机读取文件的实现，线程安全,使用pread
2. 所在文件: ../util/env_posix.cc
3. 基类: RandomAccessFile
4. 继承类: 无
5. 主要函数:
Status Read(uint64_t offset, size_t n, Slice* result,
              char* scratch) const override

# 1. PosixSequentialFile
1. 类作用： 通过read函数实现了读取文件的类，是线程友好，但是不是线程安全
2. 所在文件:../util/env_posix.cc
3. 基类: SequentialFile
4. 继承类: 无
5. 主要函数:

Status Read(size_t n, Slice* result, char* scratch) override

Status Skip(uint64_t n) override


# 1. PosixWritableFile
1. 类作用： 实现Posix环境的下的可写文件
2. 所在文件:
3. 基类: WritableFile
4. 继承类: 无
5. 主要函数:
Status Append(const Slice& data) override
Status Close() override
Status Flush() override
Status Sync() override

