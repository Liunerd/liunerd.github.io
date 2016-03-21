---
layout: post
title: "House Robber III"
date:   2016-03-15
comments: true
categories: Leetcode
---

***
<br />
[*House Robber III*](https://leetcode.com/problems/house-robber-iii/)

*The thief has found himself a new place for his thievery again. There is only one entrance to this area, called the "root." Besides the root, each house has one and only one parent house. After a tour, the smart thief realized that "all houses in this place forms a binary tree". It will automatically contact the police if two directly-linked houses were broken into on the same night.*

*Determine the maximum amount of money the thief can rob tonight without alerting the police.*

***
<br />

这题可以用递归来做，要么rob父节点和父节点的四个孙子节点，要么rob两个子节点。写起来还是比较简单的。

*代码：*

{% highlight c++ %}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        if(root == NULL) return 0;
        int robchild = rob(root -> left) + rob(root -> right);
        int robparent = root -> val;
        if(root -> left) robparent += rob(root -> left -> left) + rob(root -> left -> right);
        if(root -> right) robparent += rob(root -> right -> left) + rob(root -> right -> right);
        return robchild > robparent ? robchild : robparent;
    }
};
{% endhighlight %}

这个方法时间效率比较差，因为其中有很多的重复计算。优化可以采取原地存储计算结果的办法，把每个子树的最大收益值放在这个子树root的val域。最后直接返回整个树的root -> val即可。

*代码：*

{% highlight c++ %}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int rob(TreeNode* root) {
        if(root == NULL) return 0;
        helper(root);
        return root -> val;
    }

    void helper(TreeNode* root){
        if(root -> left == NULL && root -> right == NULL) return;
        if(root -> left) helper(root -> left);
        if(root -> right) helper(root -> right);
        int childval = root -> left ? root -> left -> val : 0;
        childval += root -> right ? root -> right -> val : 0;
        int parentval = root -> val;
        if(root -> left){
            parentval += root -> left -> left ? root -> left -> left -> val : 0;
            parentval += root -> left -> right ? root -> left -> right -> val : 0;
        }
        if(root -> right){
            parentval += root -> right -> left ? root -> right -> left -> val : 0;
            parentval += root -> right -> right ? root -> right -> right -> val : 0;
        }
        root -> val = childval > parentval ? childval : parentval;
    }
};

{% endhighlight %}

如果题目要求不能原地计算，那么还需要实现对树的深拷贝和删除算法，递归就可以，比较简单就不写了。
