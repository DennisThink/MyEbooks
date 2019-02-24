LOGOUT命令

参数：                                
无

响应：                                              
要求非标签化的响应：BYE

结果：                                              
OK－logout完成

BAD－未知命令，或者无效参数

LOGOUT命令告知服务器，客户端准备关闭连接。服务器必须在（标签化）OK响应前，发送一个BYE非标签化响应，并随后关闭这个网络连接。

例子：

```
C: A023 LOGOUT

S: * BYE IMAP4rev1 Server logging out

S: A023 OK LOGOUT completed

(Server and client then close the connection)
```