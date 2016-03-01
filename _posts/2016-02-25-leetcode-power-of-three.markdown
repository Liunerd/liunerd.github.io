---
layout: post
title: "Leetcode: Power of Three"
date:   2016-02-25
comments: true
categories: Leetcode
---

***
<br />
[*Power of Three*](https://leetcode.com/problems/power-of-three/)

*Given an integer, write a function to determine if it is a power of three.*

*Follow up:*

*Could you do it without using any loop / recursion?*

***
<br />

这题不让用循环或者递归还是挺有意思的。其实2^31以内的3的幂并没有很多，只有20个（包括3^0 = 1），而3^20就超出32位有符号int的范围了。由此这个问题就可以有各种各样的花式解法了。比如用一个大的switch-case或者if-else结构来判断n是否和这20个数字相等啊，建立一个长度为20的数组放着20个幂跑二分查找啊，甚至可以建一个hash表来代替数组，然后从中查找啊，都可以。只是效率就各不相同了。

这题我觉得理论上最直接的解决方法是一种不太可能实现的方法，就是算出1-19这19个数字的最小公倍数m，计算3^m%n，如果是0则说明这个数字是3的幂。理论上这就是一个O(1)的运算而已。然而大概估算一下，m可以确切地算出来为58198140，3^m Google给出的答案是Infinity[抠鼻]。可以大概估算一下，因为3*3约等于10，所以这个数字大概有m/2 = 29099070位（十进制）。

所以还是简化一下，不用一个数字来解决所有的问题，用多个数字尝试一下。思路就是如果测试x%n == 0，可以判断n为3的幂。x肯定是3的幂，但是不需要从3^0到3^19都测试了，比如3^12，既可以判断3^2也可以判断3^3和3^6。基于这个道理，只需要选择x=3^10到3^19就行了。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n < 0 || n % 2 == 0) return false;
        if(n == 1) return true;
        if(59049 % n == 0) return true;
        if(177147 % n == 0) return true;
        if(531441 % n == 0) return true;
        if(1594323 % n == 0) return true;
        if(4782969 % n == 0) return true;
        if(14348907 % n == 0) return true;
        if(43046721 % n == 0) return true;
        if(129140163 % n == 0) return true;
        if(387420489 % n == 0) return true;
        if(1162261467 % n == 0) return true;
        return false;
    }
};
{% endhighlight %}
