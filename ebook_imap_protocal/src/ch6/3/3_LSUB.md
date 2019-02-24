LSUB命令

参数：                            
引用名，带有可能的通配符的邮箱名

响应：                            
非标签化的响应：LSUB

结果：                            
OK－lsub完成
NO－lsub失败：不能列出那个引用或者名称
BAD－未知命令，或者无效参数

LSUB命令返回的是，用户已经声明为活动的、或者订阅了的名称序列的一个名称子集。0个或者更多的非标签化LSUB答复被返回。LSUB的参数同于LIST的形式。

返回的非标签化LSUB响应可能包含从一个非标签化LIST响应的不同邮箱标记。如果出现这个，那么在非标签化LIST中的标记会被认为是更可信的。

当使用带有%通配符的LSUB时，一种特殊的情形就出现了。试想一下，如果“foo/bar”（带有一个“/”层级定义符）是已订阅的，而“foo”不是。在LSUB响应中，LSUB的一个“%”通配符必须返回foo，而不是foo/bar，并且它必须标记为带/Noselect属性的。

服务器不能单方面从订阅列表中移除一个已经存在的邮箱名，即使那个名称的邮箱已经不存在了。

例子：                            

```
C: A002 LSUB “#news.” “comp.mail.*”

S: * LSUB () “.” #news.comp.mail.mime

S: * LSUB () “.” #news.comp.mail.misc

S: A002 OK LSUB completed

C: A003 LSUB “#news.” “comp.%”

S: * LSUB (/NoSelect) “.” #news.comp.mail

S: A003 OK LSUB completed
```