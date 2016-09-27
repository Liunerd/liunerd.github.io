---
layout: post
title: "Leetcode: Queue Reconstruction by Height"
date:   2016-09-26
comments: true
categories: Leetcode
---

***
<br />
[*Queue Reconstruction by Height*](https://leetcode.com/problems/queue-reconstruction-by-height/)

*Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.*

*Note:*

*The number of people is less than 1,100.*

*Example*

*Input:*

*`[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]`*

*Output:*

*`[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]`*

***
<br />

一道很有意思的题，每个人的信息里除了有自己的高度h以外还有此人前面的人里面比自己高/等高的人的个数k。通过题意可以知道如果两个人有相同的h，那么拥有较小k的那个人应该排在前面。

既然这样的话，可以试试采用插入的方法，插入法每一次插入决定的是一个元素的相对位置，只要能保证后面插入的元素不再影响已经插入元素的相对位置，就能保证最后得到的是正确的序列。根据这个思想，构造一个新队列，先把身高最高的人按照k从小到大插入到新队列里，因为最高的人之间的相对位置只会相互影响，而不受其他任何人影响，外界的干扰因素最小；然后再根据来处理次高的人，等等。通过这样递推，不难发现，对于每一个人，如果比他高或者等高但k比他小的人都已经确定自己在Queue里的相对位置了，那么队列里剩下的人再插入时，等高而k比较大的人会插入在队列的后半部分，h较小的人对其相对位置构不成影响，所以他的相对位置已经确定了。

实际执行算法时，可以用sort的第三个参数，构造一个匿名函数，吧people按照h从大到小，等h时k从小到大的条件进行排列。另外在插入时可以发现一个有趣的特点，就是当前处理的people的k值刚好就是他在当前队列里的位置，插入执行起来就更方便了。

{% highlight c++ %}

class Solution {
public:
    vector<pair<int, int> > reconstructQueue(vector<pair<int, int> >& people) {
        int len = people.size();
        if(len <= 1) return people;
        sort(people.begin(), people.end(), [](const pair<int, int> &a, const pair<int, int> &b){ return a.first == b.first ? a.second < b.second : a.first > b.first; });
        vector<pair<int, int> > ret(len, pair<int, int>(0, 0));
        for(int i = 0; i < len; ++i){
            for(int j = len-1; j > people[i].second; --j) ret[j] = ret[j-1];
            ret[people[i].second] = people[i];
        }
        return ret;
    }
};
{% endhighlight %}

复杂度方面，sort是O(nlogn)，插入是O(n^2)，所以最后的复杂度是O(n^2)。

这题就是考量了一个插入法和归纳法的应用。其实数学归纳法在很多算法设计问题中堪称大杀器，推荐一本书[算法引论](https://book.douban.com/subject/1436134/)，里面围绕归纳法介绍了很多算法设计的技巧。

