NOOP命令

参数：                                                  
无

响应：                                
此命令无特定响应（见下）

结果：                                
OK－noop完成

BAD－未知命令，或者参数无效

NOOP命令总是成功的。它什么也不做。

因为任何命令都可以返回一个状态更新作为非标签化数据，NOOP命令可以用作新邮件的周期性检测，或者在一个静止期间内的邮件状态刷新（实现这个，用这种方法是比较好的）。NOOP命令还可以用来重设服务器上任何静止的自动注销计时器。

例子：                                

```
C: a002 NOOP

S: a002 OK NOOP completed
```

```
…

C: a047 NOOP

S: * 22 EXPUNGE

S: * 23 EXISTS

S: * 3 RECENT

S: * 14 FETCH (FLAGS (/Seen /Deleted))

S: a047 OK NOOP completed
```