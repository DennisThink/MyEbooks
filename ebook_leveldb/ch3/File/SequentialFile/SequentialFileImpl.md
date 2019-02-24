SequentialFileImpl包装FileState使其成为一个SequentialFile
```cpp
class SequentialFileImpl : public SequentialFile {
 public:
  explicit SequentialFileImpl(FileState* file) : file_(file), pos_(0) {
    file_->Ref();
  }

  ~SequentialFileImpl() {
    file_->Unref();
  }

  virtual Status Read(size_t n, Slice* result, char* scratch) {
    Status s = file_->Read(pos_, n, result, scratch);
    if (s.ok()) {
      pos_ += result->size();
    }
    return s;
  }

  virtual Status Skip(uint64_t n) {
    if (pos_ > file_->Size()) {
      return Status::IOError("pos_ > file_->Size()");
    }
    const uint64_t available = file_->Size() - pos_;
    if (n > available) {
      n = available;
    }
    pos_ += n;
    return Status::OK();
  }

 private:
  FileState* file_;
  uint64_t pos_;
};
```