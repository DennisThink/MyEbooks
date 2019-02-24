# 1. NoDestructor<typename InstanceType>
1. 类作用： 模板类，封装析构函数从不调用的变量，主要用在函数级的静态变量
2. 所在文件:../util/no_destructor.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
//使用C++的模板变参和完美转发，构造对应的类型
template <typename... ConstructorArgTypes>
  explicit NoDestructor(ConstructorArgTypes&&... constructor_args)
//获取对应的类型 
InstanceType* get()

../util/comparator.cc
const Comparator* BytewiseComparator() {
  static NoDestructor<BytewiseComparatorImpl> singleton;
  return singleton.get();
}

# 1. NoDestructorTest
1. 类作用： 对NoDestructor<typename InstanceType>进行测试
2. 所在文件:../util/no_destructor_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

# 1. NoOpLogger
1. 类作用： 不进行任何操作的写日志类
2. 所在文件:../helpers/memenv/memenv.cc
3. 基类: Logger
4. 继承类: 无
5. 主要函数:
virtual void Logv(const char* format, va_list ap)



