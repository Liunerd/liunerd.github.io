---
layout: post
title: "Leetcode: Count Complete Tree Nodes"
date:   2015-06-08
comments: true
categories: Leetcode
---

***
<br />
[*Count Complete Tree Nodes*](https://leetcode.com/problems/count-complete-tree-nodes/)

*Given a complete binary tree, count the number of nodes.*

*Definition of a complete binary tree from Wikipedia:*

*In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2^h nodes inclusive at the last level h.*

***
<br />

思路：

还是用递归的思想来做。一个complete tree的左右子树也都是complete tree，只要反复对左右子树递归调用即可。在每次调用时，如果能如果能提前判断一个树是perfect binary tree，那么只要知道它的高度就行了。所以每一步调用先计算当前树的两个“肩”的高度h，即到最左叶子结点和最右叶子结点的路径长度，如果相等，说明是满二叉树，直接返回2^h-1即可。

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
    int countNodes(TreeNode* root) {
        if(root == NULL) return 0;
        int lh = 1, rh = 1;
        TreeNode* p = root -> left;
        while(p){
            ++lh;
            p = p -> left;
        }
        p = root -> right;
        while(p){
            ++rh;
            p = p -> right;
        }
        if(lh == rh){
            return (1 << lh) - 1;
        }else{
            return 1 + countNodes(root -> left) + countNodes(root -> right);
        }
    }
};
{% endhighlight %}
