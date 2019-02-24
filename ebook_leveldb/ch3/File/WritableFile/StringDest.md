StringDest通过将内容直接写入到std::string中，实现了WritableFile接口。同[StringSink](./StringSink.md)非常像。

## 1.添加内容函数
```cpp
virtual Status Append(const Slice& slice) {
      contents_.append(slice.data(), slice.size());
      return Status::OK();
    }
```