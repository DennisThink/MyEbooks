PREAUTH响应
内容：
OPTIONAL响应码，可读文本

PREAUTH响应永远是非标签化的，且是连接启动时三种可能欢迎中的一种。它指明连接已经通过外部手段认证了；因而不需要LOGIN命令。

例子：

```
S: * PREAUTH IMAP4rev1 server logged in as Smith
```