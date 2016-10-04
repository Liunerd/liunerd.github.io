---
layout: post
title: "Leetcode: Binary Watch"
date:   2016-09-19
comments: true
categories: Leetcode
---

***
<br />
[*Binary Watch*](https://leetcode.com/problems/binary-watch/)

*A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).*

*Each LED represents a zero or one, with the least significant bit on the right.*

![Image](https://upload.wikimedia.org/wikipedia/commons/8/8b/Binary_clock_samui_moon.jpg)

*For example, the above binary watch reads "3:25".*

*Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.*

*Example:*

*Input: `n = 1`*

*Return: `["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]`*

*Note:*

*The order of output does not matter.*

*The hour must not contain a leading zero, for example "01:00" is not valid, it should be "1:00".*

*The minute must be consist of two digits and may contain a leading zero, for example "10:2" is not valid, it should be "10:02".*

***
<br />

这题首先可以用一个10 bit数字来表示具体的事件，用一个int就可以装下这个结构，0表示灭灯，1表示亮灯。粗看是一个生成排列的问题，但是可以不用那么复杂，10个bit也就是从0到2047的范围，完全可以遍历一下，数出每个int其中的1的个数，再转换成string即可。这个复杂度是O(1)的。

代码：

{% highlight c++ %}

#define GETM(a) (a & 0x3F)
#define GETH(a) (a >> 6)

class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> ret;
        for(int clock = 0; clock < 0x3FF; ++clock) if(countDig(clock) == num && validClock(clock)) ret.push_back(int2ClockStr(clock));
        return ret;
    }
    int countDig(int n){
        int ret = 0;
        for(int i = 0; i < 11; ++i) ret += (n >> i) & 0x01;
        return ret;
    }
    bool validClock(int clock){ return (GETM(clock) < 60) && (GETH(clock) < 12); }
    string int2ClockStr(int clock){
        string ret;
        int min = GETM(clock), hr = GETH(clock);
        if(hr/10 > 0) ret.append(1, '0' + hr/10);
        ret.append(1, '0' + hr%10);
        ret.append(1, ':');
        ret.append(1, '0' + min/10);
        ret.append(1, '0' + min%10);
        return ret;
    }
};

{% endhighlight %}
