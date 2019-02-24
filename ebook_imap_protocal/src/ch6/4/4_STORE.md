STORE命令

参数：                         
序列集，邮件数据项名称，邮件数据项值

响应：                         
非标签化响应：FETCH                         

结果：                         
OK－store完成
NO－store错误：不能保存该数据
BAD－未知命令，或者无效参数

STORE命令修改邮箱中邮件相关的数据。正常地，STORE将返回数据更新后的值和一个非标签化FETCH响应。数据项名称中的“.SILENT”后缀保护该非标签化FETCH，且服务器应当假定客户端已经自行决定了该更新后的值，或者客户端不关心该更新后的值。

注意：不管是否使用了“.SILENT”后缀，如果发现一个邮件的标记有源于外部资源的改变，服务器应当发送一个非标签化FETCH响应。目的是使标记的状态在没有竞争的情况下确定。

现在已经定义了的、可以保存的数据项有：


FLAGS <flag list>

用参数替代邮件（不是/Recent）的标记。返回标记集的新值，就像那些标记集的FETCH结果一样。

FLAGS.SILENT <flag list>

等效于FLAGS，但是不会返回一个新值。


+FLAGS <flag list>

增加参数至邮件的标记集中。返回标记集的新值，就像那些标记集的FETCH结果一样。

-FLAGS <flag list>

从邮件的标记集中删除参数。返回标记集的新值，就像那些标记集的FETCH结果一样。

-FLAGS.SILENT <flag list>

等效于-FLAGS，但是不会返回一个新值。

例子：                         

```
C: A003 STORE 2:4 +FLAGS (/Deleted)

S: * 2 FETCH (FLAGS (/Deleted /Seen))

S: * 3 FETCH (FLAGS (/Deleted))

S: * 4 FETCH (FLAGS (/Deleted /Flagged /Seen))

S: A003 OK STORE completed
```