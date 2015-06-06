---
layout: post
title: "Leetcode: Edit Distance"
date:   2015-01-16
comments: true
categories: Leetcode
---

***
<br />
[*Edit Distance*](https://leetcode.com/problems/edit-distance/)

*Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)*

*You have the following 3 operations permitted on a word:*

*a) Insert a character*

*b) Delete a character*

*c) Replace a character*

***
<br />

经典的利用动态规划的题目。

假设两个字符串s1和s2的长度为m和n，维护一个m*n的表table，其中(i, j)位置的元素表示的是`s1.substr(0, i)`和`s2.substr(0, j)`的编辑距离。(i, j)位置的元素值可以由(i-1, j)，(i, j-1)和(i-1, j-1)三个位置的值推算出来，总结递归关系即分析构造两个子串的方法，有以下几种可能：

- *情况1*：字符串`s1.substr(0, i)`从`s2.substr(0, j-1)`通过添加一个字符得到，在这种情况下table(i, j) = table(i, j-1) + 1

- *情况2*：字符串`s2.substr(0, j)`从`s1.substr(0, i-1`)通过添加一个字符得到，在这种情况下table(i, j) = table(i-1, j) + 1

- *情况3*：通过修改`s1[i-1]`使其和`s2[j-1]`相等获得，在这种情况下，如果`s1[i-1]`和`s2[j-1]`本身就相等，table(i, j) = table(i-1, j-1)，若两者不等，则table(i, j) = table(i-1, j-1) + 1。

分别算出这三种情况，取最小值，即是table(i, j)的值。

为了方便计算，多添加一行和一列，分别表示当其中一个字符串是空串时和另一个字符串的相应子串之间的编辑距离，很明显table(0, j) = j，table(i, 0) = i;
返回table(m, n)，就是两个完整字符串之间的编辑距离。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        if(m == 0) return n;
        if(n == 0) return m;
        vector<vector<int> > table(m+1, vector<int>(n+1, 0));
        for(int i = 1; i <= m; ++i) table[i][0] = i;
        for(int i = 1; i <= n; ++i) table[0][i] = i;
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                int min = table[i-1][j] < table[i][j-1] ? table[i-1][j] : table[i][j-1]; // 情况1和情况2的最小值
                ++min;
                int a = table[i-1][j-1] + (word1[i-1] != word2[j-1]); // 情况3
                table[i][j] = min < a ? min : a;
            }
        }
        return table[m][n];
    }
};
{% endhighlight %}

