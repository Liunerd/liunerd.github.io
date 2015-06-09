---
layout: post
title: "Leetcode: Basic Calculator"
date:   2015-06-09
comments: true
categories: Leetcode
---

***
<br />
[*Basic Calculator*](https://leetcode.com/problems/basic-calculator/)

*Implement a basic calculator to evaluate a simple expression string.*

*The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .*

*You may assume that the given expression is always valid.*

*Some examples:*

*`"1 + 1" = 2`*

*`" 2-1 + 2 " = 3`*

*`"(1+(4+5+2)-3)+(6+8)" = 23`*

***
<br />

思路：

这题只涉及加减两种运算，不存在结合顺序的问题，可以简单地从左到右求和。

单纯的数值计算需要维护两个数值，一个val表示当前遇到的这个操作数的值，另一个ret是求值到当前位置所得的结果。关于这两部分的逻辑比较简单，遇到的字符s[i]是数字时，val *= 10, val += s[i] - '0'，遇到非数字，把val的值加到ret上，val清零即可。在把val加到ret上的时候，需要考虑val的正负：是加val还是-val（即减去val，统一化成加法来分析）。这里需要记录两个bool值来代表符号，一个是遇到的最后一个符号，计做sign，另一个是当前操作数所在的括号里内容的正负。

举个具体的例子，假如现在表达式的形式是：

`...+ (... - (... - (...)))`

...表示算术表达式，当遇到第一个括号时，括号里所有的操作数相当于都自动前缀了一个+，遇到第二个括号时，相当于所有操作数自动前缀了+-，这两个符号可以化简为一个-。当运算进入到第三个括号时，相当于括号里的所有的数值都前缀了一个--，也就是+。这里就能看出来了，记录当前括号里内容正负的数据结构应该是一个栈（假设名叫st），遇到'('进行入栈操作，遇到')'时进行出栈操作。

所以当遇到其他字符时：

首先需要把val操作到ret里，如果sign和st.top()符号相同，val是正值，否则是负的。

遇到的是'+'：sign = true;

遇到的是'-'：sign = false;

遇到的是'('：需要入栈正在进入的这个括号内数值的正负号，如果sign和st.top()相同，入栈true（表示'+'），否则入栈false（表示'-'）。

遇到的是')'：出栈最后一个符号即可。不需要考虑sign。

遇到的是空格：只需要操作val加到ret那步即可。

另外，初始状态下，sign赋值为true（+），st里push进一个true（+）即可。

*代码：*
{% highlight c++ %}
class Solution {
public:
    int calculate(string s) {
        int len = s.size(), ret = 0, val = 0;
        stack<bool> st;
        st.push(true);
        bool sign = true;
        for(int i = 0; ; ++i){
             if(i < len && s[i] >= '0' && s[i] <= '9'){
                  val *= 10;
                  val += s[i] - '0';
             }else{
                  ret += (st.top() == sign) ? val : -val;
                  val = 0;
                  if(i == len) break;
                  switch(s[i]){
                       case '+':
                            sign = true;
                            break;
                       case '-':
                            sign = false;
                            break;
                       case '(':
                            sign = sign == st.top();
                            st.push(sign);
                            sign = true;
                            break;
                       case ')':
                              st.pop();
                  }
             }
        }
        return ret;
    }
};
{% endhighlight %}

