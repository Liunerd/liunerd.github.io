---
layout: post
title: "Leetcode: Verify Preorder Serialization of a Binary Tree"
date:   2016-02-03
comments: true
categories: Leetcode
---

***
<br />
[*Verify Preorder Serialization of a Binary Tree*](https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/)

*One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.*

*For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.*

*Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.*

*Each comma separated value in the string must be either an integer or a character '#' representing null pointer.*

*You may assume that the input format is always valid, for example it could never contain two consecutive commas such as "1,,3".*

*Example 1:*

*`"9,3,4,#,#,1,#,#,2,#,6,#,#"`*

*Return `true`*

*Example 2:*

*`"1,#"`*

*Return `false`*

*Example 3:*

*`"9,#,#,1"`*

*Return false*

***
<br />

这题最直接的思路就是按照二叉树从上到下的顺序来对字符串进行分解，一个合法的字符串preorder一定可以表示为"#"（root == NULL）或者分割成一个非空的根节点（R）和R的两个子树serialize后得到的字符串sl，sr，即s = "R,sl,sr"。对sl和sr的判断可以递归调用函数自身来验证，只是这个分割在从上到下的情况下需要一次次去搜索尝试。

*代码：*

{% highlight c++ %}

class Solution {
public:
    bool isValidSerialization(string preorder) {
        int len = preorder.size(), c1 = 0;
        if(len == 0) return false;
        while(c1 < len && preorder[c1] != ',') ++c1;
        if(c1 == len) return preorder == "#"; // only one node
        if(preorder.substr(0, c1) == "#") return false; // #,xxx... -> false
        int c2 = c1 + 1;
        while(c2 < len && preorder[c2] != ',') ++c2;
        if(c2 == len) return false; // xxx,xxx -> false
        while(true){
            string left = preorder.substr(c1+1, c2 - c1 - 1), right = preorder.substr(c2+1, len - c2 - 1);
            if(isValidSerialization(left) && isValidSerialization(right)) return true;
            ++c2;
            while(c2 < len && preorder[c2] != ',') ++c2;
            if(c2 == len) return false;
        }
    }
};
{% endhighlight %}

其中加入了一些边缘情况判断，可以参考注释。然而这种方法会TLE。

很显然的在分解验证的过程中有很多重复的判断，所以可以加一个数据结构作为备忘来记录已经计算过的情况。这里可以用两种数据结构，一种是二维bool数组，table[i][j]表示从i到j这个子串是否是合法的。table可以在搜索的过程中不断更新。或者可以用两个hash表来表示验证过的子串和验证过并且合法的子串，这样也可以遇到的子串尝试直接判断，省去了递归检测的步骤。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int len = preorder.size(), c1 = 0;
        if(len == 0) return false;
        while(c1 < len && preorder[c1] != ',') ++c1;
        if(c1 == len) return preorder == "#"; // only one node
        if(preorder.substr(0, c1) == "#") return false; // #,xxx... -> false
        int c2 = c1 + 1;
        while(c2 < len && preorder[c2] != ',') ++c2;
        if(c2 == len) return false; // xxx,xxx -> false
        while(true){
            string left = preorder.substr(c1+1, c2 - c1 - 1), right = preorder.substr(c2+1, len - c2 - 1);
            if(isValidSerialization(left) && isValidSerialization(right)) return true;
            ++c2;
            while(c2 < len && preorder[c2] != ',') ++c2;
            if(c2 == len) return false;
        }
    }
};
{% endhighlight %}

hash表的版本只是用run code测试了一下，和二维bool数组的结果一样，二者都会卡在更长的测试字符串上，TLE。

最后想到了自下而上的方式对字符串进行变形，依据的规则就是如果能够在字符串中找到符合正则表达式[-\d]+,#,#,的子串（也就是一个叶子结点，左右两个孩子都是sentinel），这个子串可以被替换成一个#，而不影响最终的判断结果。这个过程很象是处理一朵菜花（花菜？西兰花？都行），不断地掐掉最小的部分，最终整个菜花将只剩下一个空的根（#）。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool isValidSerialization(string preorder) {
        if(preorder.size() == 0) return false;
        if(preorder[0] == '#') return preorder.size() == 1; // # -> true, #,xxx... -> false
        preorder += ",";
        while(true){
            string ret = helper(preorder);
            if(ret == preorder) return false;
            else if(ret == "#,") return true;
            else preorder = ret;
        }
    }
    
    string helper(string s){
        int len = s.size(), i = 0, state = 0, gap_start = 0;
        while(i < len){
            if(s[i] == '-' || (s[i] >= '0' && s[i] <= '9')){
                if(state != 0) gap_start = i;
                state = 0;
            }else if(s[i] == ','){
                ++state;
                if(state == 3) break;
            }
            ++i;
        }
        if(state == 3){
            string ret = s.substr(0, gap_start);
            ret += "#";
            ret += s.substr(i, len - i);
            return ret;
        }else return s;
    }
};
{% endhighlight %}

这里用了一个状态机，一共只有4个状态，还是比较简单的，就不画图一一说明了。
