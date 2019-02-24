EXPUNGE命令

参数：                         
无

响应：                         
非标签化响应：EXPUNGE

结果：                         
OK－expunge完成
NO－expunge失败：不能删除（例如，没有权限）
BAD－未知命令，或者无效参数

EXPUNGE命令从当前被选中邮箱中永久删除带有/Delted标记位的所有邮件。在返回一个OK到客户端前，每个被删除的的邮件会引发一个非标签化的EXPUNGE响应被发送。

例子：                         

```
C: A202 EXPUNGE
S: * 3 EXPUNGE
S: * 3 EXPUNGE
S: * 5 EXPUNGE
S: * 8 EXPUNGE
S: A202 OK EXPUNGE complted
```

注意：在这个例子中，邮件３，４，７，及１１带/Deleted标记位。进一步的解释参看EXPUNGE响应的描述。
