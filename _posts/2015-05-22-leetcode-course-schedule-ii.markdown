---
layout: post
title: "Leetcode: Course Schedule II"
date:   2015-05-22
comments: true
categories: Leetcode
---

***
<br />
[*Course Schedule II*](https://leetcode.com/problems/course-schedule-ii/)

*There are a total of n courses you have to take, labeled from `0` to `n - 1`.*

*Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: `[0,1]`*

*Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.*

*There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.*

*For example:*

*`2, [[1,0]]`*

*There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is `[0,1]`*

*`4, [[1,0],[2,0],[3,1],[3,2]]`*

*There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is `[0,1,2,3]`. Another correct ordering is `[0,2,1,3]`.*

***
<br />

这题是[Course Schedule](https://leetcode.com/problems/course-schedule/)的升级版本，在判断DAG的基础上要输出拓扑排序的结果。思路[和Course Schedule一样]({{ site.url }}/leetcode/2015/05/22/leetcode-course-schedule.html)，只是需要加一个构造输出结果的过程。

代码：
{% highlight c++ %}

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int> >& prerequisites) {
        vector<int> ret;
        vector<int> notpossible;
        if(numCourses == 0) return ret;

        vector<int> indeg(numCourses, 0);
        vector<vector<int> > edges(numCourses, vector<int>());
        vector<bool> visited(numCourses, false);
        int count = 0, nedge = prerequisites.size();

        for(int i = 0; i < nedge; ++i){
            ++indeg[prerequisites[i].first];
            edges[prerequisites[i].second].push_back(prerequisites[i].first);
        }

        while(count < numCourses){
            int i = 0;
            for(; i < numCourses; ++i) if(!visited[i] && indeg[i] == 0) break;
            if(i == numCourses) return notpossible;
            visited[i] = true;
            ++count;
            ret.push_back(i);
            int nout = edges[i].size();
            for(int j = 0; j < nout; ++j) --indeg[edges[i][j]];
        }
        return ret;
    }
};

{% endhighlight %}

