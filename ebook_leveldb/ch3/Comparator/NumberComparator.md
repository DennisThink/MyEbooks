NumberComparator是将比较器的操作转为对数字的操作来实现比较器的相关接口。

```cpp
  class NumberComparator : public Comparator {
   public:
    virtual const char* Name() const { return "test.NumberComparator"; }
    /**
     * @brief 将字符串的比较转为数字的比较
     * @return 字符串比较的结果
     */
    virtual int Compare(const Slice& a, const Slice& b) const {
      return ToNumber(a) - ToNumber(b);
    }
	
    /**
     * @brief 仅检查格式
     * @return 
     */
    virtual void FindShortestSeparator(std::string* s, const Slice& l) const {
      ToNumber(*s);     // Check format
      ToNumber(l);      // Check format
    }
	
	
    /**
     * @brief 仅检查格式
     * @return 
     */
    virtual void FindShortSuccessor(std::string* key) const {
      ToNumber(*key);   // Check format
    }
   private:
    /**
     * @brief 使用sscanf将字符串转为数字
     * @return 
     */
    static int ToNumber(const Slice& x) {
      // Check that there are no extra characters.
      ASSERT_TRUE(x.size() >= 2 && x[0] == '[' && x[x.size()-1] == ']')
          << EscapeString(x);
      int val;
      char ignored;
      ASSERT_TRUE(sscanf(x.ToString().c_str(), "[%i]%c", &val, &ignored) == 1)
          << EscapeString(x);
      return val;
    }
  };
```