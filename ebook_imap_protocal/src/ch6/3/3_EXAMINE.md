EXAMINE命令

**参数：**                                                                    
邮箱名

**响应：**                                                                   
要求非标签化响应：FLAGS，EXISTS，RECENT

要求OK非标签化响应：UNSEEN，PERMANENTFLAGS，UIDNEXT，UIDVALIDITY

**结果：**                                                                     
OK－examine完成，当前是选中状态

NO－examine失败，当前是认证状态：没有这个邮箱，不能访问邮箱

BAD－未知命令，或者无效参数

EXAMINE命令与SELECT相同，并返回同样的输出；不过，只读方式时选中的邮箱是一样的。邮箱的永久状态下，没有变动，包括有基于用户的状态的权限；特别的，EXAMINE不能使邮件丢失/Recent标记。

EXAMINE命令的标签化OK响应文本必须以“[READ-ONLY]”开头。

**例子：**                                                                    
```
C: A932 EXAMINE blurdybloop

S: * 17 EXISTS

S: * 2 RECENT

S: * OK [UNSEEN 8] Message 8 is first unseen

S: * OK [UIDVALIDITY 3857529045] UIDs valid

S: * OK [UIDNEXT 4392] Predicted next UID

S: * FLAGS (/Answered /Flagged /Deleted /Seen /Draft)

S: * OK [PERMANENTFLAGS ()] No permanent flags permitted

S: A932 OK [READ-ONLY] EXAMINE completed
```