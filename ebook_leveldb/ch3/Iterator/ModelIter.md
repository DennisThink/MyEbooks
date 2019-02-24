ModelIter,用作测试的迭代器，内部的存储结构采用std::map,key和value都是字符串，其中的查找，移动等算法都是通过Map的相关函数实现的

```cpp
  virtual bool Valid() const { return iter_ != map_->end(); }
    virtual void SeekToFirst() { iter_ = map_->begin(); }
    virtual void SeekToLast() {
      if (map_->empty()) {
        iter_ = map_->end();
      } else {
        iter_ = map_->find(map_->rbegin()->first);
      }
    }
    virtual void Seek(const Slice& k) {
      iter_ = map_->lower_bound(k.ToString());
    }
```