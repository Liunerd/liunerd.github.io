---
layout: post
title: "Leetcode: Binary Search Tree Iterator"
date:   2015-02-10
comments: true
categories: Leetcode
---

***
<br />
[*Binary Search Tree Iterator*](https://leetcode.com/problems/binary-search-tree-iterator/)

*Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.*

*Calling `next()` will return the next smallest number in the BST.*

*Note: `next()` and `hasNext()` should run in average O(1) time and uses O(h) memory, where h is the height of the tree.*

***
<br />

思路来自线索二叉树，线索二叉树会维护有一个域来指向下一个元素，如果直接用right指针，会使树变成一个有向有环图。所以需要用额外的一个数据结构来存储回溯指针。当前节点右孩子为空的时候，就取出这个指针；如果当前节点右孩子为空，而且存储空间中又没有存储的回溯指针时，说明到了整个树的最后一个元素。这里又可以分成两种思路：

1 - 在构造函数时就遍历整个树，先把所有的回溯指针都按顺序保存好。这种思路需要的是一个先入先出的数据结构。

2 - 另一种思路是运行时维护，通过不断存取来维护回溯指针，这个数据结构明显是个栈。

分析到题目的另一个要求：O(1)时间复杂度和O(h)空间复杂度，如果采取第一个办法，空间复杂度是O(n)，因为在创建iterator的时候把所有的回溯指针都保存了，这个值等于整个树中所有的右子树为NULL的节点的个数-1，根据二叉树的定义，这个值应该是O(n)。

下面给出两种思路的解法代码，这两种解法都可以AC。

*代码，第一种思路：*

{% highlight c++ %}
class BSTIterator {
public:
    BSTIterator(TreeNode *root): i(0), iter(NULL), v() {
        initTree(root);
        if(root != NULL){
            iter = root;
            while(iter -> left) iter = iter -> left;
        }
    }

    void initTree(TreeNode *root){
        if(root == NULL || root -> left == NULL && root -> right == NULL) return;
        if(root -> left){
            initTree(root -> left);
             v.push_back(root);
        }
        initTree(root -> right);
    }
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return iter != NULL;
    }

    /** @return the next smallest number */
    int next() {
        int ret = iter -> val;
        if(iter -> right){
            iter = iter -> right;
            while(iter -> left) iter = iter -> left;
        }else if(i < v.size()){
            iter = v[i];
            ++i;
        }else iter = NULL;
        return ret;
    }
private:
    TreeNode* iter;
    vector<TreeNode*> v;
    int i;
};
{% endhighlight %}

*代码，第二种思路：*

{% highlight c++ %}
class BSTIterator {
public:
    BSTIterator(TreeNode *root): iter(NULL) {
        iter = root;
        if(iter){
            while(iter -> left){
                s.push(iter);
                iter = iter -> left;
            }
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return iter != NULL;
    }

    /** @return the next smallest number */
    int next() {
        int ret = iter -> val;
        if(iter -> right){
            iter = iter -> right;
            while(iter -> left){
                s.push(iter);
                iter = iter -> left;
            }
        }else if(!s.empty()){
            iter = s.top();
            s.pop();
        }else iter = NULL;
        return ret;
    }
private:
    TreeNode* iter;
    stack<TreeNode*> s;
};
{% endhighlight %}

运行时间上来看，第一种要比第二种稍快一点。

