---
layout: post
title: "Leetcode: Jump Game II"
date:   2014-10-12
comments: true
categories: Leetcode
---

***
<br />
[*Jump Game II*](https://leetcode.com/problems/jump-game-ii/)

*Given an array of non-negative integers, you are initially positioned at the first index of the array.*

*Each element in the array represents your maximum jump length at that position.*

*Your goal is to reach the last index in the minimum number of jumps.*

*For example:*

*Given array `A = [2,3,1,1,4]`*

*The minimum number of jumps to reach the last index is 2. (Jump 1 step from index 0 to 1, then 3 steps to the last index.)*

***
<br />

思路：

正向遍历，每一次循环从上一步走到的最远距离开始到遍历到这一步能够到的最远距离，得到走下一步能够到的最远距离，当这个距离大于数组长度时，退出循环，这是记录的步数就是最少所需的步数。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if(n <= 1) return 0;
        if(nums[0] >= n-1) return 1;
        int end = nums[0], count = 1;
        for(int i = 0; i < n;){
            int newend = 0;
            for(; i <= end; ++i) newend = newend > i + nums[i] ? newend : i + nums[i];
            if(end >= newend) return 0;
            if(newend >= n-1) return count + 1;
            i = end + 1;
            end = newend;
            ++count;
        }
        return count;
    }
};
{% endhighlight %}

