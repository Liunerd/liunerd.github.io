---
layout: post
title: "Leetcode: Spiral Matrix"
date:   2014-11-10
comments: true
categories: Leetcode
---

***
<br />
[*Spiral Matrix*](https://leetcode.com/problems/spiral-matrix/)

*Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.*

*For example,

*Given the following matrix:*

[
 
 [ 1, 2, 3 ],

 [ 4, 5, 6 ],

 [ 7, 8, 9 ]

]

*You should return `[1,2,3,6,9,8,7,4,5]`.*

***
<br />

思路：

转圈向里数即可，注意边界条件。

*代码：*

{% highlight c++ %}
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        vector<int> ret;
        int row = matrix.size();
        if(row == 0) return ret;
        if(row == 1) return matrix[0];
        int col = matrix[0].size();
        int m = row > col ? col : row;
        int half = m/2;
        for(int n = 0; n < half; ++n){
            for(int i = n; i < col - n - 1; ++i) ret.push_back(matrix[n][i]);
            for(int i = n; i < row - n - 1; ++i) ret.push_back(matrix[i][col-n-1]);
            for(int i = col - n - 1; i > n; --i) ret.push_back(matrix[row-n-1][i]);
            for(int i = row - n - 1; i > n; --i) ret.push_back(matrix[i][n]);
        }
        if(m%2 == 1){
            col -= half;
            row -= half;
            for(int i = half; i < row; ++i){
                for(int j = half; j < col; ++j){
                    ret.push_back(matrix[i][j]);
                }
            }
        }
        return ret;
    }
};
{% endhighlight %}

