---
layout: post
title: "Leetcode: Self Crossing"
date:   2016-02-23
comments: true
categories: Leetcode
---

***
<br />
[*Self Crossing*](https://leetcode.com/problems/self-crossing/)

*You are given an array x of n positive numbers. You start at point `(0,0)` and moves `x[0]` metres to the north, then `x[1]` metres to the west, `x[2]` metres to the south, `x[3]` metres to the east and so on. In other words, after each move your direction changes counter-clockwise.*

*Write a one-pass algorithm with `O(1)` extra space to determine, if your path crosses itself, or not.*

***
<br />

这题有点意思，一开始只是想到了向内旋转的情况，觉得并没有什么难度。其实要看当前的旋转是向内还是向外的。如果是向内旋转，在遍历到第`i`个元素的时候，只要这个元素没有超出第`i-2`个元素即可；如果是向外旋转，需要做一些判断，因为向外旋转是可能转换成向内旋转的（然而向内旋转不可能转换成向外旋转，这点很重要）。判断的时候要注意一下会不会和3步之前的元素有交叉，如果有，可以在原地直接修改`x[i-1]`的值。

*代码：*

{% highlight c++ %}

class Solution {
public:
    bool isSelfCrossing(vector<int>& x) {
        int len = x.size();
        if(len < 4) return false;
        bool inside = x[0] >= x[2];
        for(int i = 3; i < len; ++i){
            if(inside){
                if(x[i] >= x[i-2]) return true;
            }else if(x[i] <= x[i-2]){
                inside = true;
                if(i == 3 && x[i] == x[i-2] || x[i] >= x[i-2] - x[i-4]) x[i-1] -= x[i-3];
            }
        }
        return false;
    }
};

{% endhighlight %}