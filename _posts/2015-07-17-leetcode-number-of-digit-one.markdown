---
layout: post
title: "Leetcode: Number of Digit One"
date:   2015-07-17
comments: true
categories: Leetcode
---

***
<br />
*[Number of Digit One](https://leetcode.com/problems/number-of-digit-one/)*

*Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.*

*For example:*

*Given n = 13,*

*Return 6, because digit 1 occurred in the following numbers: 1, 10, 11, 12, 13.*

***
<br />

思路：这题还是有点意思的，貌似是Google曾用过的题目。首先可以确定的一点是用从1到n遍历累加每一个数字中1的个数这种办法明显是行不通的，太耗时。为了得到一些线索，先从简单的几个例子看起：

`countDigitOne(9) = 1;`

`countDigitOne(99) = 20;`

`countDigitOne(999) = 300;`

`countDigitOne(9999) = 4000;`

`...`

这里就能看出规律了，虽然看起来手动求999和9999的情况比较麻烦，但其实推算出99的结果，999和9999的情况也就能猜到了。从这里出发可以得到一个思路，就是把n划分成`k*10^i + m`来表示，其中`1 <= k <= 9 && m < 10^i`，说白了就是按10进制的最高位和尾数来划分n。这里为了方便使用，再声明一个`b = 10^i`。另外为了下面的分析表示起来更清楚，这里假定我还有一个辅助函数（不一定需要写出来）`helper(int s, int e)`，返回`[s, e)`左闭右开区间内的所有数字含有的1的总数。这里可以得到`countDigitOne(n)`等价于`helper(0, n+1)`，下面会用上。

好了，现在来看一下逻辑。还是通过一个例子来看，假如`n = 4321`，首先按照划分方法，此时：

`k = 4, m = 321, b = 1000, i = 3`

而`countDigitOne(4321)`就可以分割表示成：

`countDigitOne(4321) = helper(0, 4000) + helper(4000, 4321+1)`

首先看`helper(0, 4000)`，我们已知了`helper(0, 1000) = i * (b / 10) = 300`，（注意，这里必须要带括号，否则会发生溢出的情况。）而4000里包含4个1000，所以出现在低三位的1的个数就是`i * (b/10) * k`。而出现在最高位上的1的个数正好有1000个（1000到1999，也可以表示成b个）。总之，这部分的1的个数为`i*(b/10)*k + b`个。

尾数的部分，因为最高位上不会出现1的情况（都是4），所以可以得到`helper(4000, 4321+1) = helper(0, 321+1) =  countDigitOne(321) = countDigitOne(m)`，可以利用递归求解。

讲到这里就会发现一种特殊情况，即最高位为1的情况，比如`n = 1234`时，首次划分的结果是

`k = 1, m = 234, b = 1000, i = 3`

`countDigitOne(1234) = helper(0, 1000) + helper(1000, 1234+1)`

`helper(0, 1000)`的部分不难得出，值为`i*(b/10)`，也可以后面加上`*k`，但是因为`k == 1`，不写也行。而`helper(1000, 1234+1)`的部分可以看出，最高位上的1一共有234+1（即m + 1）个，剩下低三位上1的个数就只剩下`helper(0, 234+1)`个了。所以：

`helper(1000, 1234+1) = 234 + 1 + helper(0, 234+1) = m + 1 + countDigitOne(m)`

综上，

- 如果`k == 1`，则`countDigitOne(n) = i*(b/10) + m + 1 + countDigitOne(m)`；

- 否则`countDigitOne(n) = i*(b/10)*k + b + countDigitOne(m)`。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int countDigitOne(int n) {
        if(n < 1) return 0;
        if(n < 10) return 1;
        int b = 1, i = 0, k = n;
        while(k >= 10){
            k /= 10;
            b *= 10;
            ++i;
        }
        int m = n%b;
        if(k == 1) return i*(b/10) + countDigitOne(m) + m + 1;
        else return i*(b/10)*k + b + countDigitOne(m);
    }
};
{% endhighlight %}

当然也可以按照这个思路来构造一个迭代算法，直接从最低位开始分割n，现在这个做法每次还要把n循环除到k为止，这里应该还是有一些优化空间的，这里就不做了（懒）。


