WritableFileImpl是通过FileState实现的WritableFile，无缓冲区。

## 1.构造函数
```cpp
WritableFileImpl(FileState* file) : file_(file) {
    file_->Ref();
}
```
## 2.析构函数
```cpp
~WritableFileImpl() {
    file_->Unref();
}
```
## 3.添加内容
```cpp
virtual Status Append(const Slice& data) {
    return file_->Append(data);
}
```