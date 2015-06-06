---
layout: post
title: "Leetcode: One Edit Distance"
date:   2015-01-17
comments: true
categories: Leetcode
---

***
<br />
[*One Edit Distance*](https://leetcode.com/problems/one-edit-distance/)

*Given two strings S and T, determine if they are both one edit distance apart.*

***
<br />

[Edit Distance](https://leetcode.com/problems/edit-distance/)的弱化版，不需要像[Edit Distance一样]({{ site.url }}/leetcode/2015/01/16/leetcode-edit-distance.html)使用动态规划，直接比较就可以。

思路：

如果两个字符串的长度只差大于1，证明肯定不能只用一步编辑来实现两个字符串之间的转换，直接返回false；

如果两个字符串长度相等，只要逐一字符比较，两个字符串相差的字符个数等于1即可；

如果两个字符串长度不相等（必定差1），如果编辑距离为1，证明必然较长的那个字符串比较短的字符串多了一个字符，逐一比较找出第一个不同的字符，跳过这个字符继续比较两个字符串剩下的部分即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        int m = s.size(), n = t.size();
        if(m - n > 1 || n - m > 1) return false;
        if(m == n){
            int e = 0, p = 0;
            while(p < m && e < 2){
                e += (s[p] != t[p]);
                ++p;
            }
            return e == 1;
        }else{
            int p = 0, q = 0, l = min(m, n);
            while(p < l && s[p] == t[p]) ++p;
            q = p;
            p += m > n;
            q += m < n;
            while(p < m && s[p] == t[q]){
                ++p;
                ++q;
            }
            return p == m;
        }
    }
};
{% endhighlight %}


