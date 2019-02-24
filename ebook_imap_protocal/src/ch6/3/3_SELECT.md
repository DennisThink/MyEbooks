SELECT命令
参数：                            
邮箱名

响应：                         
要求非标签化的响应：FLAGS，EXISTS，RECENT

要求OK非标签化响应：UNSEEN，PERMANENTFLAGS，UIDNEXT，UIDVALIDITY

结果：                         
OK－select完成，当前是选中状态

NO－select失败，当前是认证状态：不存在这个邮箱，不能访问邮箱

BAD－未知命令，或者参数无效

SELECT命令选中一个邮箱，以便这个邮箱中的邮件可以被访问。在返回一个OK给客户端前，服务器必须发送以下非标签化数据给客户端。要注意的是，这个协议的早期版本只要求FLAGS，EXISTS，和RECENT非标签化数据；因此，客户端实现体应当把丢失数据作为个别情况讨论。


FLAGS

邮箱中被定义的标记。更多细节参看FLAGS响应的描述。


<n>EXISTS

邮箱中邮件的数量。更多细节参看EXISTS响应的描述。


<n>RECENT

带有/Recent标记符的邮件的数量。更多细节参看RECENT响应的描述。


OK [UNSEEN <n>]

邮箱中第一封不可视邮件的邮件序列号。如果没有这个，客户端就不能对这个油箱中的第一封邮件做任何相关推测，如果想找到它，就需要发出一个SEARCH命令。


OK [PERMANENTFLAGS （<list of flags>）]

客户端可以永久修改的邮件标记的列表。如果没有这个，客户端应当推测所有的标记都是可以永久修改的。


OK [UIDNEXT <n>]

下一个唯一标识符的值。更多信息参考2.3.1.1一节。如果没有这个，客户端不能对下一个唯一标识符做任何相关推测。


OK [UIDVALIDITY <n>]

当前唯一标识符的值。更多信息参考2.3.1.1一节。如果没有这个，服务器就不支持唯一标识符。


在一个连接中，一次只能选中一个邮箱；同时访问多个邮箱要求多个连接。在尝试新的选择前，SELECT命令自动释放对任何当前选中邮箱的选中。因此，如果一个邮箱被选中，一个失败的SELECT命令正尝试，则没有邮箱被选中。

如果客户端被允许修改邮箱，则服务器应当把“[READ-WRITE]”响应码作为标签化OK响应的文本的前缀。

如果客户端没有修改邮箱的权限，但是有读取权限，则邮箱以只读方面选中，且服务器必须用“[READ-ONLY]”响应码作为标签化OK响应的文本前缀，以SELECT。通过SELECT方式的只读访问，与通过EXAMINE方式的只读访问，二者的区别在于，特定的只读邮箱可能允许基于用户（而不是全局）的永久状态的改变。在一个基于服务器的.newsrc文件中做了标记的网络论坛邮件就是这种可以被修改的、带有只读邮箱的、基于用户的永久状态的一个例子。

例子：                         
```
C: A142 SELECT INBOX

S: * 172 EXISTS

S: * 1 RECENT

S: * OK [UNSEEN 12] Message 12 is first unseen

S: * OK [UIDVALIDITY 3867529045] UID valid

S: * OK [UIDNEXT 4392] Predicted next UID

S: * FLAGS (/Answered /Flagged /Deleted /Seen /Draft)

S: * OK [PERMANENTFLAGS (/Deleted /Seen /*)] Limited

S: A142 OK [READ-WRITE] SELECT completed
```