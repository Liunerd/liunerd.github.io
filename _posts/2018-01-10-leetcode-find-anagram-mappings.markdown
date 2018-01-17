---
layout: post
title: "Leetcode: Find Anagram Mappings"
date:   2018-01-10
comments: true
categories: Leetcode
---

***
<br />

Given two lists Aand B, and B is an anagram of A. B is an anagram of A means B is made by randomizing the order of the elements in A.

We want to find an index mapping P, from A to B. A mapping P[i] = j means the ith element in A appears in B at index j.

These lists A and B may contain duplicates. If there are multiple answers, output any of them.

For example, given

A = [12, 28, 46, 32, 50]

B = [50, 12, 32, 46, 28]

We should return

[1, 4, 3, 2, 0]

as P[0] = 1 because the 0th element of A appears at B[1], and P[1] = 4 because the 1st element of A appears at B[4], and so on.

Note:

    A, B have equal lengths in range [1, 100].

    A[i], B[i] are integers in range [0, 10^5].



***
<br />

这是一道Easy难度的题目，但还是要说一下，因为不知道是不是题目太水，test case也一样的水，竟然看到了一些错误答案也能过。这题的一个点是A和B中可能包含重复的数字，也就是用哈希表来单纯记录位置是可能导致错误的，也正是对于这个点的test case不足导致一些错误答案稀里糊涂地ac了，具体的错误就是输出的数组里可能会有相同的数字。比如A和B都是[1,1,1]，[0,1,2]是一个正确的输出，而[0,0,0]不是，也就是说任何可能产生类似[0,0,0]的算法都应该是错误的。

思路还是很简单的，先遍历B，用哈希表记录每个元素的位置，然后再遍历A，从哈希中读出每个元素的位置。在这个过程中要区分duplicates。这题的简单之处应该在于数据的长度和数据的范围是一个比较小的数字：数组最长100，数据范围不会超过1万。可以做一个这样的简单处理，当检索到B[i] = n时，如果这是该值n在B[0..i]中的第j次出现，那么设置hash[j*100000+n] = i。j从1开始记录，hash[n]则用来存放j，也就是遇到n的次数，每次++hash[n]。遍历到A[i] = m的时候，也是通过先找出j，继而找出hash[j*100000+m]。不难看出在第一个遍历中，每处理一个元素需要++hash[B[i]]，第二个遍历中每处理一个元素需要--hash[A[i]]。

代码：

{% highlight c++ %}
#define WHERE(a, b) (a*1000000+b)
class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        unordered_map<int, int> hash;
        int len = B.size();
        vector<int> ret(len, 0);
        for(int i = len-1; i >= 0; --i) hash[WHERE(++hash[B[i]], B[i])] = i;
        for(int i = 0; i < len; ++i) ret[i] = hash[WHERE(hash[A[i]]--, A[i])];
        return ret;
    }
};
{% endhighlight %}

第一个遍历用的反向，这样能够保证得到的答案是最小的序列，强迫症福音。
