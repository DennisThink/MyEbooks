RandomAccessFile主要定义了一个随机读取文件内容的接口，用来读取文件的内容。

主要函数：
## 1.读取文件内容接口
```cpp
  virtual Status Read(uint64_t offset, size_t n, Slice* result,
                      char* scratch) const = 0;
```
