APPEND命令
**参数**：
邮箱名，OPTIONAL位的组合列表，OPTIONAL日期/时间串，邮件原义

**响应**：
此命令无特定响应

**结果**：
OK－append完成
NO－append错误：不能添加到该邮箱，标记、或者日期/时间、或者邮件文本有错误
BAD－未知命令，或者无效参数

APPEND命令将原义参数像一个新邮件一样添加到指定的目标邮箱末尾。这个参数应当是一个[RFC-2822]邮件的格式。邮件中允许8位字符串。一个不能正确保存8位数据的服务器执行体必须能够用一个[MIME-IMB]内容转换编码，进行8位APPEND数据与7位（APPEND数据）之间的可逆转换。

注意：可能有例外，比如，草稿邮件――其中被请求的[RFC-2822]头在APPEND的邮件原义参数中被省略了。这样做的整个关联必须被理解并小心权衡。

如果一个组合列表被声明，则标记位应当在结果邮件中被设置；否则，结果邮件的标记列表默认设置为空。两种情况下，Recent标记都要设置。

如果声明了一个日期－时间，实际日期应当在结果邮件中被设置；否则，结果邮件的实际日期默认设置为当前日期和时间。

如果插入操作因为某种原因不能成功，邮箱必须恢复至APPEND尝试前的状态；不允许局部的插入操作。

如果目标邮箱不存在，服务器必须返回一个错误，且不能自动创建邮箱。除非确定目标邮箱不能被创建，否则，服务器必须发送响应码“[TRYCREATE]”作为标签化NO响应的文本的前缀。这给客户端一个暗示，即它可以尝试一个CREATE命令，并且，如果CREATE成功，还可以重试APPEND。

如果邮箱当前被选中，正常的新邮件动作应当发生。特别地，服务器应当通过一个非标签化的EXISTS响应迅速通知客户端。如果服务器不这样做，客户端可以在一个或者多个APPEND命令之后发出一个NOOP命令（或者，NOOP命令失败，发出一个CHECK命令）。

**例子**：
```
C: A003 APPEND saved-messages (/Seen) {310}
S: + Ready for literal data
C: Date: Mon, 7 Feb 1994 21:52:25 -0800 (PST)
C: From: Fred Foobar foobar@Blurdybloop.COM
C: Subject: afternoon meeting
C: To: mooch@owatagu.siam.edu
C: Message-Id: B27397-0100000@Blurdybloop.COM
C: MIME-Version: 1.0
C: Content-Type: TEXT/PLAIN; CHARSET=US-ASCII
C: 
C: Hello Joe, do you think we can meet at 3:30 tomorrow?
C: 
S: A003 OK APPEND completed
```

注意：APPEND命令不用于邮件发送，因为它不支持转换[SMTP]信封信息的机制。