---
layout: post
title: "Leetcode: Game of Life"
date:   2016-03-02
comments: true
categories: Leetcode
---

***
<br />
[*Game of Life*](https://leetcode.com/problems/game-of-life/)

*According to the [Wikipedia's article](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life): "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."*

*Given a board with m by n cells, each cell has an initial state live (1) or dead (0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):*

*Any live cell with fewer than two live neighbors dies, as if caused by under-population.*

*Any live cell with two or three live neighbors lives on to the next generation.*

*Any live cell with more than three live neighbors dies, as if by over-population.*

*Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.*

Write a function to compute the next state (after one update) of the board given its current state.*

*Follow up:*

*Could you solve it in-place? Remember that the board needs to be updated at the same time: You cannot update some cells first and then use their updated values to update other cells.*

*In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches the border of the array. How would you address these problems?*

***
<br />

这题没啥好说的，就是对每一个位置求一下下一个状态就好，如果要做成in-place的，可以用位运算的方法，因为本身live/dead只需要最低一位就可以表示，所以这里可以用第二位来存储下一时刻的状态。遍历完所有元素之后再全部右移一位更新一下就行。

*代码：*

{% highlight c++ %}

#define ALIVE 0x01
#define NEXT_ALIVE 0x02

class Solution {
public:
    void gameOfLife(vector<vector<int> >& board) {
        int m = board.size(), n = board[0].size();
        for(int i = 0; i < m; ++i) for(int j = 0; j < n; ++j){
            int neighbors = 0;
            if(i > 0 && j > 0) neighbors += (board[i-1][j-1] & ALIVE);
            if(i > 0) neighbors += (board[i-1][j] & ALIVE);
            if(j > 0) neighbors += (board[i][j-1] & ALIVE);
            if(i > 0 && j < n-1) neighbors += (board[i-1][j+1] & ALIVE);
            if(j < n-1) neighbors += (board[i][j+1] & ALIVE) > 0;
            if(i < m-1 && j > 0) neighbors += (board[i+1][j-1] & ALIVE);
            if(i < m-1) neighbors += (board[i+1][j] & ALIVE);
            if(i < m-1 && j < n-1) neighbors += (board[i+1][j+1] & ALIVE);
            if(board[i][j]){
                if(neighbors == 2 || neighbors == 3) board[i][j] |= NEXT_ALIVE;
            }else if(neighbors == 3) board[i][j] |= NEXT_ALIVE;
        }
        for(int i = 0; i < m; ++i) for(int j = 0; j < n; ++j) board[i][j] >>= 1;
    }
};

{% endhighlight %}
