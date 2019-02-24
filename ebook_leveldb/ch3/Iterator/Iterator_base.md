Iterator主要制定了查找等的接口，还定义了在迭代器失效的时候，可以由用户指定回调函数。

接口定义：
## 1.有效性判定和数据获取：
1. 迭代器是否有效(`Valid()`)
2. 获取Key(`key()`)
3. 获取Value(`value()`)

## 2.迭代器移动
1. 移动到第一个位置(`SeekToFirst()`)
2. 移动到最后一个位置(`SeekToLast()`)
3. 移动到指定位置(`Seek()`)
4. 移动到下一个(`Next()`)
5. 移动到上一个(`Prev()`)

## 3.指定回调函数：
1. 回调函数类型定义(`using CleanupFunction = void (*)(void* arg1, void* arg2);`)
2. 添加回调函数(`RegisterCleanup`)