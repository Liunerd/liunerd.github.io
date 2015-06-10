---
layout: post
title: "Leetcode: Gas Station"
date:   2014-10-17
comments: true
categories: Leetcode
---

***
<br />
[*Gas Station*](https://leetcode.com/problems/gas-station/)

*There are N gas stations along a circular route, where the amount of gas at station i is `gas[i]`.*

*You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from station i to its next station `(i+1)`. You begin the journey with an empty tank at one of the gas stations.*

*Return the starting gas station's index if you can travel around the circuit once, otherwise return -1.*

***
<br />

思路：

因为经过每一个位置时都是+gas[i]-cost[i]，与顺序无关，所以不管从哪个位置开始遍历都会得到同样的结果。同时因为与顺序无关，所以可以设置两个指针分别作为前进和后退指针，起始时分别指向开始和结束的位置。先向前移动前进指针，如果遇到gas不足的问题，向后移动后退指针，直到gas够用为止，遍历完后，检查一下油箱是否是负值，负值则返回-1，非负值则后退指针所在的位置就是可能的起始位置。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int len = gas.size();
        if(len == 0) return -1;
        if(len == 1) return gas[0] >= cost[0] ? 0 : -1;
        int head = 0, tail = len - 1, g = 0;
        while(head <= tail){
            while(head <= tail && g >= 0){
                g += gas[head];
                g -= cost[head];
                ++head;
            }
            while(head <= tail && g < 0){
                g += gas[tail];
                g -= cost[tail];
                --tail;
            }
        }
        return g >= 0 ? (tail + 1) % len : -1;
    }
};
{% endhighlight %}

