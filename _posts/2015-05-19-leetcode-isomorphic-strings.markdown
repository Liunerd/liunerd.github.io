---
layout: post
title: "Leetcode: Isomorphic Strings"
date:   2015-05-19
comments: true
categories: Leetcode
---

***
<br />
[*Isomorphic Strings*](https://leetcode.com/problems/isomorphic-strings/)

*Given two strings s and t, determine if they are isomorphic.*

*Two strings are isomorphic if the characters in s can be replaced to get t.*

*All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.*

*For example,*

*Given "egg", "add", return `true`.*

*Given "foo", "bar", return `false`.*

*Given "paper", "title", return `true`.*

***
<br />

思路：

这个问题实际是关于两个集合之间的映射，需要证明映射关系必须是一对一的，不能出现的多对一的情况。所以可以用一个char数组来记录一个映射，首先验证从s到t的，再反过来验证一遍从t到s的。两边都通过即返回true。

{% highlight c++ %}
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        int m = s.size();
        if(m != t.size()) return false;
        if(m <= 1) return true;
        char match_table[256];
        for(int i = 0; i < 256; ++i) match_table[i] = '\0';
        for(int p = 0; p < m; ++p){
            if(match_table[s[p]] == '\0') match_table[s[p]] = t[p];
            else if(match_table[s[p]] != t[p]) return false;
        }
        for(int i = 0; i < 256; ++i) match_table[i] = '\0';
        for(int p = 0; p < m; ++p){
            if(match_table[t[p]] == '\0') match_table[t[p]] = s[p];
            else if(match_table[t[p]] != s[p]) return false;
        }
        return true;
    }
};
{% endhighlight %}


