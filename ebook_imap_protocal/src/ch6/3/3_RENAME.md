RENAME命令

参数：              
已经存在的邮箱名

新的邮箱名

响应：              
此命令无需特定响应

结果：
OK－rename完成

NO－rename失败：不能重命名邮箱为这个名称，不能以这个名称重命名至邮箱

BAD－未知命令，或者无效参数

RENAME命令改变一个邮箱的名称。当且仅当邮箱被重命名完成时，才返回一个标签化的OK响应。尝试把一个不存在的邮箱名重命名至一个已经存在的邮箱名，是错误的。重命名中的任何错误都将返回一个标签化的NO响应。

如果名称有子级名，（当重命名这个名称时）则子级名必须也被重命名。例如，重命名“foo”为“zap”，将重命名“foo/bar”（假设“/”是层级定义符）为“zap/bar”。

如果服务器层级分隔符出现在名称中，那么服务器应当创建RENAME命令成功完成所需要的每一个父级名。即，尝试在一个以“/”为层级分隔符的服务器上重命名“foo/bar/zap”为baz/rag/zowie，如果baz/和baz/rag/不存在，则应当创建它们。

旧邮箱使用的最高唯一标识符的值必须保留，这样一个新创建的同名邮箱就不会再使用先前引用的标识符，除非这个新的引用有一个不同的唯一标识符值。更多细节参看UID命令的描述。

重命名INBOX是允许的，并且有特殊的行为。它移动INBOX中的所有邮件至一个给定名称的新邮箱中，INBOX则为空。如果服务器实现体支持INBOX的子级名，则这些不受INBOX重命名的影响。

例子：

C: A682 LIST “” *

S: * LIST () “/” blurdybloop

S: * LIST (/Noselect) “/” foo

S: * LIST () “/” foo/bar

S: A682 OK LIST completed

C: A683 RENAME blurdybloop sarasoop

S: A683 OK RENAME completed

C: A684 RENAME foo zowie

S: A684 OK RENAME Completed

C: A685 LIST “” *

S: * LIST () “/” sarasoop

S: * LIST (/Noselect) “/” zowie

S: * LIST () “/” zowie/bar

S: A685 OK LIST completed


C: Z432 LIST “” *

S: * LIST () “.” INBOX

S: * LIST () “.” INBOX.bar

S: Z432 OK LIST completed

C: Z433 RENAME INBOX old-mail

S: Z433 OK RENAME completed

C: Z434 LIST “” *

S: * LIST () “.” INBOX

S: * LIST () “.” INBOX.bar

S: * LIST () “.” old-mail

S: Z434 OK LIST completed