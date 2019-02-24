OK 响应
内容：OPTIONAL响应码，可读文本

OK响应指明来自服务器的一个信息邮件。其标签化时，它指明关联命令的成功完成。可读文本可能作为一个信息邮件展现给用户。其非标签化形式指明一个纯信息的邮件；信息的各类可能通过一个响应码来指明。

其非标签化形式也用于连接启动时的三个可能欢迎中的一个。它指明该连接是未认证的，且需要一个LOGIN命令。

例子：
```
S: * OK IMAP4rev1 server ready

C: A001 LOGIN fred blurdybloop

S: * OK [ALERT] System shutdown in 10 minutes

S: A001 OK LOGIN Completed
```
