---
layout: post
title: "Leetcode: Counting Bits"
date:   2016-03-21
comments: true
categories: Leetcode
---

***
<br />
[*Counting Bits*](https://leetcode.com/problems/counting-bits/)

*Given a non negative integer number num. For every numbers i in the range 0 ≤ i ≤ num calculate the number of 1's in their binary representation and return them as an array.*

*Example:*

*For `num = 5` you should return `[0,1,1,2,1,2]`. *

***
<br />

这题的简单解法就是题目所说的`O(n*sizeof(int))`，但是被禁止了，所以还需要想另外的方法。因为学过数字电路，所以很容易想到，其实所有正整数的int是循环出现的，只不过是每逢2的幂在最高位添加1而已。事先开好存储空间，用一个transform就可以实现。

*代码：*

{% highlight c++ %}

class Solution {
public:
    vector<int> countBits(int num) {
        ++num;
        vector<int> ret(2*num, 0);
        for(int i = 1; i < num; i *= 2) transform(ret.begin(), ret.begin() + i, ret.begin() + i, [](int i){ return i+1; });
        ret.resize(num);
        return ret;
    }
};

{% endhighlight %}

