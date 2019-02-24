ReverseKeyComparator是对Comparator传入的数据，逆序后进行操作，然后将结果在逆序返回，InternalKey的操作与此类似。

```cpp
class ReverseKeyComparator : public Comparator {
public:
 
 
  /**
   * @brief 获取比较器的文件名
   * @return 比较器文件名
   */
  virtual const char* Name() const {
    return "leveldb.ReverseBytewiseComparator";
  }


  /**
   * @brief 比较两个Slice
   * @param a 
   * @param b
   * @return a > b ; 结果> 0  a==b 结果为0 a < b 结果小于0
   */
  virtual int Compare(const Slice& a, const Slice& b) const {
    return BytewiseComparator()->Compare(Reverse(a), Reverse(b));
  }

  /**
   * @brief 找到start和limit，最短分割器
   * @param start 传入传出参数
   * @param limit 
   */
  virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const {
    std::string s = Reverse(*start);
    std::string l = Reverse(limit);
    BytewiseComparator()->FindShortestSeparator(&s, l);
    *start = Reverse(s);
  }

  
  /**
   * @brief 获取最短的后继者
   * @param key
   */
  virtual void FindShortSuccessor(std::string* key) const {
    std::string s = Reverse(*key);
    BytewiseComparator()->FindShortSuccessor(&s);
    *key = Reverse(s);
  }
};
```