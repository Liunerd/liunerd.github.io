---
layout: post
title: "Leetcode: Candy"
date:   2014-10-13
comments: true
categories: Leetcode
---

***
<br />
[*Candy*](https://leetcode.com/problems/candy/)

*There are N children standing in a line. Each child is assigned a rating value.*

*You are giving candies to these children subjected to the following requirements:*

- *Each child must have at least one candy.*

- *Children with a higher rating get more candies than their neighbors.*

*What is the minimum candies you must give?*

***
<br />

思路：

要给某一个位置的小朋友分糖，需要知道他左右两侧的邻居有多少糖，显然当从左到右遍历的时候，是事先不会知道右边位置分到多少糖的，所以这个数组需要正向和反向各扫一遍：

正向扫的时候，只需要关注如果左边的邻居rating比当前位置低，就在左边邻居的基数上加一个，如果比左边邻居低，按照贪心原则糖数设为最低值也就是1；

反向扫的时候，只需要关注右边邻居的rating，如果比当前位置低，需要判断一下当前位置在正向遍历时分配到的糖数和右边邻居的糖数+1，取较高的那个，如果右边邻居rating低于当前位置的rating，保留当前值。

这个题的奇怪之处是如果两个孩子有相同的rating，则其中一个孩子可能拿到比另一个孩子少的candy。比如说：{1, 2, 2}这个case，给出的正确结果是4而不是5。

*能AC的代码：*

{% highlight c++ %}
class Solution {
public:
    int candy(vector<int> &ratings) {
        int len = ratings.size();
        if(len == 0) return 0;
        if(len == 1) return 1;
        vector<int> c(len, 1);
        for(int i = 1; i < len; ++i) c[i] = ratings[i] > ratings[i-1] ? c[i-1]+1 : c[i];
        for(int i = len-2; i >= 0; --i) c[i] = ratings[i] > ratings[i+1] ? max(c[i+1]+1, c[i]) : c[i];
        int ret = 0;
        for(int i = 0; i < len; ++i) ret += c[i];
        return ret;
    }
};
{% endhighlight %}

*为相同rating孩子讨回公道的代码：*

{% highlight c++ %}
class Solution {
public:
    int candy(vector<int> &ratings) {
        int len = ratings.size();
        if(len == 0) return 0;
        if(len == 1) return 1;
        vector<int> c(len, 1);
        for(int i = 1; i < len; ++i){
            int cd = c[i-1] + (ratings[i-1] != ratings[i]); // 替天行道
            c[i] = ratings[i] >= ratings[i-1] ? cd : c[i];
        }
        for(int i = len-2; i >= 0; --i)    c[i] = ratings[i] > ratings[i+1] ? max(c[i+1]+1, c[i]) : c[i];
        int ret = 0;
        for(int i = 0; i < len; ++i) ret += c[i];
        return ret;
    }
};
{% endhighlight %}

