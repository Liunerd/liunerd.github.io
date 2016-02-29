---
layout: post
title: "Leetcode: Word Pattern"
date:   2016-02-27
comments: true
categories: Leetcode
---

***
<br />
[*Word Pattern*](https://leetcode.com/problems/word-pattern/)

*Given a pattern and a string str, find if str follows the same pattern.*

*Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.*

*Examples:*

*1. `pattern = "abba"`, `str = "dog cat cat dog"` should return `true`.*

*2. `pattern = "abba"`, `str = "dog cat cat fish"` should return `false`.*

*3. `pattern = "aaaa"`, `str = "dog cat cat dog"` should return `false`.*

*4. `pattern = "abba"`, `str = "dog dog dog dog"` should return `false`.*


*Notes:*

*You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space.*

***
<br />

这个题目相对来说比较简单，只需要一个一个检测pattern中的每个字母和str中的每个子串是否满足一一对应的关系即可。从pattern match到str可以使用一个长度为26的vector，从str match到pattern则可以使用一个hash表(unordered_map)来实现。

*代码：*

{% highlight c++ %}

class Solution {
public:
    bool wordPattern(string pattern, string str) {
        vector<string> p2s(26, string(""));
        unordered_map<string, char> s2p;
        int plen = pattern.size(), slen = str.size(), start = 0, end = 0, p = 0;
        if(plen == 0) return slen == 0;
        while(start < slen && p < plen){
            end = start;
            while(end < slen && str[end] != ' ') ++end;
            string sstr = str.substr(start, end - start);
            if(p2s[pattern[p] - 'a'] == ""){
                if(s2p.find(sstr) == s2p.end()){ // find a new match
                    p2s[pattern[p] - 'a'] = sstr;
                    s2p[sstr] = pattern[p];
                }else return false;
            }else{
                if(p2s[pattern[p] - 'a'] != sstr) return false;
                else if(s2p.find(sstr) == s2p.end()) return false;
                else if(s2p[sstr] != pattern[p]) return false;
            }
            start = end + 1;
            ++p;
        }
        if(!(start == slen + 1 && p == plen)) return false;
        return true;
    }
};

{% endhighlight %}
