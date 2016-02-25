---
layout: post
title: "Leetcode: Increasing Triplet Subsequence"
date:   2016-02-18
comments: true
categories: Leetcode
---

***
<br />
[*Increasing Triplet Subsequence*](https://leetcode.com/problems/increasing-triplet-subsequence/)

*Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.*

*Formally the function should:*

*Return true if there exists i, j, k*

*such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.*

*Your algorithm should run in O(n) time complexity and O(1) space complexity.*

*Examples:*

*Given `[1, 2, 3, 4, 5]`,*

*return `true`.*

*Given `[5, 4, 3, 2, 1]`,*

*return `false`.*

***
<br />

刚过完年脑子有点秀逗，这个题一开始还觉得挺简单的啊，然后看到是O(n)和O(1)的复杂度要求，还是考虑了一会。最初觉得简单是因为马上就想到了用一个stack来存放递增的数据，新数据只要跟栈顶数据比较即可，stack的深度满3返回真；后来发现有特殊情况这种方法并不能胜任，比如`[1,0,0,0,10,0,0,0,100]`这种。后来换了个思路，可以先这样想，如果我需要找一个长度为2的递增子序列，我只需要记录当前位置之前的最小值就好了；用一个栈确实是找出连续递增序列的方法，但是还需要额外记录之前遇到的所有长度为2的递增子序中较大的那个值，并且我们并不需要记录所有满足这种条件的值，只要记录其中最小的一个就好了。这种情况可以看作是比赛中的赛点，如果在握有赛点的情况下（已经有长度为2的连续递增序列了），只要再得一分（找到一个比赛点更大的值）就可以判断为真了。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int len = nums.size();
        if(len < 3) return false; // less than 3 elements, no any triplet
        stack<int> buf;
        int match_point = INT_MAX;
        for(int i = 0; i < len; ++i){
            if(match_point < nums[i]) return true;
            if(buf.empty()) buf.push(nums[i]);
            else if(buf.top() < nums[i]) buf.push(nums[i]);
            else{
                if(buf.size() == 2) match_point = match_point < buf.top() ? match_point : buf.top();
                while(!buf.empty() && buf.top() > nums[i]) buf.pop();
                if(buf.empty() || nums[i] > buf.top()) buf.push(nums[i]);
            }
            if(buf.size() == 3) return true;
        }
        return false;
    }
};
{% endhighlight %}
