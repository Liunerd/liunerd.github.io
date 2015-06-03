---
layout: post
title: "Leetcode: Interleaving String"
date:   2015-03-10
comments: true
categories: Leetcode
---

***
<br />
[*Interleaving String*](https://leetcode.com/problems/interleaving-string/)

*Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.*

*For example,*

*Given:*

*`s1 = "aabcc",`*

*`s2 = "dbbca",`*

*When `s3 = "aadbbcbcac"`, return true.*

*When `s3 = "aadbbbaccc"`, return false.*

***
<br />

读完题一看这不又递归么，撸起袖子写了一个：

{% highlight c++ %}
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
        if(l3 != l1 + l2) return false;
        return helper(s1, 0, s2, 0, s3);
    }
    bool helper(string& s1, int p1, string& s2, int p2, string& s3){ // 从s1的p1位置和s2的p2位置往后比较（s3肯定就是p1+p2位置往后）
        while(p1 < s1.size() || p2 < s2.size()){ // 
            if(p1 < s1.size() && s1[p1] == s3[p1 + p2] && p2 < s2.size() && s2[p2] == s3[p1 + p2]){ // 如果出现两个字符串里当前的字符和s3中对应的字符都相等，就会出现分支
                if(!helper(s1, p1+1, s2, p2, s3) && !helper(s1, p1, s2, p2+1, s3)) return false;
                break;
            }else if(p1 < s1.size() && s1[p1] == s3[p1 + p2]) ++p1;
            else if(p2 < s2.size() && s2[p2] == s3[p1 + p2]) ++p2;
            else return false;
        }
        return true;
    }
};
{% endhighlight %}

果然超时了。原因就是在分支处产生了重复计算。首先考虑是否有贪心解法，想了半天没想出来。

好吧，现在就有两个思路了，一个是转用DP，另一个就是改进递归做法，加一个备忘，也就是用一个数据结构来保留求过的中间值。其实两种做法目的是一样的，就是记录已经求过的中间结果，防止重复求值。区别是一个自下而上，一个自上而下。

以下是两种解法：

*DP：*

{% highlight c++ %}
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
        if(l3 != l1 + l2) return false;
        vector<vector<bool> > table(l1+1, vector<bool>(l2+1, false));
        table[0][0] = true;
        
        for(int i = 0; i < l1; ++i) table[i+1][0] = (table[i][0] && s1[i] == s3[i]);
        for(int j = 0; j < l2; ++j) table[0][j+1] = (table[0][j] && s2[j] == s3[j]);

        for(int i = 0; i < l1; ++i){
            for(int j = 0; j < l2; ++j){
                table[i+1][j+1] = (table[i][j+1] && s1[i] == s3[i+j+1]) || (table[i+1][j] && s2[j] == s3[i+j+1]);
            }
        }
        return table[l1][l2];
    }
};
{% endhighlight %}

*带备忘的递归：*

{% highlight c++ %}
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int l1 = s1.size(), l2 = s2.size(), l3 = s3.size();
        if(l3 != l1 + l2) return false;
        vector<vector<int> > table(l1+1, vector<int>(l2+1, -1));
        return helper(s1, 0, s2, 0, s3, table);
    }
    bool helper(string& s1, int p1, string& s2, int p2, string& s3, vector<vector<int> >& table){
        if(p1 == s1.size() && p2 == s2.size()) return true;
        if(table[p1][p2] != -1) return table[p1][p2] == 1; // already solved
        else{
            if(p1 < s1.size() && s1[p1] == s3[p1+p2]){
                if(helper(s1, p1+1, s2, p2, s3, table)) table[p1][p2] = 1;
                else table[p1][p2] = 0;
            }
            if(table[p1][p2] != 1 && p2 < s2.size() && s2[p2] == s3[p1+p2]){
                if(helper(s1, p1, s2, p2+1, s3, table)) table[p1][p2] = 1;
                else table[p1][p2] = 0;
            }
        }
        if(table[p1][p2] == -1) table[p1][p2] = 0;
        return table[p1][p2] == 1;
    }
};
{% endhighlight %}

都可以AC。

最后，问题来了，这题到底有没有贪心？（无奖问答）

