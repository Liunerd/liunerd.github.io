---
layout: post
title: "Leetcode: Clone Graph"
date:   2015-03-17
comments: true
categories: Leetcode
---

***
<br />
[*Clone Graph*](https://leetcode.com/problems/clone-graph/)

*Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.*

*OJ's undirected graph serialization:*

*Nodes are labeled uniquely.*

*We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.*

*As an example, consider the serialized graph `{0,1,2#1,2#2,2}`.*

*The graph has a total of three nodes, and therefore contains three parts as separated by #.*

1. First node is labeled as 0. Connect node 0 to both nodes 1 and 2.

2. Second node is labeled as 1. Connect node 1 to node 2.

3. Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.

Visually, the graph looks like the following:

       1
      / \
     /   \
    0 --- 2
         / \
         \_/


***
<br />

这题的做法还是[参考Copy List with Random Pointer]({{ site.url }}/leetcode/2015/03/03/leetcode-copy-list-with-random-pointer.html)，首先为旧图中的每一个node生成一个新node，再建立一条旧图node指向相应新node的边，再把旧图中的每一条边“平移”到新图中即可。

*代码：*

{% highlight c++ %}
/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if(node == NULL) return NULL;
        unordered_set<UndirectedGraphNode *> table;
        vector<UndirectedGraphNode *> old;
        
        table.insert(node);
        old.push_back(node);
        for(int i = 0; i < old.size(); ++i){
            for(int j = 0; j < old[i] -> neighbors.size(); ++j){
                if(table.find(old[i] -> neighbors[j]) == table.end()){
                    table.insert(old[i] -> neighbors[j]);
                    old.push_back(old[i] -> neighbors[j]);
                }
            }
        }
        
        int n = old.size();
        for(int i = 0; i < n; ++i){
            UndirectedGraphNode *newnode = new UndirectedGraphNode(old[i] -> label);
            old[i] -> neighbors.push_back(newnode);
        }
        
        for(int i = 0; i < n; ++i){
            int edgenum = old[i] -> neighbors.size() - 1;
            UndirectedGraphNode *newnode = old[i] -> neighbors[edgenum];
            for(int j = 0; j < edgenum; ++j){
                newnode -> neighbors.push_back(old[i] -> neighbors[j] -> neighbors[old[i] -> neighbors[j] -> neighbors.size() - 1]);
            }
        }
        
        UndirectedGraphNode *ret = old[0] -> neighbors[old[0] -> neighbors.size() - 1];
        for(int i = 0; i < n; ++i) old[i] -> neighbors.pop_back();
        return ret;
    }
};
{% endhighlight %}


