---
layout: post
title: "Leetcode: Merge k Sorted Lists"
date:   2015-04-18
comments: true
categories: Leetcode
---

***
<br />
[*Merge k Sorted Lists*](https://leetcode.com/problems/merge-k-sorted-lists/)

*Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.*

***
<br />

核心的思想是维护一个小根[堆](http://en.wikipedia.org/wiki/Heap_%28data_structure%29)，具体算法细节和伪代码可以参考算法导论。

代码：

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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
         for(int i = 0; i < lists.size(); ++i){
              if(lists[i] == NULL){
                   lists[i] = lists[lists.size() - 1];
                   lists.pop_back();
                   --i;
              }
         }
         int len = lists.size();
         if(len == 0) return NULL;
         if(len == 1) return lists[0];
         for(int i = len/2; i >= 0; --i) heapify(lists, i);
         ListNode dummyhead(0);
         ListNode *p = &dummyhead;
         while(!lists.empty()){
              p -> next = lists[0];
              lists[0] = lists[0] -> next;
              p = p -> next;
              p -> next = NULL;
              if(lists[0] == NULL){
                   lists[0] = lists[lists.size() - 1];
                   lists.pop_back();
                   if(lists.size() == 1){
                        p -> next = lists[0];
                        lists.pop_back();
                   }else{
                        heapify(lists, 0);
                   }
              }else heapify(lists, 0);
         }
         return dummyhead.next;
    }

    void heapify(vector<ListNode*>& lists, int i){
         int n = lists.size(), l = i*2 + 1, r = i*2 + 2, smallest = i;
         if(l < n && lists[l] -> val < lists[smallest] -> val) smallest = l;
         if(r < n && lists[r] -> val < lists[smallest] -> val) smallest = r;
         if(smallest != i){
              ListNode* temp = lists[i];
              lists[i] = lists[smallest];
              lists[smallest] = temp;
              heapify(lists, smallest);
         }
    }
};
{% endhighlight %}
