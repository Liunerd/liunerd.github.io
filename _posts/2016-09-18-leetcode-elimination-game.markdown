---
layout: post
title: "Leetcode: Elimination Game"
date:   2016-09-18
comments: true
categories: Leetcode
---

***
<br />
[*Elimination Game*](https://leetcode.com/problems/elimination-game/)

*There is a list of sorted integers from 1 to n. Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.*

*Repeat the previous step again, but this time from right to left, remove the right most number and every other number from the remaining numbers.*

*We keep repeating the steps again, alternating left to right and right to left, until a single number remains.*

*Find the last number that remains starting with a list of length n.*

*Example:*

*Input:*

n = 9,

1 __2__ 3 __4__ 5 __6__ 7 __8__ 9

2 __4__ 6 __8__

__2__ 6

6

*Output:*

6

***
<br />

这题可以参考具体数学里介绍的[Josephus Problem](https://en.wikipedia.org/wiki/Josephus_problem)，二者相似但不相同。按照具体数学里介绍的解题思路，先尝试列出前几个n和其对应的结果，假设这个函数为E：

|  n  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |  11  |  12  |  13  |  14   |
| E(n)|  0  |  1  |  2  |  2  |  2  |  2  |  4  |  4  |  6  |  8  |  8   |  8   |  6   |  6   |  8    |


在手动解这几个n的时候，不难得出第一个规律，即n为奇数时E(n) == E(n-1)，也就是：

- `E(2m+1) = E(2m)`, 其中m为正数；

然后再看n是偶数的情况。因为第一次消除和第二次消除的方法不一样（左起第一个开始消除和右起第一个开始消除），但是我们可以把这两次消除看作是一次操作，观察两次消除之后的序列不难得出当n是4的整数倍时，前两次消除后的序列是：

2, 6, 10, 14...

可以用一个通项公式`(i-1)*4+2`来表示，其中`i`是消除后序列中的数字的下标。消除过2次之后，序列里的数字个数从`n=4m`降到了还剩`m`个，正好可以一一映射到`n = m`时的结果，也就是说如果我们对`m`求一次`E(m)`，那么我们得到的结果*__刚好是`E(4m)`的结果在`4m`消除2次后所得序列中的下标__*，即：

- `E(4m) = (E(m)-1)*4+2`，其中m为正数。

最后研究`n = 4m+2`的情况。同样是2次消除后，序列为：

4, 8, 12...

这个序列的通项公式就很直白了，`4*i`。消除完第一遍之后，剩下的序列长度为`2m+1`，消除完第二遍，因为第一遍剩下了奇数个元素，所以第二次消除一定会多消除掉一个，剩下的序列长度就是`m`。和`n = 4*m`的情况类似，如果我们对`m`求一次`E(m)`，那么我们得到的结果*__刚好是`E(4m+2)`的结果在`4m+2`消除2次后所得序列中的下标__*，即：

- `E(4*m+2) = E(m)*4`，其中m为正数。

最后用n来重写这三个公式，就得到了

![](http://latex.codecogs.com/gif.latex?E(n)=\left\{\begin{aligned}E(n-1)\;when\;n\;\%\;2\;==\;1\\(E(n/4)-1)*4+2\;when\;n\;\%\;4\;==\;0\\E((n-2)/4)*4\;when\;n\;\%\;4\;==\;2\end{aligned}\right)

然后代码就好写了，用递归就可以，跳出递归的条件是`n<4`的情况。

代码：

{% highlight c++ %}

class Solution {
public:
    int lastRemaining(int n) {
        if(n < 4) return n > 2 ? 2 : n;
        if(n % 2 == 1) return lastRemaining(n-1);
        if(n % 4 == 2) return lastRemaining((n-2)/4)*4;
        return (lastRemaining(n/4)-1)*4+2;
    }
};

{% endhighlight %}
