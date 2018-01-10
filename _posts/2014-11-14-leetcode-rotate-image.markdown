---
layout: post
title: "Leetcode: Rotate Image"
date:   2014-11-14
comments: true
categories: Leetcode
---

***
<br />
[*Rotate Image*](https://leetcode.com/problems/rotate-image/)

*You are given an n x n 2D matrix representing an image.*

*Rotate the image by 90 degrees (clockwise).*

*Follow up:*

*Could you do this in-place?*

***
<br />

思路：

翻转九十度，只要找出每一组四个点，依次挪一个位置即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        if(n < 2) return;
        int r = n/2, c = n/2 + (n%2 == 1);
        for(int x = 0; x < r; ++x) for(int y = 0; y < c; ++y){ // foreach pixel in top-left
        	int i = y, j = n-x-1; // pos in top-right
        	int val = matrix[i][j];
        	matrix[i][j] = matrix[x][y];
        	i = n-x-1; j = n-y-1; // pos in down-right
        	int temp = matrix[i][j];
        	matrix[i][j] = val;
        	i = n-y-1; j = x; // pos in down-left
        	matrix[x][y] = matrix[i][j];
        	matrix[i][j] = temp;
        }
        return;
    }
};
{% endhighlight %}


