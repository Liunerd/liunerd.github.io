---
layout: post
title: "Leetcode: House Robber"
date:   2015-05-21
comments: true
categories: Leetcode
---

***
<br />
[*House Robber*](https://leetcode.com/problems/house-robber/)

*You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.*

*Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.*

***
<br />

思路：

这题用递推的方法来想，在当前位置i，robber有两种选择，一种是抢劫这家，这意味着前一家不能抢；或者不抢这家，也就是前一家可以抢。维护两个值prev和prev2，分别表示抢劫到i-1家和抢劫到i-2家获得的最大收益。最大收益这里必然是prev和prev2 + num[i]之间较大的那个。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int rob(vector<int> &num) {
        int n = num.size();
        if(n <= 0) return 0;
        if(n == 1) return num[0];
        if(n == 2) return num[0] > num[1] ? num[0] : num[1];
        
        int prev = num[0], prev2 = 0;
        for(int i = 1; i < n; ++i){
            int temp = prev;
            prev = prev > num[i] + prev2 ? prev : num[i] + prev2;
            prev2 = temp;
        }
        return prev;
    }
};
{% endhighlight %}

注：这里不需要去分开讨论前一家是否被抢的情况，因为如果没有抢i-1家，则一定有prev == prev2，当前i位置的收益一定是prev2 + num[i]。

