---
layout: post
title: "Leetcode: Jump Game"
date:   2014-10-12
comments: true
categories: Leetcode
---

***
<br />
[*Jump Game*](https://leetcode.com/problems/jump-game/)

*Given an array of non-negative integers, you are initially positioned at the first index of the array.*

*Each element in the array represents your maximum jump length at that position.*

*Determine if you are able to reach the last index.*

*For example:*

*`A = [2,3,1,1,4]`, return `true`.*

*`A = [3,2,1,0,4]`, return `false`.*

***
<br />

思路：

典型的倒过来想就很简单的问题。首先处理一下整个数组，可以得到从每个点出发所能够到的最远距离，再逆向扫一遍，维护一个值，表示“只要能够到这一点，就一定能走到终点”。逆向扫完如果这个值为0则表示可以到达终点。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool canJump(int A[], int n) {
        for(int i = 0; i < n; ++i) A[i] += i;
        for(int i = --n; i >= 0; --i) if(A[i] >= n) n = i;
        return n == 0;
    }
};
{% endhighlight %}

