---
layout: post
title: "Leetcode: Invert Binary Tree & 白板编程"
date:   2015-06-12
comments: true
categories: Leetcode
---

***
<br />
[*Invert Binary Tree*](https://leetcode.com/problems/invert-binary-tree/)

***
<br />

Leetcode: Invert Binary Tree & 白板编程

最近在推上看到了这样一条：

![figure]({{ site.url }}/assets/images/2015/06/tweet.jpg)

我X！不会做这题就去不了Google？Leetcode马上就出了这题（太坏了哈哈哈），吓得我赶紧找来这题（然而并没有在白板上）做了做。

思路什么真的没啥好讲的，交换每一个节点的两个孩子即可。

这题一开始估计是C/C++的Driver函数写错了，导致一直报CE害得我还紧张了一下，试了原地非原地递归非递归后来发现是Judging后报CE，所以一定是封装函数出了问题（不要问我为什么知道因为有些题目C语言封装函数是我帮着写的）。几分钟以后解决了。

*递归做法：*
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
    TreeNode* invertTree(TreeNode* root) {
        if(root){
            TreeNode *temp = root -> left;
            root -> left = root -> right;
            root -> right = temp;
            invertTree(root -> left);
            invertTree(root -> right);
        }
        return root;
    }
};
{% endhighlight %}

*非递归：*
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
    TreeNode* invertTree(TreeNode* root) {
        if(root){
            stack<TreeNode*> buf;
            buf.push(root);
            while(!buf.empty()){
                TreeNode *p = buf.top();
                buf.pop();
                if(p -> left) buf.push(p -> left);
                if(p -> right) buf.push(p -> right);
                TreeNode *temp = p -> left;
                p -> left = p -> right;
                p -> right = temp;
            }
        }
        return root;
    }
};
{% endhighlight %}

多说几句，很多人因为这件事在喷白板面试，我的想法是首先这哥们被拒掉的原因可能不仅仅是这次白板编程，或许还有其他因素决定了面试结果。当然作为一个看客这都只能是我猜测。另外，虽然感觉工作中几乎没有人会真的在白板上写程序，使得白板编程看起来像是一件没有意义的事，但换个角度看，正因为在键盘上敲程序的成本太廉价，导致很多情况下程序员还没有分析清楚问题就草草下手。白板编程恰好能考察一个程序员在动手之前是否对问题有了深刻的理解，能够想清楚该怎么做再动手。这对于公司来说很重要。在没有认清问题和明确做法之前就着急动手写，很可能导致浪费大量资源，还带来后面大量的debug工作甚至重构（虽然我觉得重构是必须的，有很多问题只有动手做过了一遍才能发现），从公司的角度来讲要尽量避免这些来降低成本。而且能在动手之前沉住气，先做好问题分析也是高手必备的素质。总之，如果Google仅仅因为这次白板编程的结果就拒掉一位优秀的程序员，我觉得非常不妥，但如果真的是这样，应该反思的人是Google，作为被面试者也没有必要纠结于面试最终的结果，老祖宗不说了么，道不同不相为谋。但是作为一个看客，我觉得肯定有些背后的事情是我们不知道的，也没必要太纠结。这件事看个热闹就好了。

P.S. 展示一下白板的<划掉>正确&lt;/划掉>用法：

![figure]({{ site.url }}/assets/images/2015/06/whiteboard.jpg)

中西人民友谊万岁！