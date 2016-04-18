---
layout: post
title: "Leetcode: Flatten Nested List Iterator"
date:   2016-04-18
comments: true
categories: Leetcode
---

***
<br />
[*Flatten Nested List Iterator*](https://leetcode.com/problems/flatten-nested-list-iterator/)

*Given a nested list of integers, implement an iterator to flatten it.*

*Each element is either an integer, or a list -- whose elements may also be integers or other lists.*

*Example 1:*

*Given the list `[[1,1],2,[1,1]]`,*

*By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: `[1,1,2,1,1]`.*

*Example 2:*

*Given the list `[1,[4,[6]]]`,*

*By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6]. *

***
<br />

这题的核心是一个递归定义的链表，其中链表的元素可以是一个integer或者是链表本身。Iterator的设计还是比较简单的，维护一个vector<NestedInteger>::iterator始终指向下一个合法的integer元素，hasNext的判断可以通过和原始列表的end()比较。 next直接返回整数值，每次next执行之后， 需要移动到下一个合法的integer元素，这里明显是一个DFS，可以用一个stack追踪深度来实现。

代码：

{% highlight c++ %}

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList): lst(nestedList.end()), it(nestedList.begin()) {
        skipNonInt();
    }

    int next() {
        int ret = it -> getInteger();
        ++it;
        skipNonInt();
        return ret;
    }

    bool hasNext() {
        return it != lst;
    }
private:
    typedef vector<NestedInteger>::iterator iter;
    iter lst, it;
    stack<iter> buf;

    void skipNonInt(){
        while(1){
            while(!buf.empty() && it == (buf.top() -> getList()).end()){
                it = buf.top();
                buf.pop();
                ++it;
            }
            if(it == lst) break;
            if(it -> isInteger()) break;
            else if(!(it -> getList()).empty()){
                buf.push(it);
                it = (it -> getList()).begin();
            }else ++it;
        }
    }
};

{% endhighlight %}

这里分离出跳过非Int元素的过程单独放在一个函数里，因为构造函数和next里都会调用。

P.S. 这题的数据结构有点眼熟，不就是严蔚敏版数据结构里的广义表么。


