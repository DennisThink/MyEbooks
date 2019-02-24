EXISTS响应
内容：
无

EXISTS响应报告邮箱中的邮箱数量。这个响应作为一个SELECT或者EXAMINE命令，及邮箱大小是否改变的一个结果发生（例如，新邮件）。

来自EXISTS响应的更新必须被客户端记录。

例子：
```
S: * 23 EXISTS
```