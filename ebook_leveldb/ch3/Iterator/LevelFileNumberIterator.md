LevelFileNumIterator,内部的存储采用数组的形式，所以每次向前或者向后移动，都是修改数组的下标。

## 1.查找函数
```cpp  
virtual void Seek(const Slice& target) {
    index_ = FindFile(icmp_, *flist_, target);
}
```
FindFile采用的是二分查找法。

## 2.获取key
```cpp
Slice key() const {
    assert(Valid());
    return (*flist_)[index_]->largest.Encode();
}
```

## 3.获取Value
```cpp
Slice value() const {
assert(Valid());
EncodeFixed64(value_buf_, (*flist_)[index_]->number);
EncodeFixed64(value_buf_+8, (*flist_)[index_]->file_size);
return Slice(value_buf_, sizeof(value_buf_));
}
```