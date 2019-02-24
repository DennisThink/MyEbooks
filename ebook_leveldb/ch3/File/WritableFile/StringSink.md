同[StringDest](./StringDest.md)非常像，也是通过将内容保存到std::string,实现了WritableFile接口。

## 1.添加内容
```cpp
virtual Status Append(const Slice& data) {
    contents_.append(data.data(), data.size());
    return Status::OK();
}
```