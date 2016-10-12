---
layout: post
title: "Leetcode: Partition Equal Subset Sum"
date:   2016-10-11
comments: true
categories: Leetcode
---

***
<br />
[*Partition Equal Subset Sum*](https://leetcode.com/problems/partition-equal-subset-sum/)

*Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.*

*Note:*

*Both the array size and each of the array element will not exceed 100.*

*Example 1:*

*Input: [1, 5, 11, 5]*

*Output: true*

*Explanation: The array can be partitioned as [1, 5, 5] and [11].*

*Example 2:*

*Input: [1, 2, 3, 5]*

*Output: false*

*Explanation: The array cannot be partitioned into equal sum subsets.*

***
<br />

这个题大概思考了一下应该是一个NP问题，但是感觉用动态规划能解，偷懒查了一下[Wiki](https://en.wikipedia.org/wiki/Partition_problem)，做一下笔记。具体的解法是先算出整个数组的和，根据题意数组的和必须是偶数，然后取sum的一半为target，检查数组中的所有的值，如果有大于target的值，那么直接返回false，如果有等于target的值，那么返回true。通过这些检查后，再进行动态规划。

首先建立一个(target+1)*n的表dp，其中n是数组元素的个数，dp[i][j]表示下标从0到j（含nums[j]）的元素的子集能否找出一个和为i的子集，如果能dp[i][j]就是true。

递推关系为：

- dp[i][j]取决于两个值，如果dp[i][j-1]为true，说明下标0到j-1的元素就能构成和为i的子集，所以可以通过不选nums[j]来构成下标为0到j的集合的子集；

- 如果dp[i-nums[j]][j-1]为true，说明可以在下标0到j-1的元素中构成一个和为i-nums[j]的子集，这样可以通过向子集中加入nums[j]来实现构成一个和为i的子集。如果两种情况都为false，那么当前dp[i][j]就为false。

整个问题的最终结果就是dp[target][n-1]。

{% highlight c++ %}

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int len = nums.size();
        if(len < 2) return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum == 0) return true;
        if(sum % 2 == 1) return false;
        sum /= 2;
        for(int i = 0; i < len; ++i) if(nums[i] > sum) return false; else if(nums[i] == sum) return true;
        vector<vector<bool> > dp(sum+1, vector<bool>(len, false));
        dp[nums[0]][0] = true;
        for(int j = 0; j < len; ++j) if(nums[j] == 0) dp[0][j] = true;
        for(int i = 1; i <= sum; ++i) for(int j = 1; j < len; ++j) dp[i][j] = dp[i][j-1] || (i-nums[j] >= 0 && dp[i-nums[j]][j-1]);
        return dp[sum][len-1];
    }
};

{% endhighlight %}
