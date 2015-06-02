---
layout: post
title: "一个Perl文件句柄引用的例子"
date:   2015-04-08
comments: true
categories: Perl
---

分享一个之前在chinaunix的Perl板块上回答的问题，题主提供了一个空格分隔的多列文件，希望能够按照第二列的内容来把整个文件分割成多个小文件。

![Image](http://life.chinaunix.net/bbsfile/forum/201405/06/214614aw64qupoexxrr16p.png)

代码：

{% highlight perl %}
my @fh;

open my $src, '<', 'sourcefile' or die "CAN'T READ\n";

while (my $num = (split /\s+/, (my $thisline = <$src>) )[1]){
        my $destfh = 'filtered'.$num;
        open $$destfh, '>>', "$destfh" or die "CAN'T WRITE $destfh\n", $fh[$num] = 1 unless defined $fh[$num];
        print {$$destfh} $thisline;
}

for(0..$#fh){
        my $destfh = 'filtered'.$_, close($$destfh) if defined $fh[$_];
}

close($src);
{% endhighlight %}

这里取了个捷径，因为第二列的内容刚好是数字，所以可以直接用一个数组来标记当前遇到的数字是否出现过。如果给出的是另外的内容比如字母ABCD等，就需要用一个hash来记录了。更复杂的情况下还要考虑是否可能遇到会引起Perl解引用错误的字符或非法的变量名，就不深入讨论了。

总之，这里的想法就是同时开了多个文件句柄来处理输出，稍微用了下文件句柄的引用。

