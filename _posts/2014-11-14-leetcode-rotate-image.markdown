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
    void rotate(vector<vector<int> > &matrix) {
        int n = matrix.size();
        if(n < 2) return;
        int half = n/2;
        for(int i = 0; i < half; ++i){
            for(int j = 0; j < half; ++j){
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = temp;
            }
        }
        if(n % 2 == 1){
            half = n/2;
            for(int i = 0; i < half; ++i){
                int temp = matrix[i][half];
                matrix[i][half] = matrix[half][i];
                matrix[half][i] = matrix[n-1-i][half];
                matrix[n-1-i][half] = matrix[half][n-1-i];
                matrix[half][n-1-i] = temp;
            }
        }
    }
};
{% endhighlight %}


