leveldb_comparator_t是leveldb的比较器在C语言下的接口，主要通过回调函数的形式，来实现比较器。

```cpp
struct leveldb_comparator_t : public Comparator {
  void* state_;
  void (*destructor_)(void*);
  int (*compare_)(
      void*,
      const char* a, size_t alen,
      const char* b, size_t blen);
  const char* (*name_)(void*);

  virtual ~leveldb_comparator_t() {
    (*destructor_)(state_);
  }

  virtual int Compare(const Slice& a, const Slice& b) const {
    return (*compare_)(state_, a.data(), a.size(), b.data(), b.size());
  }

  virtual const char* Name() const {
    return (*name_)(state_);
  }

  // No-ops since the C binding does not support key shortening methods.
  virtual void FindShortestSeparator(std::string*, const Slice&) const { }
  virtual void FindShortSuccessor(std::string* key) const { }
};
```