---
layout: post
title: "一行命令搞定/usr/bin/perl^M: bad interpreter"
date:   2015-03-21
comments: true
categories: Perl
---

在*nix系统下使用Perl脚本有时会遇到如下错误：
    
`/usr/bin/perl^M: bad interpreter: No such file or directory`

最常见的原因是因为该脚本在windows系统下进行了编辑。windows系统下的换行符是`\r\n`，而unix下面是只有`\n`的。如果要解决这个问题，只要去掉`\r`即可。

第一种解决方案是用sed（假设出问题的脚本名叫`filename`）：

`sed -i 's/\r$//' filename`

这种解决方案适合简单的ASCII文件形式。如果情况再复杂些，比方说filename是Unicode文件，可能会引入了Unicode中某些新的换行符；另外有时候\r和\n在某些系统上对应的字符编码并不一致。如果再碰上垂直制表符 0x0B 和进纸符 0x0C 就更麻烦了。好在Perl提供了另一种解决方案：
 
`perl -p -i -e "s/\R/\n/g" filename`

这里用到了从Perl 5.10开始引入的\R这个字符组，用来匹配各种换行符，我们只要方便地将其替换为\n就可以了。同时也没有必要用脚本文件来实现，只需要在shell里执行这样一行命令就行了。其中-p表示逐行对filename进行操作，-i表示原地操作，覆盖原始文件，-e则是表示执行后面的语句（这三个参数刚好构成了“pie”，派，很好记）。

