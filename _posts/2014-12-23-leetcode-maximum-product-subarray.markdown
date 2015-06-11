---
layout: post
title: "Leetcode: Maximum Product Subarray"
date:   2014-12-23
comments: true
categories: Leetcode
---

***
<br />
[*Maximum Product Subarray*](https://leetcode.com/problems/maximum-product-subarray/)

*Find the contiguous subarray within an array (containing at least one number) which has the largest product.*

*For example, given the array `[2,3,-2,4]`,*

*the contiguous subarray `[2,3]` has the largest product = 6.*

***
<br />

思路：

单纯从贪婪的想法出发，正向扫一遍，维护一个连乘最大值，但是遇到奇数个负数的情况时，可能会产生两种结合方法。所以需要用同样的方法再反向扫一遍。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ret = INT_MIN, p = 1, n = nums.size();
        for(int i = 0; i < n; ++i){
            p *= nums[i];
            ret = ret > p ? ret : p;
            p = p == 0 ? 1 : p;
        }
        p = 1;
        for(int i = n-1; i >= 0; --i){
            p *= nums[i];
            ret = ret > p ? ret : p;
            p = p == 0 ? 1 : p;
        }
        return ret;
    }
};
{% endhighlight %}

