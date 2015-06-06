---
layout: post
title: "Leetcode: Course Schedule"
date:   2015-05-22
comments: true
categories: Leetcode
---

***
<br />
[*Course Schedule*](https://leetcode.com/problems/course-schedule/)

*There are a total of n courses you have to take, labeled from `0` to `n - 1`.*

*Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: `[0,1]`*

*Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?*

*For example:*

*`2, [[1,0]]`*

*There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.*

*`2, [[1,0],[0,1]]`*

*There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.*

***
<br />

图论中的一个典型题目，求有向图的[拓扑排序](http://en.wikipedia.org/wiki/Topological_sorting)，这里相对简化了一些，只需要判断一个图是否是[DAG](http://en.wikipedia.org/wiki/Directed_acyclic_graph)。

*思路：*

所有的拓扑排序都从一个入度为0的点开始（本例中就是一个不需要任何铺垫课程的课程），从图中移除该点和从它发出的所有边。重复这一过程直到所有的点都移除（表明该图是一个DAG）或者剩余的点里没有入度为0的点了（不是DAG）。

*代码：*

{% highlight c++ %}
class Solution {
public:
    bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
        if(numCourses == 0 || prerequisites.empty()) return true;
        int nedge = prerequisites.size();

        vector<int> indeg(numCourses, 0);
        vector<vector<int> > edges(numCourses, vector<int>());
        vector<bool> visited(numCourses, false);
        int count = 0;

        for(int i = 0; i < nedge; ++i){
            ++indeg[prerequisites[i].first];
            edges[prerequisites[i].second].push_back(prerequisites[i].first);
        }

        while(count < numCourses){
            int i = 0;
            for(; i < numCourses; ++i) if(!visited[i] && indeg[i] == 0) break;
            if(i == numCourses) return false;
            visited[i] = true;
            int nout = edges[i].size();
            for(int j = 0; j < nout; ++j) --indeg[edges[i][j]];
            ++count;
        }
        return true;
    }
};
{% endhighlight %}


