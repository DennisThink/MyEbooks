附录
A. 标准参考
下列文档包含了有助于适当理解本文档的定义或者规范：

[ABNF] Crocker, D. and P. Overell, "Augmented BNF for
Syntax Specifications: ABNF", RFC2234,
November 1997.

[ANONYMOUS] Newman, C., "Anonymous SASL Mechanism", RFC
2245, November 1997.

[CHARSET] Freed, N. and J. Postel, "IANA Character Set
Registration Procedures", RFC2978, October
2000.

[DIGEST-MD5] Leach, P. and C. Newman, "Using Digest
Authentication as a SASL Mechanism", RFC2831,
May 2000.

[DISPOSITION] Troost, R., Dorner, S. and K. Moore,
"Communicating Presentation Information in
Internet Messages: The Content-Disposition
Header", RFC2183, August 1997.

[IMAP-TLS] Newman, C., "Using TLS with IMAP, POP3 and
ACAP", RFC2595, June 1999.

[KEYWORDS] Bradner, S., "Key words for use in RFCs to
Indicate Requirement Levels", BCP 14, RFC2119,
March 1997.

[LANGUAGE-TAGS] Alvestrand, H., "Tags for the Identification of
Languages", BCP 47, RFC3066, January 2001.

[LOCATION] Palme, J., Hopmann, A. and N. Shelness, "MIME
Encapsulation of Aggregate Documents, such as
HTML (MHTML)", RFC2557, March 1999.

[MD5] Myers, J. and M. Rose, "The Content-MD5 Header
Field", RFC1864, October 1995.

[MIME-HDRS] Moore, K., "MIME (Multipurpose Internet Mail
Extensions) Part Three: Message Header
Extensions for Non-ASCII Text", RFC2047,
November 1996.

[MIME-IMB] Freed, N. and N. Borenstein, "MIME
(Multipurpose Internet Mail Extensions) Part
One: Format of Internet Message Bodies", RFC
2045, November 1996.

[MIME-IMT] Freed, N. and N. Borenstein, "MIME
(Multipurpose Internet Mail Extensions) Part
Two: Media Types", RFC2046, November 1996.

[RFC-2822] Resnick, P., "Internet Message Format", RFC
2822, April 2001.

[SASL] Myers, J., "Simple Authentication and Security
Layer (SASL)", RFC2222, October 1997.

[TLS] Dierks, T. and C. Allen, "The TLS Protocol
Version 1.0", RFC2246, January 1999.

[UTF-7] Goldsmith, D. and M. Davis, "UTF-7: A Mail-Safe
Transformation Format of Unicode", RFC2152,
May 1997.

The following documents describe quality-of-implementation issues
that should be carefully considered when implementing this protocol:

[IMAP-IMPLEMENTATION] Leiba, B., "IMAP Implementation
Recommendations", RFC2683, September 1999.

[IMAP-MULTIACCESS] Gahrns, M., "IMAP4 Multi-Accessed Mailbox
Practice", RFC2180, July 1997.

A.1 Informative References

The following documents describe related protocols:

[IMAP-DISC] Austein, R., "Synchronization Operations for
Disconnected IMAP4 Clients", Work in Progress.

[IMAP-MODEL] Crispin, M., "Distributed Electronic Mail
Models in IMAP4", RFC1733, December 1994.

[ACAP] Newman, C. and J. Myers, "ACAP -- Application
Configuration Access Protocol", RFC2244,
November 1997.

[SMTP] Klensin, J., "Simple Mail Transfer Protocol",
STD 10, RFC2821, April 2001.

The following documents are historical or describe historical aspects
of this protocol:

[IMAP-COMPAT] Crispin, M., "IMAP4 Compatibility with
IMAP2bis", RFC2061, December 1996.

[IMAP-HISTORICAL] Crispin, M., "IMAP4 Compatibility with IMAP2
and IMAP2bis", RFC1732, December 1994.

[IMAP-OBSOLETE] Crispin, M., "Internet Message Access Protocol
- Obsolete Syntax", RFC2062, December 1996.

[IMAP2] Crispin, M., "Interactive Mail Access Protocol
- Version 2", RFC1176, August 1990.

[RFC-822] Crocker, D., "Standard for the Format of ARPA
Internet Text Messages", STD 11, RFC822,
August 1982.

[RFC-821] Postel, J., "Simple Mail Transfer Protocol",
STD 10, RFC821, August 1982.
B. 修改于 RFC2060

1) Clarify description of unique identifiers and their semantics.

2) Fix the SELECT description to clarify that UIDVALIDITY is required
in the SELECT and EXAMINE responses.

3) Added an example of a failing search.

4) Correct store-att-flags: "#flag" should be "1#flag".

5) Made search and section rules clearer.

6) Correct the STORE example.

7) Correct "BASE645" misspelling.

8) Remove extraneous close parenthesis in example of two-part message
with text and BASE64 attachment.

9) Remove obsolete "MAILBOX" response from mailbox-data.

10) A spurious "<" in the rule for mailbox-data was removed.

11) Add CRLF to continue-req.

12) Specifically exclude "]" from the atom in resp-text-code.

13) Clarify that clients and servers should adhere strictly to the
protocol syntax.

14) Emphasize in 5.2 that EXISTS can not be used to shrink a mailbox.

15) Add NEWNAME to resp-text-code.

16) Clarify that the empty string, not NIL, is used as arguments to
LIST.

17) Clarify that NIL can be returned as a hierarchy delimiter for the
empty string mailbox name argument if the mailbox namespace is flat.

18) Clarify that addr-mailbox and addr-name have RFC-2822 quoting
removed.

19) Update UTF-7 reference.

20) Fix example in 6.3.11.

21) Clarify that non-existent UIDs are ignored.

22) Update DISPOSITION reference.

23) Expand state diagram.

24) Clarify that partial fetch responses are only returned in
response to a partial fetch command.

25) Add UIDNEXT response code. Correct UIDVALIDITY definition
reference.

26) Further clarification of "can" vs. "MAY".

27) Reference RFC-2119.

28) Clarify that superfluous shifts are not permitted in modified
UTF-7.

29) Clarify that there are no implicit shifts in modified UTF-7.

30) Clarify that "INBOX" in a mailbox name is always INBOX, even if
it is given as a string.

31) Add missing open parenthesis in media-basic grammar rule.

32) Correct attribute syntax in mailbox-data.

33) Add UIDNEXT to EXAMINE responses.

34) Clarify UNSEEN, PERMANENTFLAGS, UIDVALIDITY, and UIDNEXT
responses in SELECT and EXAMINE. They are required now, but weren't
in older versions.

35) Update references with RFCnumbers.

36) Flush text-mime2.

37) Clarify that modified UTF-7 names must be case-sensitive and that
violating the convention should be avoided.

38) Correct UID FETCH example.

39) Clarify UID FETCH, UID STORE, and UID SEARCH vs. untagged EXPUNGE
responses.

40) Clarify the use of the word "convention".

41) Clarify that a command is not "in progress" until it has been
fully received (specifically, that a command is not "in progress"
during command continuation negotiation).

42) Clarify envelope defaulting.

43) Clarify that SP means one and only one space character.

44) Forbid silly states in LIST response.

45) Clarify that the ENVELOPE, INTERNALDATE, RFC822*, BODY*, and UID
for a message is static.

46) Add BADCHARSET response code.

47) Update formal syntax to [ABNF] conventions.

48) Clarify trailing hierarchy delimiter in CREATE semantics.

49) Clarify that the "blank line" is the [RFC-2822] delimiting blank
line.

50) Clarify that RENAME should also create hierarchy as needed for
the command to complete.

51) Fix body-ext-mpart to not require language if disposition
present.

52) Clarify the RFC822.HEADER response.

53) Correct missing space after charset astring in search.

54) Correct missing quote for BADCHARSET in resp-text-code.

55) Clarify that ALL, FAST, and FULL preclude any other data items
appearing.

56) Clarify semantics of reference argument in LIST.

57) Clarify that a null string for SEARCH HEADER X-FOO means any
message with a header line with a field-name of X-FOO regardless of
the text of the header.

58) Specifically reserve 8-bit mailbox names for future use as UTF-8.

59) It is not an error for the client to store a flag that is not in
the PERMANENTFLAGS list; however, the server will either ignore the
change or make the change in the 会话 only.

60) Correct/clarify the text regarding superfluous shifts.

61) Correct typographic errors in the "Changes" section.

62) Clarify that STATUS must not be used to check for new messages in
the selected mailbox

63) Clarify LSUB behavior with "%" wildcard.

64) Change AUTHORIZATION to AUTHENTICATE in section 7.5.

65) Clarify description of multipart body type.

66) Clarify that STORE FLAGS does not affect /Recent.

67) Change "west" to "east" in description of timezone.

68) Clarify that commands which break command pipelining must wait
for a completion result response.

69) Clarify that EXAMINE does not affect /Recent.

70) Make description of MIME structure consistent.

71) Clarify that date searches disregard the time and timezone of the
INTERNALDATE or Date: header. In other words, "ON 13-APR-2000" means
messages with an INTERNALDATE text which starts with "13-APR-2000",
even if timezone differential from the local timezone is sufficient
to move that INTERNALDATE into the previous or next day.

72) Clarify that the header fetches don't add a blank line if one
isn't in the [RFC-2822] message.

73) Clarify (in discussion of UIDs) that messages are immutable.

74) Add an example of CHARSET searching.

75) Clarify in SEARCH that keywords are a type of flag.

76) Clarify the mandatory nature of the SELECT data responses.

77) Add optional CAPABILITY response code in the initial OK or
PREAUTH.

78) Add note that server can send an untagged CAPABILITY command as
part of the responses to AUTHENTICATE and LOGIN.

79) Remove statement about it being unnecessary to issue a CAPABILITY
command more than once in a connection. That statement is no longer
true.

80) Clarify that untagged EXPUNGE decrements the number of messages
in the mailbox.

81) Fix definition of "body" (concatenation has tighter binding than
alternation).

82) Add a new "Special Notes to Implementors" section with reference
to [IMAP-IMPLEMENTATION].

83) Clarify that an untagged CAPABILITY response to an AUTHENTICATE
command should only be done if a security layer was not negotiated.

84) Change the definition of atom to exclude "]". Update astring to
include "]" for compatibility with the past. Remove resp-text-atom.

85) Remove NEWNAME. It can't work because mailbox names can be
literals and can include "]". Functionality can be addressed via
referrals.

86) Move modified UTF-7 rationale in order to have more logical
paragraph flow.

87) Clarify UID uniqueness guarantees with the use of MUST.

88) Note that clients should read response data until the connection
is closed instead of immediately closing on a BYE.

89) Change RFC-822 references to RFC-2822.

90) Clarify that RFC-2822 should be followed instead of RFC-822.

91) Change recommendation of optional automatic capabilities in LOGIN
and AUTHENTICATE to use the CAPABILITY response code in the tagged
OK. This is more interoperable than an unsolicited untagged
CAPABILITY response.

92) STARTTLS and AUTH=PLAIN are mandatory to implement; add
recommendations for other [SASL] mechanisms.

93) Clarify that a "connection" (as opposed to "server" or "command")
is in one of the four states.

94) Clarify that a failed or rejected command does not change state.

95) Split references between normative and informative.

96) Discuss authentication failure issues in security section.

97) Clarify that a data item is not necessarily of only one data
type.

98) Clarify that sequence ranges are independent of order.

99) Change an example to clarify that superfluous shifts in
Modified-UTF7 can not be fixed just by omitting the shift. The
entire string must be recalculated.

100) Change Envelope Structure definition since [RFC-2822] uses
"envelope" to refer to the [SMTP] envelope and not the envelope data
that appears in the [RFC-2822] header.

101) Expand on RFC822.HEADER response data vs. BODY[HEADER].

102) Clarify Logout state semantics, change ASCII art.

103) Security changes to comply with IESG requirements.

104) Add definition for body URI.

105) Break sequence range definition into three rules, with rewritten
descriptions for each.

106) Move STARTTLS and LOGINDISABLED here from [IMAP-TLS].

107) Add IANA Considerations section.

108) Clarify valid client assumptions for new message UIDs vs.
UIDNEXT.

109) Clarify that changes to permanentflags affect concurrent
会话s as well as subsequent 会话s.

110) Clarify that authenticated state can be entered by the CLOSE
command.

111) Emphasize that SELECT and EXAMINE are the exceptions to the rule
that a failing command does not change state.

112) Clarify that newly-appended messages have the Recent flag set.

113) Clarify that newly-copied messages SHOULD have the Recent flag
set.

114) Clarify that UID commands always return the UID in FETCH
responses.

C.关键词索引
+FLAGS <flag list> (store command data item)
+FLAGS.SILENT <flag list> (store command data item)
-FLAGS <flag list> (store command data item)
-FLAGS.SILENT <flag list> (store command data item)
ALERT (response code)
ALL (fetch item)
ALL (search key)
ANSWERED (search key)
APPEND (command)
AUTHENTICATE (command)
BAD (response)
BADCHARSET (response code)
BCC <string> (search key)
BEFORE <date> (search key)
BODY (fetch item)
BODY (fetch result)
BODY <string> (search key)
BODY.PEEK[<section>]<<partial>> (fetch item)
BODYSTRUCTURE (fetch item)
BODYSTRUCTURE (fetch result)
BODY[<section>]<<origin octet>> (fetch result)
BODY[<section>]<<partial>> (fetch item)
BYE (response)
Body Structure (message attribute)
CAPABILITY (command)
CAPABILITY (response code)
CAPABILITY (response)
CC <string> (search key)
CHECK (command)
CLOSE (command)
COPY (command)
CREATE (command)
DELETE (command)
DELETED (search key)
DRAFT (search key)
ENVELOPE (fetch item)
ENVELOPE (fetch result)
EXAMINE (command)
EXISTS (response)
EXPUNGE (command)
EXPUNGE (response)
Envelope Structure (message attribute)
FAST (fetch item)
FETCH (command)
FETCH (response)
FLAGGED (search key)
FLAGS (fetch item)
FLAGS (fetch result)
FLAGS (response)
FLAGS <flag list> (store command data item)
FLAGS.SILENT <flag list> (store command data item)
FROM <string> (search key)
FULL (fetch item)
Flags (message attribute)
HEADER (part specifier)
HEADER <field-name> <string> (search key)
HEADER.FIELDS <header-list> (part specifier)
HEADER.FIELDS.NOT <header-list> (part specifier)
INTERNALDATE (fetch item)
INTERNALDATE (fetch result)
Internal Date (message attribute)
KEYWORD <flag> (search key)
Keyword (type of flag)
LARGER <n> (search key)
LIST (command)
LIST (response)
LOGIN (command)
LOGOUT (command)
LSUB (command)
LSUB (response)
MAY (specification requirement term)
MESSAGES (status item)
MIME (part specifier)
MUST (specification requirement term)
MUST NOT (specification requirement term)
Message Sequence Number (message attribute)
NEW (search key)
NO (response)
NOOP (command)
NOT <search-key> (search key)
OK (response)
OLD (search key)
ON <date> (search key)
OPTIONAL (specification requirement term)
OR <search-key1> <search-key2> (search key)
PARSE (response code)
PERMANENTFLAGS (response code)
PREAUTH (response)
Permanent Flag (class of flag)
READ-ONLY (response code)
READ-WRITE (response code)
RECENT (response)
RECENT (search key)
RECENT (status item)
RENAME (command)
REQUIRED (specification requirement term)
RFC822 (fetch item)
RFC822 (fetch result)
RFC822.HEADER (fetch item)
RFC822.HEADER (fetch result)
RFC822.SIZE (fetch item)
RFC822.SIZE (fetch result)
RFC822.TEXT (fetch item)
RFC822.TEXT (fetch result)
SEARCH (command)
SEARCH (response)
SEEN (search key)
SELECT (command)
SENTBEFORE <date> (search key)
SENTON <date> (search key)
SENTSINCE <date> (search key)
SHOULD (specification requirement term)
SHOULD NOT (specification requirement term)
SINCE <date> (search key)
SMALLER <n> (search key)
STARTTLS (command)
STATUS (command)
STATUS (response)
STORE (command)
SUBJECT <string> (search key)
SUBSCRIBE (command)
会话 Flag (class of flag)
System Flag (type of flag)
TEXT (part specifier)
TEXT <string> (search key)
TO <string> (search key)
TRYCREATE (response code)
UID (command)
UID (fetch item)
UID (fetch result)
UID <sequence set> (search key)
UIDNEXT (response code)
UIDNEXT (status item)
UIDVALIDITY (response code)
UIDVALIDITY (status item)
UNANSWERED (search key)
UNDELETED (search key)
UNDRAFT (search key)
UNFLAGGED (search key)
UNKEYWORD <flag> (search key)
UNSEEN (response code)
UNSEEN (search key)
UNSEEN (status item)
UNSUBSCRIBE (command)
Unique Identifier (UID) (message attribute)
X<atom> (command)
[RFC-2822] Size (message attribute)
/Answered (system flag)
/Deleted (system flag)
/Draft (system flag)
/Flagged (system flag)
/Marked (mailbox name attribute)
/Noinferiors (mailbox name attribute)
/Noselect (mailbox name attribute)
/Recent (system flag)
/Seen (system flag)
/Unmarked (mailbox name attribute)

作者地址
Mark R. Crispin
Networks and Distributed Computing
University of Washington
4545 15th Avenue NE
Seattle, WA 98105-4527
Phone: (206) 543-5762
EMail: MRC@CAC.Washington.EDU
完整版权声明
Copyright (C) The Internet Society (2003). All Rights Reserved.


（以下是版权声明的英文原文）


This document and translations of it may be copied and furnished to
others, and derivative works that comment on or otherwise explain it
or assist in its implementation may be prepared, copied, published
and distributed, in whole or in part, without restriction of any
kind, provided that the above copyright notice and this paragraph are
included on all such copies and derivative works. However, this
document itself may not be modified in any way, such as by removing
the copyright notice or references to the Internet Society or other
Internet organizations, except as needed for the purpose of
developing Internet standards in which case the procedures for
copyrights defined in the Internet Standards process must be
followed, or as required to translate it into languages other than
English.

The limited permissions granted above are perpetual and will not be
revoked by the Internet Society or its successors or assigns. v This
document and the information contained herein is provided on an "AS
IS" basis and THE INTERNET SOCIETY AND THE INTERNET ENGINEERING TASK
FORCE DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO ANY WARRANTY THAT THE USE OF THE INFORMATION HEREIN WILL
NOT INFRINGE ANY RIGHTS OR ANY IMPLIED WARRANTIES OF MERCHANTABILITY
OR FITNESS FOR A PARTICULAR PURPOSE.


（以下是版权声明的译文）


倘若以上的版权声明和本段被包含进所有拷贝和派生作品中，那么，全部或者部分的，没有任何形式的限制，本文档和它的翻译版可以被复制和提供给其它人；评论它、或者解析它、或者帮助它实现的派生作品可以编制，复制，出版和分发。但是，本文档不能有任何形式的修改，如，删除该版权声明，或者指向网络聚合或者其它网络组织，除非出于发展网络标准的意图的需要――这种情况下定义于网络标准处理的版权程序必须遵守，或者需要将它翻译成英语以外的语言。

以上有限授权是永久的，且不会被网络聚合、或者其后来者、或者分配者废除。本文档及包含在这里的声明在“AS IS”的基本原则下提供，网络聚合和网络工程作业力量放弃所有授权，显式或者隐式地，包括但不仅限于任何授权――在这里的声明不会破坏任何权利或者任何隐式的商业授权或者一个特殊意图。

感谢
　　RECEditor功能的基金目前由网络聚合提供。