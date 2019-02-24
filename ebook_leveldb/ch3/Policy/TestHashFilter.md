TestHashFilter为每个Key生成一个32bit的哈希值，保存到dst中用作过滤器。

## 1.创建过滤数据
```cpp
virtual void CreateFilter(const Slice* keys, int n, std::string* dst) const {
    for (int i = 0; i < n; i++) {
      uint32_t h = Hash(keys[i].data(), keys[i].size(), 1);
      PutFixed32(dst, h);
    }
}
```

## 2.判断Key是否在Filter中
```cpp
virtual bool KeyMayMatch(const Slice& key, const Slice& filter) const {
    uint32_t h = Hash(key.data(), key.size(), 1);
    for (size_t i = 0; i + 4 <= filter.size(); i += 4) {
        if (h == DecodeFixed32(filter.data() + i)) {
        return true;
        }
    }
    return false;
}
```