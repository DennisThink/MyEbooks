PosixSequentialFile实现了Posix环境的下的序列化读取文件接口。

## 1.构造函数
文件需要在调用前打开成功。
```cpp
PosixSequentialFile(std::string filename, int fd)
      : fd_(fd), filename_(filename) {}
```

## 2.析构函数
析构函数中关闭文件，
```cpp
 ~PosixSequentialFile() override { close(fd_); }
```

## 3.读取数据
使用read函数读取数据
```cpp
Status Read(size_t n, Slice* result, char* scratch) override {
Status status;
while (true) {
    ::ssize_t read_size = ::read(fd_, scratch, n);
    if (read_size < 0) {  // Read error.
    if (errno == EINTR) {
        continue;  // Retry
    }
    status = PosixError(filename_, errno);
    break;
    }
    *result = Slice(scratch, read_size);
    break;
}
return status;
}
```
