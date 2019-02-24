BytewiseComparatorImpl是Comparator的一个实现类。
其主要函数如下:


## 1.获取名称
```cpp
virtual const char* Name() const {
   return "leveldb.BytewiseComparator";
}
```

## 2.比较Slice的大小
```cpp
virtual int Compare(const Slice& a, const Slice& b) const {
   return a.compare(b);
}
```

## 3.获取较短的分割器
```cpp
  virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const {
    // Find length of common prefix
    size_t min_length = std::min(start->size(), limit.size());
    size_t diff_index = 0;
	
	//查找start和limit的相同的字符
    while ((diff_index < min_length) &&
           ((*start)[diff_index] == limit[diff_index])) {
      diff_index++;
    }
	

    //如果一个另一个的前缀的话，则无需改变
    if (diff_index >= min_length) {
      // Do not shorten if one string is a prefix of the other
    } else {
	  //改变start值，作为结果返回
      uint8_t diff_byte = static_cast<uint8_t>((*start)[diff_index]);
      if (diff_byte < static_cast<uint8_t>(0xff) &&
          diff_byte + 1 < static_cast<uint8_t>(limit[diff_index])) {
        (*start)[diff_index]++;
        start->resize(diff_index + 1);
        assert(Compare(*start, limit) < 0);
      }
    }
  }
```

## 4.获取key中第一个不是0xff的字符
```cpp
 virtual void FindShortSuccessor(std::string* key) const {
    // Find first character that can be incremented
    size_t n = key->size();
    for (size_t i = 0; i < n; i++) {
      const uint8_t byte = (*key)[i];
      if (byte != static_cast<uint8_t>(0xff)) {
        (*key)[i] = byte + 1;
        key->resize(i+1);
        return;
      }
    }
    // *key is a run of 0xffs.  Leave it alone.
  }
```