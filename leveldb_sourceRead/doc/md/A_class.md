# 1 Arena
1. 类作用：负责内存的分配和回收
2. 所在文件: ../util/arena.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:
* // 返回bytes字节的新的内存块
  char* Allocate(size_t bytes);
*   // 返回具有字节对齐的bytes字节的内存块
  char* AllocateAligned(size_t bytes);
*   // 返回arena使用的总的内存数量
  size_t MemoryUsage()
# 2. ArenaTest   
1. 类作用：用作类`Arena`的自动化测试
2. 所在文件../util/arena_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
* TEST(ArenaTest, Simple)

# 2. ArenaTest   
1. 类作用：用作类`Arena`的自动化测试
2. 所在文件../util/arena_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
* TEST(ArenaTest, Simple)

# 3 AtomicCounter    
1. 类作用：用于原子计数
2. 所在文件/home/dennis/GitHub/leveldb_sourceRead/code/leveldb-master/db/db_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
* void Increment()
* void IncrementBy(int count)
* int Read() 
* void Reset() 


# 2. AtomicPointer   
1. 类作用：通过内存序保证原子访问
2. 所在文件../port/atomic_pointer.h
3. 基类: 无
4. 继承类: 无
5. 主要函数:

获取值
> void* NoBarrier_Load() 

设置值
> void NoBarrier_Store(void* v) 

获取值
> void* Acquire_Load() 

设置值
>  void Release_Store(void* v) 

# 2. AutoCompactTest   
1. 类作用：测试数据库的读取
2. 所在文件../db/autocompact_test.cc
3. 基类: 无
4. 继承类: 无
5. 主要函数:
  /**
   * @brief 根据i 生成Key
   * @param i 输入参数
   * @return 生成的Key
   */
  std::string Key(int i)

  /**
   * @brief 获取从start到limit的size
   * @param start 起始位置
   * @param limit 结束位置
   * @return 获取的size
   */
  uint64_t Size(const Slice& start, const Slice& limit)

