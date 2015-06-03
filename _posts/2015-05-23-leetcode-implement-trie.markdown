---
layout: post
title: "Leetcode: Implement Trie"
date:   2015-05-23
comments: true
categories: Leetcode
---

***
<br />
[*Implement Trie*](https://leetcode.com/problems/implement-trie-prefix-tree/)

*Implement a trie with insert, search, and startsWith methods. *

*Note:*

*You may assume that all inputs are consist of lowercase letters a-z.*

***
<br />

经典的数据结构，不多解释了。

*代码：*

{% highlight c++ %}
class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {
        isWord = false;
        for(int i = 0; i < 26; ++i) next[i] = NULL;
    }
    bool isWord;
    TrieNode* next[26];
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string s) {
        int n = s.size();
        TrieNode* p = root;
        for(int i = 0; i < n; ++i){
            if(p -> next[s[i] - 'a'] == NULL){
                TrieNode* temp = new TrieNode();
                p -> next[s[i] - 'a'] = temp;
            }
            p = p -> next[s[i] - 'a'];
        }
        p -> isWord = true;
    }

    // Returns if the word is in the trie.
    bool search(string key) {
        int n = key.size();
        TrieNode* p = root;
        for(int i = 0; i < n; ++i){
            if(p -> next[key[i] - 'a'] == NULL) return false;
            p = p -> next[key[i] - 'a'];
        }
        return p -> isWord;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        int n = prefix.size();
        TrieNode* p = root;
        for(int i = 0; i < n; ++i){
            if(p -> next[prefix[i] - 'a'] == NULL) return false;
            p = p -> next[prefix[i] - 'a'];
        }
        return true;
    }

private:
    TrieNode* root;
};

// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");
{% endhighlight %}
