# Summary

* [Introduction](README.md)
* [Ref](Reference.md)
* [第一章 如何阅读本书](ch1/README.md)
  * [第一节 本书的结构](ch1/1.md)
  * [第二节 本书的约定语](ch1/2.md)
  * [第三节 实现者需要注意的地方](ch1/3.md)
* [第二章 协议概述](ch2/README.md)
  * [第一节 链路层](ch2/1.md)
  * [第二节 命令以及响应](ch2/2.md)
  * [第三节 邮件属性](ch2/3.md)
    * [1](ch2/3_1.md)
    * [2](ch2/3_2.md)
    * [3](ch2/3_3.md) 
  
* [第三章 状态和流程图](ch3/README.md)
  * [第一节 未认证状态](ch3/1.md)
  * [第二节 认证状态](ch3/2.md)
  * [第三节 选中状态](ch3/3.md)
  * [第四节 注销状态](ch4/4.md)

* [第四章 数据格式](ch4/README.md)
  * [第一节 原语](ch4/1.md)
  * [第二节 数字](ch4/2.md)
  * [第三节 字符串](ch4/3.md)
    * [1 字节及二进制字符串](ch4/3_1.md)
  * [第四节 圆括符列表](ch4/4.md)
  * [第五节 NIL](ch4/5.md)

* [第五章 操作的考虑](ch5/README.md)
  * [第一节 邮箱命名](ch5/1.md)
    * [1 邮箱层级命名](ch5/1_1.md)
    * [2 邮箱命名空间的约定](ch5/1_2.md)
    * [3 邮箱的国际命名约定](ch5/1_3.md)
  * [第二节 邮箱大小和邮件状态更新](ch5/2.md)
  * [第三节 没有命令在行进中的响应](ch5/3.md)
  * [第四节 自动注销计时器](ch5/4.md)
  * [第五节 多个命令在行进中](ch5/5.md)

* [第六章 客户端命令](ch6/README.md)
  * [第一节 客户端命令－任意状态](ch6/1.md) 
    * [1 CAPABILITY命令](ch6/1/1_CAPABILITY.md)
    * [2 NOOP命令](ch6/1/1_NOOP.md)
    * [3 LOGOUT命令](ch6/1/1_LOGOUT.md)
  * [第二节 客户端命令－未认证状态](ch6/2.md)
    * [1 STARTTLS命令](ch6/2/2_STARTTLS.md)
    * [2 AUTHENTICATE命令](ch6/2/2_AUTHENTICATE.md)
    * [3 LOGIN命令](ch6/2/2_LOGIN.md)
  * [第三节 客户端命令－认证状态](ch6/3.md)
    * [1 SELECT命令](ch6/3/3_SELECT.md)
    * [2 EXAMINE命令](ch6/3/3_EXAMINE.md)
    * [3 CREATE命令](ch6/3/3_CREATE.md)
    * [4 DELETE命令](ch6/3/3_DELETE.md)
    * [5 RENAME命令](ch6/3/3_RENAME.md)
    * [6 SUBSCRIBE命令](ch6/3/3_SUBSCRIBE.md)
    * [7 UNSUBSCRIBE命令](ch6/3/3_UNSUBSCRIBE.md)
    * [8 LIST命令](ch6/3/3_LIST.md)
    * [9 LSUB命令](ch6/3/3_LSUB.md)
    * [10 STATUS命令](ch6/3/3_STATUS.md)
    * [11 APPEND命令](ch6/3/3_APPEND.md)
  * [第四节 客户端命令－被选中状态](ch6/4.md)
    * [1 CHECK命令](ch6/4/4_CHECK.md)
    * [2 CLOSE命令](ch6/4/4_CLOSE.md)
    * [3 EXPUNGE命令](ch6/4/4_EXPUNGE.md)
    * [4 SEARCH命令](ch6/4/4_SEARCH.md)
    * [5 FETCH命令](ch6/4/4_FETCH.md)
    * [6 STORE命令](ch6/4/4_STORE.md)
    * [7 COPY命令](ch6/4/4_COPY.md)
    * [8 UID命令](ch6/4/4_UID.md)
  * [第五节 客户端命令－试验/扩展](ch6/5.md)
    * [X<atom>命令]

* [第七章 服务器响应](ch7/README.md)
  * [第一节 服务器响应－状态响应](ch7/1.md)
    * [OK响应]
    * [NO响应]
    * [PREAUTH响应]
    * [BYE响应]
  * [第二节 服务器响应－服务器和邮箱状态](ch7/2.md)
    * [CAPABILITY响应]
    * [LIST响应]
    * [LSUB响应]
    * [STATUS响应]
    * [SEARCH响应]
    * [FLAGS响应]
  * [第三节 服务器响应－邮箱大小](ch7/3.md)
    * [EXISTS响应]
    * [RECENT响应]
  * [第四节 服务器响应－邮件状态](ch7/4.md)
    * [EXPUNGE响应]
    * [FETCH响应]
  * [第五节 服务器响应－命令连续请求](ch7/5.md)

* [第八章 IMAP4rev1连接例子](ch8/README.md)

* [第九章 正式语法](ch9/README.md)
* [第十章 作者的说明](ch10/README.md)
* [第十一章 安全考虑](ch11/README.md)
  * [STARTTLS安全考虑]
  * [其它安全考虑]
  
* [IANA考虑](ch12/README.md)
* [附录]
  * [标准参考]
  * [关键词索引]
* [作者地址]
* [感谢]


