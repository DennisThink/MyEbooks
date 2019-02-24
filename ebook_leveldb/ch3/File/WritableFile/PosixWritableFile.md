PosixWritableFile是WritableFile增加了一个缓冲区的Posix环境下的实现。

## 1.添加数据
首先尝试向缓冲区中写入数据，如果缓冲区的空间够，直接写入文件。
```cpp
Status Append(const Slice& data) override {
    size_t write_size = data.size();
    const char* write_data = data.data();

    // Fit as much as possible into buffer.
    size_t copy_size = std::min(write_size, kWritableFileBufferSize - pos_);
    std::memcpy(buf_ + pos_, write_data, copy_size);
    write_data += copy_size;
    write_size -= copy_size;
    pos_ += copy_size;
	//已有的空间足够，写入到buf_
    if (write_size == 0) {
      return Status::OK();
    }

    // Can't fit in buffer, so need to do at least one write.
	// 将buf刷入硬盘
    Status status = FlushBuffer();
    if (!status.ok()) {
      return status;
    }

    // Small writes go to buffer, large writes are written directly.
	//
    if (write_size < kWritableFileBufferSize) {
      std::memcpy(buf_, write_data, write_size);
      pos_ = write_size;
      return Status::OK();
    }
	//直接写入硬盘
    return WriteUnbuffered(write_data, write_size);
  }
```

## 2.关闭文件
先将缓冲区写入文件，然后再关闭文件。
```cpp
Status Close() override {
    Status status = FlushBuffer();
    const int close_result = ::close(fd_);
    if (close_result < 0 && status.ok()) {
        status = PosixError(filename_, errno);
    }
    fd_ = -1;
    return status;
}
```

