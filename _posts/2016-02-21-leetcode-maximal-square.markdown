---
layout: post
title: "Leetcode: Maximal Square"
date:   2016-02-21
comments: true
categories: Leetcode
---

***
<br />
[*Maximal Square*](https://leetcode.com/problems/maximal-square/)

*Given a 2D binary matrix filled with 0's and 1's, find the largest square containing all 1's and return its area.*

*For example, given the following matrix:*

`1 0 1 0 0`

`1 0 1 1 1`

`1 1 1 1 1`

`1 0 0 1 0`

*Return `4`.*

***
<br />

这题是一个典型的动态规划问题，只要搞清楚递推关系就非常简单了。可以用一个矩阵记录中间结果，其中中间结果矩阵中`[i][j]`点的值表示以点`[i][j]`为最右下角元素的最大全1正方形的边长。这样可以推算出在`matrix[i][j] == '1'`的情况下，`[i][j]`的值只和其上，左和左上的三个值有关，是这三个值的最小值+1。如果`matrix[i][j] == '0'`，那中间结果矩阵中`[i][j]`位置的值直接就是0。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int maximalSquare(vector<vector<char> >& matrix) {
        int m = matrix.size();
        if(m == 0) return 0;
        int n = matrix[0].size();
        vector<vector<int> > table(m, vector<int>(n, -1));
        for(int i = 0; i < m; ++i) table[i][0] = matrix[i][0] - '0';
        for(int j = 1; j < n; ++j) table[0][j] = matrix[0][j] - '0';
        for(int i = 1; i < m; ++i) for(int j = 1; j < n; ++j) table[i][j] = matrix[i][j] == '1' ? min3(table[i-1][j-1], table[i-1][j], table[i][j-1]) + 1 : 0;
        int ret = table[0][0];
        for(int i = 0; i < m; ++i) for(int j = 0; j < n; ++j) ret = table[i][j] > ret ? table[i][j] : ret;
        return ret*ret;
    }
    
    static inline int min3(int a, int b, int c){
        return a < b ? (a < c ? a : c) : (b < c ? b : c);
    }
};
{% endhighlight %}
