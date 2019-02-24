StringSource是以std::string为存储，实现的RandomAccessFile

```cpp
class StringSource: public RandomAccessFile {
 public:
  StringSource(const Slice& contents)
      : contents_(contents.data(), contents.size()) {
  }

  virtual ~StringSource() { }

  uint64_t Size() const { return contents_.size(); }

  /**
   * @brief 重载RandomAccessFile的Read函数，将[offset，offset+n]的内容保存到result中，内存由scratch保持
   * @param offset 读取的起始位置
   * @param n 读取的长度
   * @param result 读取的结果
   * @param scratch 传入的内存
   * @return 读取的结果
   */
  virtual Status Read(uint64_t offset, size_t n, Slice* result,
                       char* scratch) const {
    if (offset > contents_.size()) {
      return Status::InvalidArgument("invalid Read offset");
    }
    if (offset + n > contents_.size()) {
      n = contents_.size() - offset;
    }
    memcpy(scratch, &contents_[offset], n);
    *result = Slice(scratch, n);
    return Status::OK();
  }

 private:
  std::string contents_;
};
```