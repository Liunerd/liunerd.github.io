---
layout: post
title: "Leetcode: Bulls and Cows"
date:   2015-11-03
comments: true
categories: Leetcode
---

***
<br />
*[Bulls and Cows](https://leetcode.com/problems/bulls-and-cows/)*

*You are playing the following [Bulls and Cows](https://en.wikipedia.org/wiki/Bulls_and_Cows) game with your friend: You write down a number and ask your friend to guess what the number is. Each time your friend makes a guess, you provide a hint that indicates how many digits in said guess match your secret number exactly in both digit and position (called "bulls") and how many digits match the secret number but locate in the wrong position (called "cows"). Your friend will use successive guesses and hints to eventually derive the secret number.*

*For example:*

*`Secret number:  "1807"`*

*`Friend's guess: "7810"`*

*Hint: 1 bull and 3 cows. (The bull is 8, the cows are 0, 1 and 7.)*

*Write a function to return a hint according to the secret number and friend's guess, use A to indicate the bulls and B to indicate the cows. In the above example, your function should return "1A3B".*

*Please note that both secret number and friend's guess may contain duplicate digits, for example:*

*`Secret number:  "1123"`*

*`Friend's guess: "0111"`*

*In this case, the 1st 1 in friend's guess is a bull, the 2nd or 3rd 1 is a cow, and your function should return "1A1B".*

*You may assume that the secret number and your friend's guess only contain digits, and their lengths are always equal.*

***
<br />

这是一道比较简单的题，只要弄清楚bull和cow是怎么算出来的就好了，其中bull是位置和值都正确的猜测，cow是值正确但是位置不正确的猜测。这里隐含一个条件就是属于bull的位置不会在cow中重复了。可以用两个长度为10的数组分别统计非bull情况下secret和guess中的每一位，然后逐个统计其中对应较小值的和即可。

*代码：*

{% highlight c++ %}
class Solution {
public:
    string getHint(string secret, string guess) {
        int bull = 0, cow = 0, len = secret.size();
        int s[10] = {0}, g[10] = {0};
        for(int i = 0; i < len; ++i){
        	if(secret[i] == guess[i]) ++bull;
        	else{
        		++s[secret[i]-'0'];
        		++g[guess[i]-'0'];
        	}
        }
        for(int i = 0; i < 10; ++i) cow += s[i] < g[i] ? s[i] : g[i];
        char buf[20];
        sprintf(buf, "%dA%dB", bull, cow);
        return string(buf);
    }
};
{% endhighlight %}
