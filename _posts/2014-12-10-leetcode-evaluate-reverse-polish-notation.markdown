---
layout: post
title: "Leetcode: Evaluate Reverse Polish Notation"
date:   2014-12-10
comments: true
categories: Leetcode
---

***
<br />
[*Evaluate Reverse Polish Notation*](https://leetcode.com/problems/evaluate-reverse-polish-notation/)

*Evaluate the value of an arithmetic expression in [Reverse Polish Notation](http://en.wikipedia.org/wiki/Reverse_Polish_notation).*

*Valid operators are +, -, *, /. Each operand may be an integer or another expression.*

*Some examples:*

  ["2", "1", "+", "3", "*"] -> ((2 + 1) * 3) -> 9

  ["4", "13", "5", "/", "+"] -> (4 + (13 / 5)) -> 6


***
<br />

思路：

Reverse Polish Notation是编译过程中常用的一种形式化表示方法，它的一个优势就是能够明确求解顺序，不需要考虑结合的歧义。

这题可以使用一个栈来辅助操作。从左到右扫描所token，遇到数字就入栈，遇到操作符就pop栈顶的两个元素进行计算，并把结果push回栈中。

代码：
{% highlight c++ %}
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        stack<int> buff;
        int len = tokens.size();
        for(int i = 0; i < len; ++i){
            if(isOperator(tokens[i])){
                int op1 = buff.top();
                buff.pop();
                int op2 = buff.top();
                buff.pop();
                buff.push(calc(op1, op2, tokens[i][0]));
            }else{
                buff.push(str2int(tokens[i]));
            }
        }
        return buff.top();
    }
    inline bool isOperator(string c){
        return (c == "+" || c == "-" || c == "*" || c == "/");
    }
    int str2int(string& s){
        int ret = 0, p = 0, len = s.size();
        bool neg = false;
        if(s[p] == '-'){
            neg = true;
            ++p;
        }
        while(p < len){
            ret *= 10;
            ret += (s[p] - '0');
            ++p;
        }
        return neg ? -ret : ret;
    }
    int calc(int op1, int op2, char op){
        int ret = 0;
        switch(op){
            case '+':
                ret = op1 + op2;
                break;
            case '-':
                ret = op2 - op1;
                break;
            case '*':
                ret = op1 * op2;
                break;
            case '/':
                ret = op2 / op1;
                break;
            default:
                break;
        }
        return ret;
    }
};
{% endhighlight %}

另外，Polish Notation是波兰数学家Lukasiewicz发明的，因为当时特殊的沙文主义，他的工作由一位只记得他国籍而记不得名字的学者发布在美国的刊物上，所以没用他的名字命名。（论一个简单好记名字的重要性。）
