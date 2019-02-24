MemTableIterator是对SkipList的Iterator的一个封装，主要重载了两个函数。
此处可能涉及到SkipList的存储方式。
## 1.查找函数
将带查找的Key编码以后再查找
```cpp
virtual void Seek(const Slice& k) { iter_.Seek(EncodeKey(&tmp_, k)); }
```

## 2.获取Key
```cpp
 virtual Slice key() const { return GetLengthPrefixedSlice(iter_.key()); }
```

## 3.获取Value
```cpp
virtual Slice value() const {
    Slice key_slice = GetLengthPrefixedSlice(iter_.key());
    return GetLengthPrefixedSlice(key_slice.data() + key_slice.size());
  }
```

此处需要注意的两个函数，
一个是将长度放到数据之前，
一个是从带长度的数据中，解析出真正的数据。

编码数据
```cpp
static const char* EncodeKey(std::string* scratch, const Slice& target) {
  scratch->clear();
  PutVarint32(scratch, target.size());
  scratch->append(target.data(), target.size());
  return scratch->data();
}
```

解析数据
```cpp
static Slice GetLengthPrefixedSlice(const char* data) {
  uint32_t len;
  const char* p = data;
  p = GetVarint32Ptr(p, p + 5, &len);  // +5: we assume "p" is not corrupted
  return Slice(p, len);
}
```

