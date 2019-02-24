UNSUBSCRIBE命令
参数：                         
邮箱名

响应：                         
此命令无需特定响应

结果：                         
OK－unsubscribe完成

NO－unsubscribe失败：不能取消订阅该邮箱名

BAD－未知命令，无效参数

UNSUBSCRIBE从服务器的活动邮箱序列或者订阅邮箱序列中删除特定邮箱名，通过LSUB命令返回。当且仅当取消订阅成功时，该命令返回一个标签化的OK响应。

例子：                         

```
C: A002 UNSUBSCRIBE #news.comp.mail.mime

S: A002 OK UNSUBSCRIBE completed
```