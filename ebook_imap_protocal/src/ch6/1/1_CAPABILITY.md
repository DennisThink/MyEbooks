### CAPABILITY命令

*参数:*          
无

响应：              
请求非标签化响应：CAPABILITY

结果：              
OK－capability完成
BAD－未知命令，或者参数无效


CAPABILITY命令请求服务器支持的功能列表。在（标签化）OK响应之前，服务器必须发送一个非标签化的、带有“IMAP4rev1”作为其功能列表之一的CAPABILITY响应。

一个以“AUTH=”开头的capability名，表示服务器支持这种特定的认证机制。所有这些名称，在定义上，都是本文档的一部分。例如，一个实验性的“blurdybloop”认证者的认证capability可以是“AUTH=XBLURDYBLOOP”，而不是“XAUTH=BLURDYBLOOP”或者“XAUTH=XBLURDYBLOOP”。

其它的capability名参考本文档的扩展版、修订版、或者改正版。更多信息参见CAPABILITY响应的文档。除非有明确的客户端动作激活capability，否则，超出本文档IMAP4rev1基本集的capabilities是不可用的。

客户端和服务器必须实现STARTTLS，LOGINDISABLED，和AUTH=PALIN（“IMAP-TLS”中有描述）的capabilities。重要信息参看安全考虑一节。

关于站点形式或者实现体特定的capability信息参看题为“客户端命令－试验/扩展”一节。

例子：

```
C: abcd CAPABILITY

S: * CAPABILITY IMAP4rev1 STARTTLS AUTH=GSSAPI

LOGINDISABLED

S: abcd OK CAPABILITY completed

C: efgh STARTTLS

S: efgh OK STARTTLS completed

<TLS negotiation, further commands are under [TLS] layer>

C: ijkl CAPABILITY

S: * CAPABILITY IMAP4rev1 AUTH=GSSAPI AUTH=PLAIN

S: ijkl OK CAPABILITY completed
```