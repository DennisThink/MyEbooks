DELETE命令
**参数**：                                                      
邮箱名

**响应**：                                                      
此命令无需特定响应

**结果**：                                                      
OK－delete完成

NO－delete失败：不能删除这个名称的邮箱

BAD－未知命令，或者无效参数

DELETE命令永久删除给定名称的邮箱。若邮箱被删除，则返回一个标签化的OK响应。尝试删除INBOX，或者一个不存在的邮箱，是错误的。

DELETE命令不能删除子级。例如，如果一个邮箱有一个子级“foo.bar”（假设“.”是层级定义符），删除“foo”不能删除“foo.bar”。尝试删除一个带有子级、并且有/Noselect属性的邮箱名，是错误的（更多细节参看LIST响应的描述）。

删除一个带有子级、并且没有/Noselect属性的邮箱名，是允许的。这种情况下，这个邮箱中的所有邮件被删除，且这个邮箱名将取得/Noselect邮箱名属性。

删除了的邮箱使用的最高唯一标识符的值必须保留，这样一个新创建的同名邮箱就不会再使用先前引用的标识符，除非这个新的引用有一个不同的唯一标识符值。更多细节参看UID命令的描述。

**例子**：

```
C: A682 LIST “” *

S: * LIST () “/” blurdybloop

S: * LIST (/Noselect) “/” foo

S: * LIST () “/” foo/bar

S: A682 OK LIST completed

C: A683 DELETE blurdybloop

S: A683 OK DELETE completed

C: A684 DELTE foo

S: A684 NO Name “foo” has inferior hierarchical names

C: A685 DELETE foo/bar

S: A685 OK DELETE Completed

C: A686 LIST “” *

S: * LIST (/Noselect) “/” foo

S: A686 OK LIST completed

C: A687 DELETE foo

S: A687 OK DELETE Completed


C: A82 LIST “” *

S: * LIST () “.” Blurdybloop

S: * LIST () “.” Foo

S: * LIST () “.” Foo.bar

S: A82 OK LIST completed

C: A83 DELETE blurdybloop

S: A83 OK DELETE completed

C: A84 DELETE foo

S: A84 OK DELETE Completed

C: A85 LIST “” *

S: * LIST () “.” foo.bar

S: A85 OK LIST completed

C: A86 LIST “” %

S: * LIST (/Noselect) “.” foo

S: A86 OK LIST completed
```
