---
layout: post
title: "Leetcode: Valid Number"
date:   2015-04-14
comments: true
categories: Leetcode
---

***
<br />
[*Valid Number*](https://leetcode.com/problems/valid-number/)

*Validate if a given string is numeric.*

*Some examples:*

*`"0" => true`*

*`" 0.1 " => true`*

*`"abc" => false`*

*`"1 a" => false`*

*`"2e10" => true`*

*Note: It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one.*

***
<br />

这个题目可以通过设计一个有限状态机来做。根据题意，有限状态机的状态转换图如图：

![figure]({{ site.url }}/assets/images/2015/04/valid-number.jpg)

然后就可以写代码了（C++）：

{% highlight c++ %}
const int STATE_NUM = 9;
const int TRANS_TYPE = 6;

struct FSMNode{
    bool isValid;
    int transTable[TRANS_TYPE]; // maybe use int
    FSMNode(){
        isValid = false;
        for(int i = 0; i < TRANS_TYPE; ++i) transTable[i] = -1;
    }
};

class Solution {
public:
    bool isNumber(string s) {
        int len = s.size();
        if(len == 0) return false;

        // use automata
        // construct automata
        FSMNode* FSM = new FSMNode[STATE_NUM];
        // change bool value of pos 2 and 5
        FSM[2].isValid = true;
        FSM[4].isValid = true;
        FSM[7].isValid = true;
        FSM[8].isValid = true;
        // illegal chars in pos 0, all NULL
        // space and tab in pos 1
        FSM[0].transTable[1] = 0;
        FSM[2].transTable[1] = 8;
        FSM[4].transTable[1] = 8;
        FSM[7].transTable[1] = 8;
        FSM[8].transTable[1] = 8;
        // digit in pos 2
        FSM[0].transTable[2] = 2;
        FSM[1].transTable[2] = 2;
        FSM[2].transTable[2] = 2;
        FSM[3].transTable[2] = 4;
        FSM[4].transTable[2] = 4;
        FSM[5].transTable[2] = 7;
        FSM[6].transTable[2] = 7;
        FSM[7].transTable[2] = 7;
        // pos/neg in pos 3
        FSM[0].transTable[3] = 1;
        FSM[5].transTable[3] = 6;
        // E/e in pos 4
        FSM[2].transTable[4] = 5;
        FSM[4].transTable[4] = 5;
        // . in pos 5
        FSM[0].transTable[5] = 3;
        FSM[1].transTable[5] = 3;
        FSM[2].transTable[5] = 3;
        // current state
        int curr = 0;
        for(int i = 0; i < len; ++i){
            int pos = char2num(s[i]);
            curr = FSM[curr].transTable[pos];
            if(curr == 2){
                FSM[3].isValid = true;
                FSM[3].transTable[1] = 8;
                FSM[3].transTable[4] = 5;
            }
            if(curr == -1) return false;
        }
        delete[] FSM;
        return FSM[curr].isValid;
    }
private:
    int char2num(char c){
        if(c == ' ' || c == '\t'){
            return 1;
        }else if(c >= '0' && c <= '9'){
            return 2;
        }else if(c == '+' || c == '-'){
            return 3;
        }else if(c == 'e' || c == 'E'){
            return 4;
        }else if(c == '.'){
            return 5;
        }else{
            return 0;
        }
    }
};
{% endhighlight %}

还可以写得更丧心病狂一点（换成了C）：

{% highlight c %}
enum {TRANS_TYPE = 6, STATE_NUM = 11, CHAR_TABLE_SIZE = 256};

int char2num[CHAR_TABLE_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 3, 5, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool FSMBool[STATE_NUM] = {false, false, true, true, false, true, false, false, true, true, false};
int FSMTrans[STATE_NUM][TRANS_TYPE] = {\{10, 0, 2, 1, 10, 4}, {10, 10, 2, 10, 10, 4}, {10, 9, 2, 10, 6, 3}, {10, 9, 5, 10, 6, 10}, {10, 10, 5, 10, 10, 10}, {10, 9, 5, 10, 6, 10}, {10, 10, 8, 7, 10, 10}, {10, 10, 8, 10, 10, 10}, {10, 9, 8, 10, 10, 10}, {10, 9, 10, 10, 10, 10}, {10, 10, 10, 10, 10, 10}\};

bool isNumber(char *s) {
    int i = 0, state = 0;
    for(i = 0; s[i] != '\0'; ++i){
        int jump = char2num[s[i]];
        state = FSMTrans[state][jump];
    }
    return FSMBool[state];
}
{% endhighlight %}
