---
layout: post
title: "Leetcode： Range Sum Query - Immutable"
date:   2015-11-19
comments: true
categories: Leetcode
---

***
<br />
*[Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/)*

*Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.*

*Example:*

*`Given nums = [-2, 0, 3, -5, 2, -1]`*

*`sumRange(0, 2) -> 1`*

*`sumRange(2, 5) -> -1`*

*`sumRange(0, 5) -> -3`*

*Note:*

*You may assume that the array does not change.*
*There are many calls to sumRange function.*

***
<br />

这题的思路比较简单，维护两个vector，在第i位分别记录原数组中前i位和后n-i位的和，计算`sumRange(i, j)`时，只要计算前j位和后n-i位的和，再减去整个数组所有元素的和即可。

*代码：*

{% highlight c++ %}
class NumArray {
public:
    NumArray(vector<int> &nums) {
        sum = 0;
        int len = nums.size();
        for(int i = 0; i < len; ++i){
            sum += nums[i];
            sum_left.push_back(sum);
        }
        if(sum) sum_right.push_back(sum);
        for(int i = 1; i < len; ++i) sum_right.push_back(sum - sum_left[i-1]);
    }

    int sumRange(int i, int j) {
        return sum_left[j] - sum + sum_right[i];
    }
    
    vector<int> sum_left;
    vector<int> sum_right;
    int sum;
};
{% endhighlight %}

复杂度非常直观，新建的时间复杂度是O(n)，sumRange的时间复杂度为O(1)，空间复杂度是O(n)。
