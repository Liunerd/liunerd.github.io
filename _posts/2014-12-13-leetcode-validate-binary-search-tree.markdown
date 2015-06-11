---
layout: post
title: "Leetcode: Validate Binary Search Tree"
date:   2014-12-13
comments: true
categories: Leetcode
---

***
<br />
[*Validate Binary Search Tree*](https://leetcode.com/problems/validate-binary-search-tree/)

*Given a binary tree, determine if it is a valid binary search tree (BST).*

*Assume a BST is defined as follows:*

*The left subtree of a node contains only nodes with keys less than the node's key.*

*The right subtree of a node contains only nodes with keys greater than the node's key.*

*Both the left and right subtrees must also be binary search trees.*

***
<br />

思路：

找出根节点的前趋节点和后继节点，验证三者的值满足从小到大的关系，再分别对根节点的左右子树递归调用isValidBST即可。

代码：
{% highlight c++ %}
/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode *root) {
        if(root == NULL) return true;
        bool lv = true, rv = true;
        if(root -> left != NULL){
            TreeNode* lc = root -> left;
            while(lc -> right != NULL) lc = lc -> right;
            lv = (root -> val > lc -> val) && isValidBST(root -> left);
        }
        if(root -> right != NULL){
            TreeNode* rc = root -> right;
            while(rc -> left != NULL) rc = rc -> left;
            rv = (root -> val < rc -> val) && isValidBST(root -> right);
        }
        return lv && rv;
    }
};
{% endhighlight %}

