SUBSCRIBE命令
参数：                         
邮箱

响应：                         
此命令无需特定

结果：                         
OK－subscribe完成

NO－subscribe失败：不能订阅这个邮箱名

BAD－未知命令，或者无效参数

SUBSCRIBE命令增加指定邮箱名至服务器的活动邮箱序列或者订阅邮箱序列中，通过LSUB命令返回。当且仅当订阅成功时，该命令返回一个标签化的OK响应。

服务器可以向SUBSCRIBE证实邮箱参数以确保它的存在。但是，它不能单方面从订阅列表中删除一个存在的邮箱名，即使该邮箱名不存在了。

注意：这个需求是出于，一个服务器可以选择，在一个邮箱名众所周知的邮箱的内容过期后，常规地删除该邮箱（比如，“system-alerts”），以便在新的内容匹配时重新创建它。

例子：                         

```
C: A002 SUBSCRIBE #news.comp.mail.mime

S: A002 OK SUBSCRIBE completed
```