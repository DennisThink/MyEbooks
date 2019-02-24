STATUS命令

参数：                         
邮箱名，状态数据项名

响应：                         
非标签化响应：STATUS

结果：                         
OK－status完成
NO－status失败：没有那个名称的status
BAD－未知命令，或者无效参数

STATUS命令请求指定邮箱的状态。它不改变当前被选中的邮箱，也不影响被请求的邮箱中的任何邮件的状态（特别的，STATUS不能使邮件失去/Recent标记）。

STATUS提供了这样一个选择：在没有取消选择第一次IMAP4rev1连接中的当前邮箱的情况下，就打第二次IMAP4rev1连接，并在一个邮箱上进行一个EXAMINE命令以请求那个邮箱的状态。

与LIST命令不同，STATUS命令不一定是快速响应的。在特定条件下，它可能是很慢的。在某些实现体中，服务器被希望以只读方式内部打开邮箱获取特定的状态信息。STATUS命令不接受通配符，这一点也与LIST命令不同。

注意：STATUS命令用于访问邮箱的状态，而不是当前选中的邮箱。因为STATUS命令可以使邮箱被内部打开，且这个信息是可以通过在选中邮箱上的其它手段获取的，所以STATUS命令不应当用于当前选中邮箱。

STATUS命令不能用于“检查选中邮箱中的新邮件”操作（关于检查新邮件的恰当方法的更多信息，参看第7章，7.3.1和7.3.2）。

因为STATUS命令不一定是快速响应的，所以客户端不应当预计能够发出一连串的STATUS命令并获得相应的执行。

当前定义了的、可以请求的状态数据项有：


> MESSAGES

邮箱中邮件数量。

> RECENT

带有/Recent标记位的邮件数量。

> UIDNEXT

邮箱的下一个唯一标识符的值。更多信息参看2.3.1.1一节。

> UIDVALIDITY

邮箱的唯一标识符检验码。更多信息参看2.3.1.1一节。

> UNSEEN

不带有/Seen标记位的邮件数量。


例子：                         
```
C: A042 STATUS blurdybloop (UIDNEXT MESSAGES)

S: * STATUS blurdybloop (MESSAGES 231 UIDNEXT 44292)

S: A042 OK STATUS completed
```