实现WritableFile接口，直接输出到控制台。

## 1.添加文件内容的函数
```cpp
virtual Status Append(const Slice& data) {
    fwrite(data.data(), 1, data.size(), stdout);
    return Status::OK();
}
```