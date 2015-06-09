---
layout: post
title: "Leetcode: Factorial Trailing Zeroes"
date:   2015-02-26
comments: true
categories: Leetcode
---

***
<br />
[*Factorial Trailing Zeroes*](https://leetcode.com/problems/factorial-trailing-zeroes/)

*Given an integer n, return the number of trailing zeroes in n!.*

*Note: Your solution should be in logarithmic time complexity.*

***
<br />

思路：

如果我们将每一个数字看成是其质因数分解后的所得的数字的连乘，那么最终的阶乘也就可以看成一系列质数相乘的积。如果最终结果的结尾有一个0出现，则证明在质数相乘的形式中有一个2*5。而作为连续整数质因子，2出现的频率要高于5，所以我们只要计算出其中有几个5作为因子即可。

这题只要想明白一点就迎刃而解了。代码非常简单：

{% highlight c++ %}
class Solution {
public:
    int trailingZeroes(int n) {
        int ret = 0;
        while(n >= 5){
            ret += n/5;
            n/=5;
        }
        return ret;
    }
};
{% endhighlight %}


