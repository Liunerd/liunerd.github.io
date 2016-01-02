---
layout: post
title: "Leetcode: Minimum Height Trees"
date:   2015-11-19
comments: true
categories: Leetcode
---

***
<br />
[*Minimum Height Trees*](https://leetcode.com/problems/minimum-height-trees/)

*For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.*

*Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).*

*You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.*

***
<br />

在一个图里，如果给定的节点为根做一个树，用BFS就能求出这个树的高度，所以这题最直观的思路就是对所有点进行BFS，算出不同节点为根时树的深度，最后求一个最小值即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int> >& edges) {
        vector<int> ret;
        if(n == 0) return ret;
        if(n == 1) return vector<int>(1, 0);
        vector<vector<int> > e(n, vector<int>());
        int nedges = edges.size(), min = 1;
        for(int i = 0; i < nedges; ++i){
            e[edges[i].first].push_back(edges[i].second);
            e[edges[i].second].push_back(edges[i].first);
        }
        vector<int> depth(n, 0);
        for(int i = 0; i < n; ++i) depth[i] = helper(i, n, e);
        for(int i = 0; i < n; ++i) min = min < depth[i] ? min : depth[i];
        for(int i = 0; i < n; ++i) if(depth[i] == min) ret.push_back(i);
        return ret;
    }
    
    int helper(int i, int n, vector<vector<int> >& edges){
        vector<bool> visited(n, false);
        visited[i] = true;
        queue<int> q;
        vector<int> depth(n, 0);
        q.push(i);
        int max = -1;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(int j = 0; j < edges[node].size(); ++j){
                int nextnode = edges[node][j];
                if(!visited[nextnode]){
                    visited[nextnode] = true;
                    depth[nextnode] = depth[node] + 1;
                    q.push(nextnode);
                }
            }
        }
        for(int j = 0; j < n; ++j) max = max > depth[j] ? max : depth[j];
        return max;
    }
};
{% endhighlight %}

这种方法会TLE。时间复杂度上，假设节点个数为V，边的个数为E，则helper函数的复杂度为O(E)+O(V)，因为这里假设了一定能构成一个树（无向无环图），所以E为V-1，E和V是同阶的，所以复杂度为O(V)或者O(E)。在findMinHeightTrees里对helper调用了V次，所以整体的复杂度为O(V*E)。

再仔细想一想，不管有几种能够构成最矮树的方法，最矮树的根节点 一定是在整个图中的最长路径上的。这个结论可以用反证法来证明，假设MHT根节点（R）不在最长路径上，那么这个节点必然能通过某条其他路径连接到最长路径上的某个节点（P）上。假设R到P长度为L，P到最长路径两端（节点A和节点B）的长度为La和Lb，以P为端点，P和R所在的最长子路径长度为Lr，则有以下结论：

`L <= Lr;`

`Lr < La;` （否则可以以A-P-R-构造长为Lr+Lb的更长路径）

`Lr < Lb;` （道理同上）

所以R为根的这棵树的高度为L+max(La, Lb, Lr-L) = L+max(La, Lb)。而以P为根节点的树高度为max(La, Lb, Lr) = max(La, Lb)。所以以R为根节点的树一定会高于以P为根的树。所以MHT的根节点一定在最长路径上，并且应该是最长路径的中点（奇数长度，偶数长度为中点对）。

所以这个问题就退化成了：如何找出一个无向无环图中的最长路径，也就是这个图的直径。

这个问题的解还是比较简单的，从任意点做BFS，找出所有距离最远的点，再分别从这些点开始做BFS，找出这些点到离它们最远的点的路径，再找出这些路径的中间点就OK了。

*代码：*

{% highlight c++ %}
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<pair<int, int> >& edges) {
        vector<int> ret;
        if(n == 0) return ret;
        if(n == 1) return vector<int>(1, 0);
        vector<vector<int> > e(n, vector<int>());
        int nedges = edges.size();
        for(int i = 0; i < nedges; ++i){
            e[edges[i].first].push_back(edges[i].second);
            e[edges[i].second].push_back(edges[i].first);
        }
        vector<int> path = findRemotePath(0, n, e);
        int remote = path[path.size() - 1];
        path = findRemotePath(remote, n, e);
        if(path.size() % 2 == 0){
            ret.push_back(path[path.size()/2 - 1]);
            ret.push_back(path[path.size()/2]);
        }else ret.push_back(path[path.size()/2]);
        return ret;
    }
    
    vector<int> findRemotePath(int i, int n, vector<vector<int> >& edges){
        vector<bool> visited(n, false);
        visited[i] = true;
        queue<int> q;
        q.push(i);
        vector<int> from(n, -1);
        vector<int> distance(n, 0);
        vector<int> ret;
        while(!q.empty()){
            int node = q.front();
            q.pop();
            for(int j = 0; j < edges[node].size(); ++j){
                int next = edges[node][j];
                if(!visited[next]){
                    visited[next] = true;
                    q.push(next);
                    distance[next] = distance[node] + 1;
                    from[next] = node;
                }
            }
        }
        int max = 0, p = i;
        for(int j = 0; j < n; ++j){
            if(max < distance[j]){
                max = distance[j];
                p = j;
            }
        }
        while(p != i){
            ret.push_back(p);
            p = from[p];
        }
        ret.push_back(i);
        reverse(ret.begin(), ret.end());
        return ret;
    }
};
{% endhighlight %}

开个脑洞：这个模型有点类似网页模型，如果这个图是动态的，应该可以用类似权重传递的方法来做比如page rank？
