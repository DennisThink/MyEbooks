定义一个空的迭代器，对所有接口给出默认的实现,在无法给出有效的迭代器的时候，返回一个空的迭代器，而不是返回nullptr。通过这种方式可以简化内部的逻辑判断。



代码实现：

```cpp
class EmptyIterator : public Iterator {
 public:
  EmptyIterator(const Status& s) : status_(s) { }
  ~EmptyIterator() override = default;

  bool Valid() const override { return false; }
  void Seek(const Slice& target) override { }
  void SeekToFirst() override { }
  void SeekToLast() override { }
  void Next() override { assert(false); }
  void Prev() override { assert(false); }
  Slice key() const override { assert(false); return Slice(); }
  Slice value() const override { assert(false); return Slice(); }
  Status status() const override { return status_; }

 private:
  Status status_;
};
```


