KeyConvertingIterator主要完成了UserKey和InternalKey的转换，它通过在构造的时候，传入一个Iter的指针，对大部分的函数调用都是通过转发的方式来进行。主要的修改点在获取Key的值，以及查找的地方。

## 1.获取Key的值
```cpp
  /**
   * @brief 将InternalKey转为UserKey返回
   * @return UserKey
   */
  
  virtual Slice key() const {
    assert(Valid());
    ParsedInternalKey key;
    if (!ParseInternalKey(iter_->key(), &key)) {
      status_ = Status::Corruption("malformed internal key");
      return Slice("corrupted key");
    }
    return key.user_key;
  }
```

## 2.进行查找
在查找的时候，将UserKey转为InternalKey进行查找。
```cpp
  /**
   * @brief 在查找的时候，先将UserKey转为InternalKey，再查找
   * @param target 待查找的Userkey
   */
  
  virtual void Seek(const Slice& target) {
    ParsedInternalKey ikey(target, kMaxSequenceNumber, kTypeValue);
    std::string encoded;
    AppendInternalKey(&encoded, ikey);
    iter_->Seek(encoded);
  }
```