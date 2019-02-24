PosixRandomAccessFile通过重载Read函数，在其中使用pread，可以在不改变文件指针位置的情况下，读取指定区域的内容。

## 1.构造函数
调用Acquire加锁
```cpp
PosixRandomAccessFile(std::string filename, int fd, Limiter* fd_limiter)
      : has_permanent_fd_(fd_limiter->Acquire()),
        fd_(has_permanent_fd_ ? fd : -1),
        fd_limiter_(fd_limiter),
        filename_(std::move(filename)) {
    if (!has_permanent_fd_) {
      assert(fd_ == -1);
      ::close(fd);  // The file will be opened on every read.
    }
  }
```

## 2.析构函数
调用Release解锁
```cpp
  ~PosixRandomAccessFile() override {
    if (has_permanent_fd_) {
      assert(fd_ != -1);
      ::close(fd_);
      fd_limiter_->Release();
    }
  }
```

## 3.读取内容
```cpp
Status Read(uint64_t offset, size_t n, Slice* result,
              char* scratch) const override {
    int fd = fd_;
    if (!has_permanent_fd_) {
      fd = ::open(filename_.c_str(), O_RDONLY);
      if (fd < 0) {
        return PosixError(filename_, errno);
      }
    }

    assert(fd != -1);

    Status status;
	//pread通过传入offset，可以在不改变文件读取位置的情况下，读取内容，
    ssize_t read_size = ::pread(fd, scratch, n, static_cast<off_t>(offset));
    *result = Slice(scratch, (read_size < 0) ? 0 : read_size);
    if (read_size < 0) {
      // An error: return a non-ok status.
      status = PosixError(filename_, errno);
    }
    if (!has_permanent_fd_) {
      // Close the temporary file descriptor opened earlier.
      assert(fd != fd_);
      ::close(fd);
    }
    return status;
  }
```

## 4.成员变量
```cpp
private:
  //false 每次read的时候打开，true，保持打开
  const bool has_permanent_fd_;  // If false, the file is opened on every read.
  
  // has_permanent_fd_ 则fd_为-1，因为每次都打开，所以不保存文件描述符
  const int fd_;  // -1 if has_permanent_fd_ is false.
  //文件打开的限制，在构造和析构函数中使用
  Limiter* const fd_limiter_;
  //文件名
  const std::string filename_;
```