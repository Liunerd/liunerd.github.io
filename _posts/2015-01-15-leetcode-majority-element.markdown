---
layout: post
title: "Leetcode: Majority Element"
date:   2015-01-15
comments: true
categories: Leetcode
---

***
<br />
*[Majority Element](https://leetcode.com/problems/majority-element/)*

*Given an array of size n, find the majority element. The majority element is the element that appears more than `⌊ n/2 ⌋` times.*

*You may assume that the array is non-empty and the majority element always exist in the array.*

***
<br />

题目本身比较简单。之前在某本书上（确实忘了）看到过思路，用到了[Boyer-Moore Vote Algorithm](https://en.wikipedia.org/wiki/Boyer-Moore_Majority_Vote_Algorithm)。

算法的思路可以简单描述成：如果从数组里取出两个数，发现二者不同，则删掉二者，直到整个数组中只剩下相同的数字为止。在算法的两个发明者之一Moore的网站上给出了一个简单清晰到让人抓狂的[实现方法和demo](http://www.cs.utexas.edu/~moore/best-ideas/mjrty/index.html)。

具体方法是：维护一个majority vote和vote count，分别存放当前最多的vote和最多vote的票数。依次遍历数组的元素，如果遇到的vote和当前的majority vote不相等，则--vote count，否则++vote count。如果vote count为0，则当前遇到的vote就是marjority vote。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int c = 0, v = 0; // count and vote
        for(int i = 0; i < nums.size(); ++i){
            if(c == 0) v = nums[i];
            c += v == nums[i] ? 1 : -1;
        }
        return v;
    }
};
{% endhighlight %}

值得强调的一点是，Boyer-Moore Vote Algorithm只是找出了可能成为多数元素的元素，至于是不是多数元素，还需要再扫描一遍数组来确认。在这里因为题目已经保证了这个元素的存在，所以不需要这个步骤了。

另外，这两个发明者还发明过一个非常有名的[字符串匹配算法Boyer-Moore算法](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm)。这两个老爷子联手的作品不少，基本上都是经典。详细的工作可以戳他们的主页：

[Home page of Robert Stephen Boyer](http://www.cs.utexas.edu/~boyer/)

[J Strother Moore's home page](http://www.cs.utexas.edu/users/moore/)


