---
layout: post
title: "Leetcode: Copy List with Random Pointer"
date:   2015-03-03
comments: true
categories: Leetcode
---

***
<br />
[*Copy List with Random Pointer*](https://leetcode.com/problems/copy-list-with-random-pointer/)

*A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.*

*Return a deep copy of the list.*

***
<br />

这个题目有个很巧妙的解法，就是利用链表的性质，可以在原链表的每个node后面插入新node，形成新链表：

![figure]({{ site.url }}/assets/images/2015/03/copy-list-with-random-pointer-before.jpg)

*（其中绿色的是新建的node）*

再将原链表中的random指针“平移”到新链表的node中：

![figure]({{ site.url }}/assets/images/2015/03/copy-list-with-random-pointer-after.jpg)

*（其中红色的指针表示“平移”得到的新random指针）*

最后再像解拉链一样把两个链表分开即可。

代码：

{% highlight c++ %}
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(head == NULL) return NULL;
        RandomListNode *p = head;
        while(p != NULL){
            RandomListNode *temp = new RandomListNode(p -> label);
            temp -> next = p -> next;
            p -> next = temp;
            p = temp -> next;
        }
        p = head;
        while(p != NULL){
            if(p -> random != NULL) p -> next -> random = p -> random -> next;
            p = p -> next -> next;
        }
        RandomListNode dummyhead(0);
        RandomListNode *tail = &dummyhead;
        p = head;
        while(p != NULL){
            RandomListNode *pnext = p -> next;
            p -> next = p -> next -> next;
            tail -> next = pnext;
            p = p -> next;
            tail = tail -> next;
        }
        tail -> next = NULL;
        return dummyhead.next;
    }
};
{% endhighlight %}

