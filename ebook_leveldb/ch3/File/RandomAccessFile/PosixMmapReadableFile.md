通过使用mmap，将文件映射到内存，PosixMmapReadableFile通过封装这块内存，实现像访问普通文件的方式来访问数据。加锁在外部进行。解锁在析构函数进行，具体参照`env_posix.cc`的`NewRandomAccessFile`函数。

## 1.构造函数
```cpp
PosixMmapReadableFile(std::string filename, char* mmap_base, size_t length,
                        Limiter* mmap_limiter)
      : mmap_base_(mmap_base), length_(length), mmap_limiter_(mmap_limiter),
        filename_(std::move(filename)) {}
```

## 2.析构函数
```cpp
~PosixMmapReadableFile() override {
    ::munmap(static_cast<void*>(mmap_base_), length_);
    mmap_limiter_->Release();
  }
```

## 3.读取数据
直接将保存的内容，放入结果
```cpp
Status Read(uint64_t offset, size_t n, Slice* result,
            char* scratch) const override {
if (offset + n > length_) {
    *result = Slice();
    return PosixError(filename_, EINVAL);
}

*result = Slice(mmap_base_ + offset, n);
return Status::OK();
}
```