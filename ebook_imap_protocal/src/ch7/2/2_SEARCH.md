SEARCH响应
内容：
０个或者更多个数字

SEARCH响应作为一个SEARCH或者UID SEARCH命令的一个结果发生。这些数字指向那些符合检索标准的邮件。对SEARCH，这些是邮件序列号；对UID SEARCH，这些是唯一标识符。每个数字被一个空格分开。

例子：
```
S: * SEARCH 2 3 6
```