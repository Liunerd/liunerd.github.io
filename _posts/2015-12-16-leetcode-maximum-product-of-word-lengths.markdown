---
layout: post
title: "Leetcode: Maximum Product of Word Lengths"
date:   2015-12-16
comments: true
categories: Leetcode
---

***
<br />
[*Maximum Product of Word Lengths*](https://leetcode.com/problems/maximum-product-of-word-lengths/)

*Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.*

*Example 1:*

*Given `["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]`*

*Return `16`*

*The two words can be `"abcw"`, `"xtfn"`.*

*Example 2:*

*Given `["a", "ab", "abc", "d", "cd", "bcd", "abcd"]`*

*Return `4`*

*The two words can be `"ab"`, `"cd"`.*

*Example 3:*

*Given `["a", "aa", "aaa", "aaaa"]`*

*Return `0`*

*No such pair of words.*

***
<br />

这题思路还是比较简单的，核心就是设计一个O(1)复杂度的比较两个单词没有相同字母的方法。因为题面里说了只有26个小写字母，所以一个32位的int就可以用来作为一个bitmap来记录26个字母是否出现的辅助数据结构。直接上代码：

{% highlight c++ %}
class Solution {
public:
    int maxProduct(vector<string>& words) {
        int n = words.size();
        if(n <= 1) return 0;
        vector<int> aux(n, 0);
        for(int i = 0; i < n; ++i)for(int j = 0; j < words[i].size(); ++j){
            int pos = 1 << (words[i][j] - 'a');
            aux[i] |= pos;
        }
        int ret = 0;
        for(int i = 0; i < n-1; ++i) for(int j = i+1; j < n; ++j){
            int testval = aux[i] & aux[j];
            if(testval == 0){
                int wlp = words[i].size() * words[j].size();
                ret = ret > wlp ? ret : wlp;
            }
        }
        return ret;
    }
};
{% endhighlight %}

因为用了一个和words等长的数组，空间复杂度是O(n)；时间复杂度上，计算aux数组每一个值的复杂度为O(L)，其中L为单词的平均长度，第二步的计算复杂度为O(n^2)，我们假设n和L的量级大概相同，则整体复杂度就是一个O(n^2)。
