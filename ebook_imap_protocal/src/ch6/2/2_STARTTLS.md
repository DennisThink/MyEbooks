STARTTLS命令
**参数**：
无

**响应**：
此命令无需特定响应

**结果**：
OK－starttls完成，开始TLS对话
BAD－未知命令，或者无效参数

在来自服务器端的标签化OK响应末尾的CRLF之后，一个“TLS”对话就开始了。一旦一个客户端发出一个STARTTLS命令，它就不能再发送其它命令，直到服务器响应出现并且“TLS”对话结束。

服务器保持未认证状态，即使客户端证书在“TLS”对话期间是受支持的。这不排除像EXTERNAL（“SASL”中定义的）的认证机制使用“TLS”对话决定的用户标识。

一旦“TLS”开始，客户端必须丢弃关于服务器功能的缓存信息，且应当重新发出CAPABILITY命令。这对保护免受修改功能列表指向STARTTLS的中间者攻击是有必要的。服务器可以在STARTTLS后发出不同功能。

**例子**：
```
C: a001 CAPABILITY

S: * CAPABILITY IMAP4rev1 STARTTLS LOGINDISABLED

S: a001 OK CAPABILITY completed

C: a002 STARTTLS

S: a002 OK Begin TLS negotiation now

<TLS negotiation, further commands are under [TLS] layer>

C: a003 CAPABILITY

S: * CAPABILITY IMAP4rev1 AUTH=PLAIN

S: a003 OK CAPABILITY completed

C: a004 LOGIN joe password

S: a004 OK LOGIN completed
```