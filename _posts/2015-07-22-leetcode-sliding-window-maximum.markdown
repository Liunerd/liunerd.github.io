---
layout: post
title: "Leetcode: Sliding Window Maximum"
date:   2015-07-22
comments: true
categories: Leetcode
---

***
<br />
*[Sliding Window Maximum](https://leetcode.com/problems/sliding-window-maximum/)*

*Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.*

***
<br />

这题的关键是如何记录当前window的最大值，并且在sliding window滑动的过程中方便地维护。

思路：Sliding window在滑动的过程中，每次会移除一个旧元素，进来一个新元素，移除的和新进的元素都可能对当前最大值产生影响。下面分开分析：

先看移除的元素，如果移除的元素不是最大值元素，最大值不变，不需要进行任何操作；如果移除的元素是最大值元素，我们需要重新找到整个window剩下k-1个元素的最大值，如果重复去做的话明显会增大算法的时间复杂度。为了减小这一步的复杂度，我们需要记录window中遇到的局部最大值（注意不仅仅是最大值）元素，这个局部最大值元素满足的条件，是从位于window内比它大且位于它左侧（数组头方向）的另一个局部最大值元素的下一个位置开始，到整个window最右端这个子序列的最大值。可以看出这个局部最大值序列是一个单调递减序列（非严格），其最左端元素就是整个window的最大值。维护这个局部最大值序列可以放新元素进入window时来做。

再来看添加新的元素，在前面所说的维护局部最大值的条件下，如果遇到新的元素，这个新的元素有可能影响到这些局部最大值，因为局部最大值序列是一个单调递减序列，所以新进元素具体能影响的范围可以从局部最大值序列的最右侧开始判断，如果新元素大于某个局部最大值，那么这个局部最大值就可以抛弃了，因为后进入window的元素一定比先进入window的元素后离开window（说白了就是个FIFO），所以抛弃的局部最大值并不会影响最终最大值的选择。

综上所述，我们用来构造局部最大值序列的辅助数据结构必须有以下功能：从一端读和取出最大值；从另一端放入新遇到的元素，并且能从这一端取出需要抛弃的局部最大值元素。明显这个数据结构是个deque。

思路清楚了以后代码就好写了。

*代码：*

{% highlight c++ %}
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();
        k = k < nums.size() ? k : nums.size();
        vector<int> ret;
        if(len == 0) return ret;
        deque<int> maxq;
        for(int i = 0; i < k; ++i){
            while(!maxq.empty() && maxq.back() < nums[i]) maxq.pop_back();
            maxq.push_back(nums[i]);
        }
        for(int i = 1; i < len - k + 1; ++i){
            ret.push_back(maxq.front());
            int last = nums[i-1], newitem = nums[i+k-1];
            if(last == maxq.front()) maxq.pop_front();
            while(!maxq.empty() && maxq.back() < newitem) maxq.pop_back();
            maxq.push_back(newitem);
        }
        ret.push_back(maxq.front());
        return ret;
    }
};
{% endhighlight %}

这个算法是O(n)复杂度的，因为它对数组的每一个元素都进行了常数次操作：一次进入window，一次移出window，可能有一次放入maxq，一次移出maxq。虽然是有两层循环嵌套，但是仍然是一个线性算法。


