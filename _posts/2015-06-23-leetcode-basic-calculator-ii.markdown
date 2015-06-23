---
layout: post
title: "Leetcode: Basic Calculator II"
date:   2015-06-23
comments: true
categories: Leetcode
---

***
<br />
[*Basic Calculator II*](https://leetcode.com/problems/basic-calculator-ii/)

*Implement a basic calculator to evaluate a simple expression string.*

*The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.*

*You may assume that the given expression is always valid.*

*Some examples:*

*`"3+2*2" = 7`*

*`" 3/2 " = 1`*

*`" 3+5 / 2 " = 5`*

*Note: Do not use the `eval` built-in library function.*

***
<br />

这题是[Basic Calculator](https://leetcode.com/problems/basic-calculator/)的升级版，需要根据运算符的优先级来决定运算顺序。思路有很多。联想到编译原理的一些办法，马上就能想到的办法有reverse Polish Notation，或者建立表达式树。但这题显然没必要。

因为只有+-\*/四种运算，不涉及括号，所以整个表达式可以看成“两级”，第一级由+-两种操作组成，第二级是\*/。如果第一遍扫描我们能够计算出所有*/操作的结果，第二遍扫描只要再计算+-就可以了。两次扫描都不需要再考虑结合顺序的问题，都是从左向右计算。

根据这个思路可以想到先扫描第一遍，把字符转成int，同时计算所有\*和/，结果放到一个数据结构里。在计算\*和/的过程中，我们需要把前一次计算的结果取出，计算后再放回数据结构里。第二遍再从左向右扫描一遍表达式，求所有的+和-即可。从求值顺序可以看出，第一遍扫描需要这个数据结构有LIFO的能力，第二遍需要这个数据结构有FIFO的能力。这个数据结构是deque，当然也可以用vector来实现。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int calculate(string s) {
        deque<int> dq;
        s += "$";
        int len = s.size(), val = 0, ret = 0;
        if(s.size() == 1) return 0;
        char op = '\0';
        for(int i = 0; ; ++i){
            if(s[i] >= '0' && s[i] <= '9'){
                val *= 10;
                val += s[i] - '0';
            }else if(s[i] != ' '){
                switch(op){
                    case '\0':
                    case '+':
                    case '-':
                        dq.push_back(val);
                        break;
                    case '*':
                        val *= dq.back();
                        dq.pop_back();
                        dq.push_back(val);
                        break;
                    case '/':
                        val = dq.back() / val;
                        dq.pop_back();
                        dq.push_back(val);
                        break;
                }
                if(s[i] == '$') break;
                if(s[i] == '+' || s[i] == '-') dq.push_back(s[i] == '+' ? 1 : -1);
                op = s[i];
                val = 0;
            }
        }
        while(1){
            ret = dq.front();
            dq.pop_front();
            if(dq.empty()) break;
            int op = dq.front();
            dq.pop_front();
            int a = dq.front();
            dq.pop_front();
            ret += op*a;
            if(dq.empty()) break;
            dq.push_front(ret);
        }
        return ret;
    }
};
{% endhighlight %}

这里用到了两个技巧，一个是在字符串后先加上了一个`'$'`作为结尾标志，这样最后一个数值也可以顺利求值；另一个是用1代表+，用-1代表-，这样第二遍求值就直接变成了`ret += op*a`。

这里还有继续优化的空间。这种办法的空间复杂度为`O(n)`，但其实仔细想想，在求值完一个只有*和/操作的子串后，求值的结果就可以合并到最终的结果里了。所以可以用两套暂存中间结果的变量，分别表示之前所说的两级运算的结果。

*代码：*

{% highlight c++ %}
class Solution {
public:
    int calculate(string s) {
        int len = s.size();
        if(len == 0) return 0;
        s += "$";
        int ret1 = 0, ret2 = 0, op1 = 1, op2 = 0, val = 0;
        for(int i = 0; i <= len; ++i){
            if(s[i] >= '0' && s[i] <= '9'){
                val *= 10;
                val += s[i] - '0';
            }else if(s[i] != ' '){
                if(op2 == 0){ // 运算在第一级
                    if(s[i] == '*' || s[i] == '/'){
                        ret2 = val;
                        op2 = s[i] == '*' ? 1 : -1; // 进入第二级
                    }else{ // 运算仍然在第一级
                        ret1 += op1*val;
                        op1 = s[i] == '+' ? 1 : -1;
                    }
                }else{ // 运算在第二级
                    if(op2 == 1) ret2 *= val;
                    else if(op2 == -1) ret2 /= val;
                    if(s[i] == '*' || s[i] == '/') op2 = s[i] == '*' ? 1 : -1; // 运算仍然在第二级
                    else{ // 合并第二级的运算结果，重置第二级运算的暂存变量，运算回到第一级。
                        ret1 += ret2*op1;
                        op1 = s[i] == '+' ? 1 : -1;
                        op2 = 0;
                        ret2 = 0;
                    }
                }
                val = 0;
            }
        }
        return ret1;
    }
};
{% endhighlight %}

