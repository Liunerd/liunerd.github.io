---
layout: post
title: "Leetcode: Implement Stack using Queues"
date:   2015-06-11
comments: true
categories: Leetcode
---

***
<br />
[*Implement Stack using Queues*](https://leetcode.com/problems/implement-stack-using-queues/)

*Implement the following operations of a stack using queues.*

- *push(x) -- Push element x onto stack.*

- *pop() -- Removes the element on top of the stack.*

- *top() -- Get the top element.*

- *empty() -- Return whether the stack is empty.*

*Notes:*

- *You may assume that all operations are valid (for example, no pop or top operations will be called on an empty stack).*

- *Depending on your language, queue may not be supported natively. You may simulate a queue by using a list or deque (double-ended queue), as long as you use only standard operations of a queue -- which means only push to back, pop from front, size, and is empty operations are valid.*

***
<br />

思路：

Queue是FIFO，如果需要在出Queue处能直接取出最后一个push的元素，需要首先把最后一个元素调整到出口。这个调整可以放在push/pop阶段也可以放在pop/top阶段。实际应用中可以根据两种行为调用的频率进行优化选择。这种思想也可以看作是懒惰（放在pop/top阶段）或非懒惰（放在push/pop阶段）策略。

*代码，移位放在pop/top阶段：*

{% highlight c++ %}
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        data.push(x);
    }

    // Removes the element on top of the stack.
    void pop(void) {
        shift(data.size() - 1);
        data.pop();
    }

    // Get the top element.
    int top(void) {
        shift(data.size() - 1);
        int ret = data.front();
        shift(1);
        return ret;
    }

    // Return whether the stack is empty.
    bool empty(void) {
        return data.empty();
    }
    
    void shift(int n){
        for(int i = 0; i < n; ++i){
            int temp = data.front();
            data.pop();
            data.push(temp);
        }
    }
    
private:
    queue<int> data;
};
{% endhighlight %}

*代码，移位放在push/pop阶段：*

{% highlight c++ %}
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        shift(1);
        data.push(x);
        shift(data.size() - 1);
    }

    // Removes the element on top of the stack.
    void pop(void) {
        data.pop();
        shift(data.size() - 1);
    }

    // Get the top element.
    int top(void) {
        return data.front();
    }

    // Return whether the stack is empty.
    bool empty(void) {
        return data.empty();
    }
    
    void shift(int n){
        if(data.empty()) return;
        for(int i = 0; i < n; ++i){
            int temp = data.front();
            data.pop();
            data.push(temp);
        }
    }
    
private:
    queue<int> data;
};
{% endhighlight %}

