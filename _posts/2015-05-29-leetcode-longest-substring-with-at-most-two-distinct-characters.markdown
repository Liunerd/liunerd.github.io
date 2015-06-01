---
layout: post
title: "Leetcode: Longest Substring with At Most Two Distinct Characters"
date:   2015-05-29
categories: Leetcode
---

***
<br />
[*Longest Substring with At Most Two Distinct Characters*](https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/)

*Given a string, find the length of the longest substring T that contains at most 2 distinct characters.*

*For example, Given s = “eceba”,*

*T is "ece" which its length is 3.*

***
<br />

思路：

维护以下几个位置信息：

`start`：第一种字符（CH1）起始的位置；

`i`：第一个第二种字符（CH2）出现的位置；

`j`：第一个第三种字符（CH3）出现的位置；

`k`：j之前最长连续相同字符（CH1或CH2）构成的字符串的起始位置。

关系如图所示：

![figure]({{ site.url }}/assets/2015/05/Longest-Substring-with-At-Most-Two-Distinct-Characters.jpg)

S的三个子串满足以下条件：

S<sub>i</sub>：只有CH1；

S<sub>i+1</sub>：由CH1和CH2组成；

S<sub>i+2</sub>：由CH1和CH2中的一种组成；

且有：

`s[k] != s[k-1]`

`s[i] == CH2`

`s[start] = CH1`

`s[j] == CH3`

维护一个`ret`来记录之前遇到的最大的满足条件的子串长度，每次找到满足这个条件的`start`，`i`，`j`，`k`之后，`j-start`就是只有两种字符组成的子串的长度，与`ret`比较并更新`ret`。下一次搜索的起始条件是`start=k`，`i=j`。直到`j == `字符串长度`len`之后，跳出循环，并最后一次比较`len-start`和`ret`，更新并返回`ret`即可。

代码：

{% highlight c++ %}
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int ret = 0, start = 0, i = 0, j = 0, k = 0, len = s.size();
        if(len <= 2) return len; // 如果字符串的长度不超过2，直接返回字符串长度即可。
        for(i = 1; i < len; ++i){
            if(s[i] == s[i-1]) continue; // 搜寻下一个i的位置
            k = i; //更新k
            for(j = i + 1; j < len; ++j){
                if(s[j] == s[i - 1] || s[j] == s[i]) k = s[j] != s[j - 1] ? j : k; // 搜寻下一个j的位置，并根据是否是s[j]是否有变化更新k的值
                else{
                    ret = ret > j - start ? ret : j - start; // 找到了j的位置，更新ret。
                    break;
                }
            }
            i = j - 1; // 更新i
            if(j == len) break; // 如果已经走到了字符串尾部，跳出循环
            start = k; // 更新start
        }
        return ret > len - start ? ret : len - start;
    }
};
{% endhighlight %}

