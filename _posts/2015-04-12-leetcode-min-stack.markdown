---
layout: post
title: "Leetcode: Min Stack"
date:   2015-04-12
comments: true
categories: Leetcode
---

***
<br />
[*Min Stack*](https://leetcode.com/problems/min-stack/)

*Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.*

- *`push(x)` -- Push element x onto stack.*

- *`pop()` -- Removes the element on top of the stack.*

- *`top()` -- Get the top element.*

- *`getMin()` -- Retrieve the minimum element in the stack.*

***
<br />

思路：

用两个stack来实现，一个用来存放数据，一个用来放当前遇到的最小值，getMin就直接返回top。如果当前入/出栈的数据小于等于最小值，需要执行最小值入/出栈操作。

*代码：*

{% highlight c++ %}
class MinStack {
public:
    void push(int x) {
        data.push(x);
        if(mins.empty() || x <= mins.top()) mins.push(x);
    }

    void pop() {
        if(data.empty()) return;
        if(mins.top() == data.top()) mins.pop();
        data.pop();
    }

    int top() {
        return data.top();
    }

    int getMin() {
        return mins.top();
    }
private:
    stack<int> data;
    stack<int> mins;
};
{% endhighlight %}

