---
layout: post
title: "Leetcode: Reverse Nodes in k-Group"
date:   2014-09-19
comments: true
categories: Leetcode
---

***
<br />
[*Reverse Nodes in k-Group*](https://leetcode.com/problems/reverse-nodes-in-k-group/)

*Given a linked list, reverse the nodes of a linked list k at a time and return its modified list.*

*If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is.*

*You may not alter the values in the nodes, only nodes itself may be changed.*

*Only constant memory is allowed.*

*For example,*

*Given this linked list: `1->2->3->4->5`*

*For k = 2, you should return: `2->1->4->3->5`*

*For k = 3, you should return: `3->2->1->4->5`*

***
<br />

思路：

这题可以利用递归的办法来解，先翻转前k个node，不足k个直接返回head，随后递归调用reverseKGroup得到链表除了前k个node以后部分翻转好的链表的头，把它直接接在翻转好的前k个node的尾部即可。

*代码：*

{% highlight c++ %}
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *reverseKGroup(ListNode *head, int k) {
        if(head == NULL) return NULL;
        if(k == 1) return head;
        ListNode* tail = head;
        int count = k;
        while(count > 1 && tail != NULL){
            --count;
            tail = tail -> next;
        }
        if(tail == NULL){
            return head;
        }else{
            ListNode* next_group = tail -> next;
            ListNode* p = head -> next;
            ListNode* next_node = p;
            ListNode* prev = head;
            while(p != tail){
                next_node = p -> next;
                p -> next = prev;
                prev = p;
                p = next_node;
            }
            tail -> next = prev;
            head -> next = reverseKGroup(next_group, k);
            return tail;
        }
    }
};
{% endhighlight %}

