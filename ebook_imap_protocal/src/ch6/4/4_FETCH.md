FETCH命令

参数：                         
序列集，邮件数据项名称或者宏

响应：                         
非标签化响应：FETCH

结果：                         
OK－fetch完成
NO－fetch错误：不能获取该数据
BAD－未知命令，或者无效参数

FETCH命令获取邮箱中的一个邮件的相关数据。被获取的数据项可以是一个原语，或者一个组合列表。

在正式语法中基于msg-att-static规则确认的大部分数据项，是静态的，并且不能因为任意特定邮件而改变。在正式语法中msg-att-static规则确认的其它数据项，可以改变，或者作为一个STORE命令的一个结果，或者因为外部事件。

例如，如果一个客户端接收到它已经知道的、一个邮件的一个信封，它可以安全地忽略新传送的信封。

有三种宏，它们指明数据项的普遍使用集，并能代替数据项使用。一个宏必须被自身所用，并且不能与其它宏或者数据项连接。


> ALL

等效于：(FLAGS INTERNALDATE RFC822.SIZE ENVELOPE)

> FAST

等效于：(FLAGS INTERNALDATE RFC822.SIZE)


> FULL

等效于：(FLAGS INTERNALDATE RFC822.SIZE ENVELOPE BODY)


现在已经定义的、可以被获取的数据项有：


> BODY

BODYSTRUCTURE的不可扩展形式。


BODY[<section>]<<partial>>

特定主体块的文本。块声明是一个零的集合，或者根据时间分隔开的更多块声明。一个块声明或者是一个块号，或者是以下的一个：HEADER，HEADER.FIELDS，HEADER.FIELDS.NOT，MIME，及TEXT。一个空的块声明指向整个邮件，包括头部。

每个邮件有至少一个块号。Non-[MIME-IMB]邮件，及不带内嵌邮件的non-multipart[MIME-IMB]邮件，只有一个块１。

邮件簇被分配连续的块号，如果它们出现在邮件中。如果一个特定块的类型是邮件或者邮件簇，则这个块后面必须跟着它在块簇中的块号的时间。

一个类型为MEEAGE/RFC822类型的块也有块号，指向MESSAGE块域的块集。

HEADER，HEADER.FIELDS，HEADER.FIELDS.NOT，及TEXT块声明可能是单个块声明，也可能是以一个或者多个数字型的块声明为前缀――其前提是该数字型的块声明指向一个MESSAGE/RFC822类型的块。MIME块声明必须以一个或者多个数字型的块声明为前缀。

HEADER，HEADER.FIELDS，及HEADER.FIELDS.NOT块声明指向邮件的[RFC-2822]头部，或者一个内嵌[MIME-IMT] MESSAGE/RFC822邮件。HEADER.FIELDS和HEADER.FIELDS.NOT其后跟着field-name（[RFC-2822]中有定义）名称的一个列表，并返回头部的一个子集。HEADER.FIELDS返回的子集只包括那些带有与列表中的名称之一相符的一个field-name的头部域；类似地，HEADER.FIELDS.NOT返回的子集只包含带有一个不匹配域名称的头部域。域匹配是不区分大小写的，除非用别的方法强制。子集化并不把[RFC-2822]定义的、头部和主体之间的空行排除在外；空行包含在所有头部获得中，除非一个邮件没有主体也没有空行。

MIME块声明指向该块的[MIME-IMB]头部。

TEXT块声明指向邮件的文本主体，不包括[RFC-2822]头部。

这是一个带有它的一些块声明的复杂邮件的一个例子：

HEADER ([RFC-2822] header of the message)

TEXT ([RFC-2822] text body of the message) MULTIPART/MIXID

1 TEXT/PLAIN

2 APPLICATION/OCTET-STREAM

3 MESSAGE/RFC2822

3.HEADER ([RFC-2822] header of the message)

3.TEXT ([RFC-2822] text body of the message) MULTIPART/MIXED

3.1 TEXT/PLAIN

3.2 APPLICATION/OCTET-STREAM

4 MULTIPART/MIXED

4.1 IMAGE/GIF

4.1.MIME ([MIME-IMB] header for the IMAGE/GIF)

4.2 MESSAGE/RFC822

4.2.HEADER ([RFC-2822] header of the message)

4.2.TEXT ([RFC-2822] text body of the message) MULTIPART/MIXID

4.2.1 TEXT/PLAIN

4.2.2 MULTIPART/ALTERNATIVE

4.2.2.1 TEXT/PLAIN

4.2.2.2 TEXT/RICHTEXT

获取指定文本的一个子串是可能的。这是通过添加一个开的角符（“〈”），请求的第一个字节位置，一个时间，请求的字节的最大数，及一个闭的角符（“〉”）到块声明，来实现的。如果起始字节超出了文本的末尾，则返回一个空的字符串。

试图读取超出文本末尾内容的任何局部获取都会被适当截断。从第０字节开始的一个局部获取都返回局部获取，即使这种截断发生。

注意：这意味着一个1500字节的邮件的BODY[]<0.2048>将返回带有一个大小１５００的原义的BODY[]<0>，而不是BODY[]。

注意：一个HEADER.FIELDS或者HEADER.FIELDS.NOT块声明的一个子串获取，在子集化头部之后计算。

/Seen标记是隐含标记；如果这导致标记改变，它们应当作为FETCH响应的一部分被包含进来。


BODY.PEEK[<section>]<<partial>>

BODY[<section>]的一个替代形式，它不会暗暗设置/Seen标记。


BODYSTRUCTURE

邮件的[MIME-IMB]主体结构。它的计算是由服务器把[MIME-IMB]头部域解释为[RFC-2822]头部和[MIME-IMB]头部。


ENVELOPE

邮件的信封结构。它的计算是由服务器把[RFC-2822]头部解释为组件块，默认为所需要的多个域。


FLASG

为该邮件设置的标记。


INTERNALDATE

邮件的实际日期。


RFC822

功能上等效于BODY[]，不同的是，其结果的非标签化FETCH数据（返回RFC822）的语法。


RFC822.HEADER

功能上等效于BODY.PEEK[HEADER]，不同的是，其结果的非标签化FETCH数据（返回RFC822.HEADER）的语法。


RFC822.SIZE

邮件的[RFC-2822]大小。


RFC822.TEXT

功能上等效于BODY[TEXT]，不同的是，其结果的非标签化FETCH数据（返回RFC822.TEXT）的语法。


UID

邮件的唯一标识符。


例子：                         

```
C: A654 FETCH 2:4 (FLAGS BODY[HEADER.FIELDS (DATE FROM)])

S: * 2 FETCH ….

S: * 3 FETCH ….

S: * 4 FETCH ….

S: A654 OK FETCH completed
```
