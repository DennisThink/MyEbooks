BAD响应
内容：
OPTIONAL响应码，可读文本

BAD响应指明来自服务器的一个错误。其标签化时，它报告客户端命令的一个协议级的错误；标签指明导致该错误的命令。其非标签化形式指明关联命令不能抉择的一个协议级错误；它也指明一个内部服务器失败。可读文本描述了这种情况。

例子：
```
C: ...very long command line...
S: * BAD Command line too long
C: ...empty line...
S: * BAD Empty command line
C: A443 EXPUNGE
S: * BAD Disk crash, attempting salvage to a new disk!
S: * OK Salvage successful, no data lost
S: A443 OK Expunge completed
```