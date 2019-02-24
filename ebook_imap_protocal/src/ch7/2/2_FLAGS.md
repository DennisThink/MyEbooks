FLAGS响应
内容：
标记组合列表

FLAGS响应作为一个SELECT或者EXAMINE命令的一个结果发生。标记组合列表确定适用于该邮箱的标记（至少，系统定义的标记）。系统标记以外的标记也可以存在，这取决于服务器实现体。

来自FLAGS响应的更新必须被客户端记录。

例子：
```
S: * FLAGS (/Answered /Flagged /Deleted /Seen /Draft)
```