---
layout: post
title: "Leetcode: Peeking Iterator"
date:   2015-09-21
comments: true
categories: Leetcode
---

***
<br />
*[Peeking Iterator](https://leetcode.com/problems/peeking-iterator/)*

*Given an Iterator class interface with methods: next() and hasNext(), design and implement a PeekingIterator that support the peek() operation -- it essentially peek() at the element that will be returned by the next call to next().*

*Here is an example. Assume that the iterator is initialized to the beginning of the list: [1, 2, 3].*

*Call next() gets you 1, the first element in the list.*

*Now you call peek() and it returns 2, the next element. Calling next() after that still return 2.*

*You call next() the final time and it returns 3, the last element. Calling hasNext() after that should return false.*

***
<br />

这个题的题面有点啰嗦，看了代码才明白。出题者的要求是这个PeekingIterator对数据的具体操作需要完全依赖于父类Iterator的实现，只能调用父类的next()和hasNext()两个函数，在此基础上添加一个peek()函数来查看下一个元素。因为hasNext()方法并不会移动Iterator，所以暂且不看，根据剩下两个函数peek()和next()的调用情况，这个PeekingIterator会有两种状态：

一种是上一个非hasNext()操作不是peek()，此时当前Iterator的位置是正确的，调用PeekingIterator的next()或者hasNext()可以直接使用父类的实现。如果需要执行peek()，唯一能够得到vector中下一个元素的方法还是要依赖调用父类的next()实现，在这种情况下，PeekingIterator进入了另一个状态，即：

上一个非hasNext()操作是peek()，此时我们可以想象有一个影子Iterator留在了原地，而目前Iterator的真身已经移动到了影子Iterator的下一个位置。而PeekingIterator对外展现的行为应该取决于影子Iterator的位置。在这种情况下如果再调用next()，我们需要返回当前Iterator真身指向的元素，这种功能是父类中没有提供的，所以需要在peek()的时候记录peek到的值。

这样思路就清楚了。这里只需要两个变量分别记录当前PeekingIterator的状态和上一次peek()到的值，二者分别用bool和int类型就行了。

逻辑也很简单，代码：

{% highlight c++ %}

// Below is the interface for Iterator, which is already defined for you.
// **DO NOT** modify the interface for Iterator.
class Iterator {
    struct Data;
    Data* data;
public:
    Iterator(const vector<int>& nums);
    Iterator(const Iterator& iter);
    virtual ~Iterator();
    // Returns the next element in the iteration.
    int next();
    // Returns true if the iteration has more elements.
    bool hasNext() const;
};


class PeekingIterator : public Iterator {
public:
    PeekingIterator(const vector<int>& nums) : Iterator(nums), peeked(false), now(0) {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {
        if(!peeked){
            peeked = true;
            now = Iterator::next();
        }
        return now;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {
        if(peeked){
            peeked = false;
            return now;
        }else return Iterator::next();
    }

    bool hasNext() const {
        if(peeked) return true;
        return Iterator::hasNext();
    }
private:
    bool peeked;
    int now;
};

{% endhighlight %}

还有一个想提一下的点就是在调用peek()有可能越界。这里的题意看起来应该是通过父类的next()或者调用者自己保证先使用hasNext()来实现了。

回顾一下这题还是非常简单的，吓人的是题面，然后用到了一点面向对象的继承。所以遇到问题不要慌，弄明白出题者需要你给出什么样的答案才是最重要的。#都是人生经验不说了都是泪#
