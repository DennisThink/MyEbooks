# 1. Arena
1. 类作用：负责内存的分配和回收
2. 所在文件: ../util/arena.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*返回bytes字节的新的内存块*
```cpp
char* Allocate(size_t bytes);
```
*返回具有字节对齐的bytes字节的内存块*

```cpp
char* AllocateAligned(size_t bytes);
```

*返回arena使用的总的内存数量*
```cpp
size_t MemoryUsage()
```

# 2. ArenaTest   
1. 类作用：用作类`Arena`的自动化测试
2. 所在文件../util/arena_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*测试Arena的构造和析构*
```cpp
TEST(ArenaTest, Empty)
```
*使用arena申请内存，并按照%256的值赋值，然后检查赋值是否正确*
```cpp
TEST(ArenaTest, Simple)
```

# 3. AtomicCounter    
1. 类作用：用于原子计数
2. 所在文件：../db/db_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*计数量加1*
```cpp
void Increment()
```

*计数量增加Count*
```cpp
void IncrementBy(int count)
```

*读取当前计数值,线程安全*
```cpp
int Read() 
```

*重置计数器*
```cpp
void Reset() 
```

# 4.AtomicPointer   
1. 类作用：通过内存序保证原子访问
2. 所在文件../port/atomic_pointer.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*获取值，多线程不安全*
```cpp
void* NoBarrier_Load() 
```

*设置值，多线程不安全*
```cpp
void NoBarrier_Store(void* v) 
```

*获取值,多线程安全*
```cpp
void* Acquire_Load() 
```

*设置值,多线程安全*
```cpp
void Release_Store(void* v) 
```

# 5. AutoCompactTest   
1. 类作用：测试数据库的读取
2. 所在文件../db/autocompact_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:

*根据i生成Key,1-->"key000001"*
```cpp  
std::string Key(int i)
```

*获取从start到limit的size*
```cpp
uint64_t Size(const Slice& start, const Slice& limit)
```
