---
layout: post
title: "Leetcode: House Robber II"
date:   2015-05-21
comments: true
categories: Leetcode
---

***
<br />
[*House Robber II*](https://leetcode.com/problems/house-robber-ii/)

*Note: This is an extension of [House Robber](https://leetcode.com/problems/house-robber/).*

*After robbing those houses on that street, the thief has found himself a new place for his thievery so that he will not get too much attention. This time, all houses at this place are arranged in a circle. That means the first house is the neighbor of the last one. Meanwhile, the security system for these houses remain the same as for those in the previous street.*

*Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.*

***
<br />

思路：

想法[继承House Robber]({{ site.url }}/leetcode/2015/05/21/leetcode-house-robber.html)，还是要先把环拆成线性的来处理。拆成环就有两种情况需要分析，假定拆开的位置是数组的最后一个元素位置n-1，则取得最大收益时，要么抢劫了这家，要么没抢，这点是无法确定的。先写了一个helper函数来计算线性情况下从第s家抢到第e家（不包括第e家）获得的收益，如果没有抢第n-1家，则收益是helper(nums, 0, n-1)，如果抢劫了第n-1家，则可以得到的一个结论是第0家和第n-2家也不会抢劫，这种情况下收益是helper(nums, 1, n-2)，比较两个收益取较大返回就是正确结果。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n = nums.size();
        
        int maxroblast = helper(nums, 1, n-2) + nums[n-1];
        int maxnroblast = helper(nums, 0, n-1);
        return maxroblast > maxnroblast ? maxroblast : maxnroblast;
    }
    int helper(vector<int>& nums, int s, int e){
        if(e - s <= 0) return 0;
        if(e - s == 1) return nums[s];
        if(e - s == 2) return nums[s] > nums[s+1] ? nums[s] : nums[s+1];
        
        int prev = nums[s], prev2 = 0;
        for(int i = s+1; i < e; ++i){
            int temp = prev;
            prev = prev > nums[i] + prev2 ? prev : nums[i] + prev2;
            prev2 = temp;
        }
        return prev;
    }
};
{% endhighlight %}

