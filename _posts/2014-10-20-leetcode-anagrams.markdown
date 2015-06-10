---
layout: post
title: "Leetcode: Anagrams"
date:   2014-10-20
comments: true
categories: Leetcode
---

***
<br />
[*Anagrams*](https://leetcode.com/problems/anagrams/)

*Given an array of strings, return all groups of strings that are anagrams.*

*Note: All inputs will be in lower-case.*

***
<br />

思路：

这题可以巧妙利用排序来解决。首先明确这样一个事实：如果两个字符串是anagram，那么分别排序这两个字符串里的所有字母，得到的两个新的字符串一定是想等的。这样对于每个字符串可以构造一个新串，其长度是旧串的两倍，前半部分是旧串排序好的所有字母，后半部分是旧串本身，再把所有的新串排序一下，这样互为anagram的字符串就自动聚到了一起，通过比较前半部分找出互为anagram的字符串，输出后半部分即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    vector<string> anagrams(vector<string> &strs) {
        int len = strs.size();
        vector<string> ret;
        if(len < 2) return ret;
        for(int i = 0; i < len; ++i){
            string temp = strs[i];
            sort(strs[i].begin(), strs[i].end());
            strs[i] += temp;
        }
        sort(strs.begin(), strs.end());
        for(int i = 0; i < len; ++i){
            if(i < len-1 && strs[i].substr(0, strs[i].size()/2) == strs[i+1].substr(0, strs[i+1].size()/2)){
                ret.push_back(strs[i].substr(strs[i].size()/2, strs[i].size()/2));
            }else if(i > 0 && strs[i].substr(0, strs[i].size()/2) == strs[i-1].substr(0, strs[i-1].size()/2)){
                ret.push_back(strs[i].substr(strs[i].size()/2, strs[i].size()/2));
            }
        }
        return ret;
    }
};
{% endhighlight %}

算法来自[编程珠玑](http://book.douban.com/subject/4924297/)。

