---
layout: post
title: "Leetcode: Spiral Matrix II"
date:   2014-11-12
comments: true
categories: Leetcode
---

***
<br />
[*Spiral Matrix II*](https://leetcode.com/problems/spiral-matrix-ii/)

*Given an integer n, generate a square matrix filled with elements from 1 to n^2 in spiral order.*

*For example,*

*Given `n = 3`,*

*You should return the following matrix:*

[

 [ 1, 2, 3 ],

 [ 8, 9, 4 ],

 [ 7, 6, 5 ]

]

***
<br />

思路：

转圈向里赋值，注意边界条件即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        int half = n/2, cnt = 1;
        vector<vector<int> > ret(n, vector<int>(n, 0));
        for(int m = 0; m < half; ++m){
            for(int i = m; i < n - m - 1; ++i){
                ret[m][i] = cnt;
                ++cnt;
            }
            for(int i = m; i < n - m - 1; ++i){
                ret[i][n-m-1] = cnt;
                ++cnt;
            }
            for(int i = n - m - 1; i > m; --i){
                ret[n-m-1][i] = cnt;
                ++cnt;
            }
            for(int i = n - m - 1; i > m; --i){
                ret[i][m] = cnt;
                ++cnt;
            }
        }
        if(n % 2 == 1) ret[n/2][n/2] = n*n;
        return ret;
    }
};
{% endhighlight %}


