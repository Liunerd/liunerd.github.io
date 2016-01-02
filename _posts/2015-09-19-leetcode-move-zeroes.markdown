---
layout: post
title: "Leetcode： Move Zeroes"
date:   2015-09-19
comments: true
categories: Leetcode
---

***
<br />
*[Move Zeroes](https://leetcode.com/problems/move-zeroes/)*

*Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.*

*For example, given `nums = [0, 1, 0, 3, 12]`, after calling your function, nums should be `[1, 3, 12, 0, 0]`.*

*Note:*

*-You must do this in-place without making a copy of the array.*

*-Minimize the total number of operations.*


***
<br />

这题有点太水了，只需要维护一个读指针一个写指针，读指针逐个遍历数组，遇到非零元素就把读指针内容写入到写指针位置并移动写指针到下一个位置，最后再把写指针所在位置到数组尾部全部填充0即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int len = nums.size(), r = 0, w = 0;
        for(; r < len; ++r){
            if(nums[r] != 0){
                if(r != w) nums[w] = nums[r];
                ++w;
            }
        }
        for(; w < len; ++w) nums[w] = 0;
    }
};
{% endhighlight %}

吐个槽：这题应该比谁的复杂度更高，算法在不触发TLE的前提下更耗时，感觉还有点意思。

