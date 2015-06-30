---
layout: post
title: "Leetcode: Majority Element II"
date:   2015-06-29
comments: true
categories: Leetcode
---

***
<br />
*[Majority Element II](https://leetcode.com/problems/majority-element-ii/)*

*Given an integer array of size n, find all elements that appear more than `⌊ n/3 ⌋` times. The algorithm should run in linear time and in O(1) space.*

***
<br />

思路：

参考[Majority Element来思考]({{ site.url }}/leetcode/2015/01/15/leetcode-majority-element.html)，变化一下[Boyer Moore Vote Algorithm](https://en.wikipedia.org/wiki/Boyer-Moore_Majority_Vote_Algorithm)，因为要取出现频率大于n/3的数字，这个数字至多只能有两个，所以记录两个cadidiate vote作为最后的结果，同时记录两个cadidate的累计票数。假设我们最终得到的两个Majority Element值分别是v1和v2，累积票数为c1和c2；然后把整个给出的数组分成三部分来看，第一部分可以看成是全部由v1组成，第二部分看成是全部由v2组成，第三部分是剩下的元素，如果分别把第一第二部分和第三部分组合在一起，就可以得到一个满足Boyer Moore Vote Algorithm的情形。但是实际操作中我们不需要事先把数组分割（在知道最终结果前也不可能分割），只要稍微改变一下Boyer Moore Vote Algorithm的逻辑就好了：

- 如果c1 == c2 == 0：没有任何一个candidate，v1 = nums[i]；
- 如果c1 == 0，c2 != 0：判断nums[i]是否与v2相同，相同则++c2，不同则v1 = nums[i]；
- 如果c2 == 0，c1 !=0，类似上一种情况，交换c1和c2在上一种情况中的地位；
- 如果c1 != 0，c2 != 0，比较nums[i]和v1，v2，如果和任何一个都不相同，--c1，--c2；如果和其中一个相同，++相应的票数。

这题的要求里没有给出保证，一定有这样的cadidate，cadidate的个数可能是2个，也可能是1个或者0个。所以上面的做法只能保证在有这样的candidate的情况下，cadidate一定在v1和v2里。所以最后需要再遍历一遍整个数组，来确认v1和v2的个数都超过了`nums.size()/3`。（一直想避免这一步的，但是实在没想出什么其他的好办法。）

代码：

{% highlight c++ %}
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ret;
        int len = nums.size();
        if(len == 0) return ret;
        if(len == 1){
            ret.push_back(nums[0]);
            return ret;
        }
        if(len == 2){
            ret.push_back(nums[0]);
            if(nums[1] != nums[0]) ret.push_back(nums[1]);
            return ret;
        }
        int c1 = 0, c2 = 0, v1 = 0, v2 = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(c1 == 0 && c2 == 0){
                v1 = nums[i];
                ++c1;
            }else if(c1 == 0 && c2 != 0){
                if(v2 == nums[i]) ++c2;
                else{
                    v1 = nums[i];
                    ++c1;
                }
            }else if(c1 != 0 && c2 == 0){
                if(v1 == nums[i]) ++c1;
                else{
                    v2 = nums[i];
                    ++c2;
                }
            }else{
                if(v1 == nums[i]) ++c1;
                else if(v2 == nums[i]) ++c2;
                else{
                    --c1;
                    --c2;
                }
            }
        }
        c1 = c2 = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] == v1) ++c1;
            else if(nums[i] == v2) ++c2;
        }
        if(c1 > nums.size()/3) ret.push_back(v1);
        if(c2 > nums.size()/3) ret.push_back(v2);
        return ret;
    }
};
{% endhighlight %}

提交AC以后发现Discuss里点赞最多的算法和我写的一样。

