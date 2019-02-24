CAPABILITY响应
内容：
capability列表

CAPABILITY响应作为一个CAPABILITY命令的一个结果发生。capability列表包含一个用空格分隔的、服务器支持的功能列表。功能列表必须包含原语“IMAP4rev1”。

另外，客户端和服务器实现体必须实现STARTTLS，LOGINDISABLED，及AUTH=PLAIN（描述于[IMAP-TLS]）功能。重要信息参看安全考虑一节。

以“AUTH=”开头的一个功能名表明服务器支持这种特别的认证机制。

LOGINDISABLED功能表明LOGIN命令是不可用的，并且，即使用户名和密码是正确的，服务器也将会以一个标签化的NO响应作为使用LOGIN命令的任何尝试的响应。如果服务器宣告LOGINDISABLED功能，那么一个IMAP客户端就不能发送LOGIN命令。

其它的功能名表明服务器支持IMAP4rev1协议的一个扩展，修订版，或者改善版。服务器响应必须遵守本文档，直至客户端发送一个使用关联功能的命令。

功能名必须以“X”开头，或者是标准的，或者是标准的IMAP4rev1扩展，修订版，或者在IANA注册的改善版。一个服务器不能提供未注册的，或者非标准的功能名，除非这些名称以“X”为前缀。

客户端不应当请求“IMAP4rev１”以外的任何功能名，而且必须忽略任何未知的功能名。

通过在初始PREAUTH时使用一个CAPABILITY响应码，或者使用OK响应，通过发送标签化的OK响应中的一个更新的CAPABILITY响应作为一个成功认证的一部分，服务器就可以自动地发送功能。如果客户端识别出了这些自动的功能，它就没必要发送一个单独的CAPABILITY命令。

例子：
```
S: * CAPABILITY　IMAP4rev1 STARTTLS AUTH=GSSAPI XPIG-LATIN
```