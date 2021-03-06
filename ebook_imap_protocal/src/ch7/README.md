服务器响应
　　服务器响应有三种形式：状态响应，服务器数据，及命令连续请求。一个服务器响应中的信息，在下面的响应描述中定义的“内容：”，通过功能，而不是语法来描述。服务器响应的精确语法在正式语法一节中有描述。

客户端必须一直准备着接收任何响应。

状态响应可以是标签化或者非标签化的。标签化的状态响应表示一个客户端命令的完成结果（OK，NO，或者BAD状态），并且有一个与该命令匹配的标签。

某些状态响应，及所有的服务器数据，是非标签化的。一个非标签化的响应用一个“*”记号而不是一个标签来表示。非标签化的状态响应表示服务器欢迎，或者那些不表示一个命令完成的服务器状态（例如，一个紧急系统关机警告）。因为历史原因，非标签化服务器数据响应也被称为“主动提供的数据”，虽然严格地讲，只有单方面服务器数据是真正的“主动提供的数据”。

某些服务器数据，当客户端接收到它们的时候，必须被记录下来；它被记到那些数据的描述里。这些数据承载着影响到所有后来的命令和响应的解释的紧急信息（例如，创建或者销毁邮件相关的更新）。

其它的服务器数据应当记录以便以后参考；如果客户端不需要记录这些数据，或者没有明显的意图要记录这些数据（例如，没有其它SEARCH命令在行进中时的一个SEARCH响应），那么就应当忽略这些数据。

当IMAP连接在选中状态时，单方面的、非标签化的服务器数据的一个例子就发生了。在选中状态，服务器确认邮箱的新邮件，这作为命令执行的一部分。通常，这是任何一个命令的执行的一部分；因此，一个NOOP命令就可以确认新邮件。如果发现新邮件，服务器发送非标签化的、反映邮箱的新大小的EXISTS和RECENT响应。经常有不同的连接至相同邮箱的服务器实现体，如果另外的代理改变任意邮件标记的状态或者删除任意邮件，它也应当发送适当的、单方面的、非标签化FETCH和EXPUNGE响应。

命令的连续请求响应使用标记“+”取代一个标签。这些响应由服务器发送，以确信一个不完整的客户端命令和命令的剩余部分的准备就绪