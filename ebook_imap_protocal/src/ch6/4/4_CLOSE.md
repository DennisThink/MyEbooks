CLOSE命令                         

参数：                         
无

响应：                         
此命令无需特定响应

结果：                         
OK－close完成，当前是认证状态
BAD－未知命令，或者无效参数

CLOSE命令从当前被选中邮箱中永久删除带有/Deleted标记位的所有邮件，并从被选中状态返回至认证状态。没有非标签化EXPUNGE响应被发送。

如果邮箱通过EXAMINE命令被选中，或者用别的方法以只读方式选中，则没有邮件会被删除，也不会报错。

甚至，一个邮箱被选中，没有预先发送一个CLOSE命令，一个SELECT, EXAMINE, 或者LOGOUT命令就可以被发出。SELECT, EXAMINE, 及LOGOUT命令没有进行删除，就暗暗关闭了当前被选中的邮箱。然而，当很多邮件被删除时，一个CLOSE-LOGOUT或者CLOSE-SELECT序列比一个EXPUNGE-LOGOUT或者EXPUNGE-SELECT快得多，因为没有非标签化EXPUNGE响应（客户端可以适当忽略）被发送。
