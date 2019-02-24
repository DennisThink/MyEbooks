InternalKeyComparator是对Comparator的继承，在构造的时候，使用了user_comparator。在进行相关操作的时候，都需要先从internalKey中提取出UserKey,然后进行操作，

## 1. 比较函数
在比较之前要将UserKey先抽离出来，再做比较。
在UserKey相同的情况下，要比较SequenceNumber以及类型。
```cpp
/**
 * @brief 按升序比较UserKey,按降序比较序列号，按降序比较类型
 * @param akey 待比较的第一个key
 * @param bkey 待比较的第二个key
 * @return 比较结果
 */
int InternalKeyComparator::Compare(const Slice& akey, const Slice& bkey) const {
  // Order by:
  //    increasing user key (according to user-supplied comparator)
  //    decreasing sequence number
  //    decreasing type (though sequence# should be enough to disambiguate)
  int r = user_comparator_->Compare(ExtractUserKey(akey), ExtractUserKey(bkey));
  if (r == 0) {
    const uint64_t anum = DecodeFixed64(akey.data() + akey.size() - 8);
    const uint64_t bnum = DecodeFixed64(bkey.data() + bkey.size() - 8);
    if (anum > bnum) {
      r = -1;
    } else if (anum < bnum) {
      r = +1;
    }
  }
  return r;
}
```

## 2.获取比较器的名称
```cpp
const char* InternalKeyComparator::Name() const {
  return "leveldb.InternalKeyComparator";
}
```

## 3.获取较短的Key
```cpp
void InternalKeyComparator::FindShortestSeparator(
      std::string* start,
      const Slice& limit) const {
  // Attempt to shorten the user portion of the key
  // 先从数据中抽取出UserKey
  Slice user_start = ExtractUserKey(*start);
  Slice user_limit = ExtractUserKey(limit);
  std::string tmp(user_start.data(), user_start.size());
  user_comparator_->FindShortestSeparator(&tmp, user_limit);
  if (tmp.size() < user_start.size() &&
      user_comparator_->Compare(user_start, tmp) < 0) {
    // User key has become shorter physically, but larger logically.
    // Tack on the earliest possible number to the shortened user key.
	// 将UserKey转为InternalKey
    PutFixed64(&tmp, PackSequenceAndType(kMaxSequenceNumber,kValueTypeForSeek));
    assert(this->Compare(*start, tmp) < 0);
    assert(this->Compare(tmp, limit) < 0);
    start->swap(tmp);
  }
}


```

## 4.获取较短的Successer
```cpp
/**
 * @brief 
 * @param key
 */
void InternalKeyComparator::FindShortSuccessor(std::string* key) const {
  //转为UserKey	
  Slice user_key = ExtractUserKey(*key);
  std::string tmp(user_key.data(), user_key.size());
  //找最短的
  user_comparator_->FindShortSuccessor(&tmp);
  if (tmp.size() < user_key.size() &&
      user_comparator_->Compare(user_key, tmp) < 0) {
    // User key has become shorter physically, but larger logically.
    // Tack on the earliest possible number to the shortened user key.
	//转为InternalKey
    PutFixed64(&tmp, PackSequenceAndType(kMaxSequenceNumber,kValueTypeForSeek));
    assert(this->Compare(*key, tmp) < 0);
    key->swap(tmp);
  }
}
      const Slice& limit) const = 0;
```