---
layout: post
title: "Leetcode: Serialize and Deserialize Binary Tree"
date:   2015-11-04
comments: true
categories: Leetcode
---

***
<br />
*[Serialize and Deserialize Binary Tree](https://leetcode.com/problems/serialize-and-deserialize-binary-tree/)*

*Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.*

*Design an algorithm to serialize and deserialize a binary tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary tree can be serialized to a string and this string can be deserialized to the original tree structure.*

***
<br />

这题思路类似于按层输出一个二叉树，而这个二叉树需要注意的问题是它的每层不一定是满的。按照[leetcode给的转换方法](https://leetcode.com/faq/#binary-tree)，在字符串中只记录上层为非NULL节点的两个孩子。按照这个思路，serialize()就不难实现了：

维护一个数据结构来记录每一层的节点，对每层进行循环，如果本层某个节点不为NULL，则在返回的字符串里添加它的val值，并记录它的2个子节点。如果节点为NULL，则在返回的字符串里添加一个null。

这里需要注意一个问题，在循环中是会保存下层子节点中的NULL值的，而当前层的非NULL节点已经全部遍历过以后，需要做一个判断，看下层是否还有非NULL节点，如果有，需要把本层的所有剩下的NULL节点遍历完，继续下层循环，否则就可以直接退出了。

deserialize()的过程就可以反过来推出了，每读到一个值，就建立一个新节点，并添加在上一层的对应父节点下。此处只需记录父层的非NULL节点，并且如果父层有n个非NULL节点，子层在给出的字符串中应该对应有2*n个元素（最后一层除外，可能小于2*n）。

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
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if(!root) return "[]";
        vector<vector<TreeNode *> > buf(2, vector<TreeNode*>());
        string ret("[");
        int curr = 0, next = 1, count = 1;
        buf[curr].push_back(root);
        while(count){
            int len = buf[curr].size(), nextcount = 0;
            for(int i = 0; i < len; ++i){
                if(!buf[curr][i]) ret += "null,";
                else{
                    --count;
                    ret += itoa(buf[curr][i] -> val);
                    ret += ",";
                    nextcount += (buf[curr][i] -> left != NULL) + (buf[curr][i] -> right != NULL);
                    buf[next].push_back(buf[curr][i] -> left);
                    buf[next].push_back(buf[curr][i] -> right);
                    // delete buf[curr][i];
                    if(count == 0 && nextcount == 0) break;
                }
            }
            count = nextcount;
            buf[curr].clear();
            curr = next;
            next = (next + 1) % 2;
        }
        ret[ret.size() - 1] = ']';
        return ret;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if(data == "[]") return NULL;
        int s = 1, e = 1, len = data.size(), curr = 0, next = 1;
        vector<vector<TreeNode *> > buf(2, vector<TreeNode*>());
        while(e < len && data[e] != ']' && data[e] != ',') ++e;
        string numstr = data.substr(s, e-s);
        TreeNode *root = new TreeNode(atoi(numstr.c_str()));
        buf[curr].push_back(root);
        ++e;
        s = e;
        while(e < len){
            int n = buf[curr].size();
            for(int i = 0; e < len && i < 2*n; ++i){
                while(e < len && data[e] != ']' && data[e] != ',') ++e;
                numstr = data.substr(s, e-s);
                if(numstr != "null"){
                    TreeNode *p = new TreeNode(atoi(numstr.c_str()));
                    buf[next].push_back(p);
                    if(i % 2 == 0) buf[curr][i/2] -> left = p;
                    else buf[curr][i/2] -> right = p;
                }
                ++e;
                s = e;
            }
            buf[curr].clear();
            curr = next;
            next = (next + 1) % 2;
        }
        return root;
    }

    string itoa(int n){
        char buf[20];
        sprintf(buf, "%d", n);
        return string(buf);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));

{% endhighlight %}

这里还有一个小插曲就是serialize遍历后不要删除原节点。第一次做的时候下意识地把资源回收了，结果会RTE。
