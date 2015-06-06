---
layout: post
title: "Leetcode: Dungeon Game"
date:   2015-02-03
comments: true
categories: Leetcode
---

***
<br />
[*Dungeon Game*](https://leetcode.com/problems/dungeon-game/)

*The demons had captured the princess (P) and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of M x N rooms laid out in a 2D grid. Our valiant knight (K) was initially positioned in the top-left room and must fight his way through the dungeon to rescue the princess.*

*The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.*

*Some of the rooms are guarded by demons, so the knight loses health (negative integers) upon entering these rooms; other rooms are either empty (0's) or contain magic orbs that increase the knight's health (positive integers).*

*In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.*

*Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.*

*For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT-> RIGHT -> DOWN -> DOWN.*

|| -2 (K) || -3 || 3 ||
|| -5 || -10 || 1 ||
|| 10 || 30 || -5 (P) ||

*Notes:*

*- The knight's health has no upper bound.*

*- Any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.*

***
<br />

还是动态规划，这里采用从终点向起点倒推的方法来想比较简单一些，重点是要理清dp的起始条件和递推关系。

*条件：*

- Kight在途径路径上的每一个格子时血量必须>0；

- Kight只能向下或者向右移动；

定义一个table，table(i, j)表示从这点出发走到终点所需要的最少血量。

初始条件：计算走到最右下角（终点）时所需的最小血量，值为`1-dungeon[m-1][n-1]`，如果这个值为负值，说明在该点只需要1点血量就行。

递推：经过点(i, j)后，Kight有两条路可以选择，向下或者向右。找出这条路所需要的最小值，即min(table[i][j+1], table[i+1][j])，减去当前点(i, j)的值，即当前点所需的最小血量。注意，和终点一样，如果这个值是负值，说明在该点只需要1点血量即可。

另外，在初始完终点后可以先初始化一下最下一行和最右一列，当Kight位于这两块区域的任意一点时，只有一条路可以走到终点，初始化的办法参考普通点初始化的办法，不过只需要考虑一个方向即可。

*代码，在原地做的dp：*

{% highlight c++ %}
class Solution {
public:
    int calculateMinimumHP(vector<vector<int> > &dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        dungeon[m-1][n-1] = 1 - dungeon[m-1][n-1];
        if(dungeon[m-1][n-1] <= 0) dungeon[m-1][n-1] = 1;
        for(int i = n-2; i >= 0; --i){
            dungeon[m-1][i] = dungeon[m-1][i+1] - dungeon[m-1][i];
            if(dungeon[m-1][i] <= 0) dungeon[m-1][i] = 1;
        }
        for(int i = m-2; i >= 0; --i){
            dungeon[i][n-1] = dungeon[i+1][n-1] - dungeon[i][n-1];
            if(dungeon[i][n-1] <= 0) dungeon[i][n-1] = 1;
        }
        for(int i = m-2; i >= 0; --i){
            for(int j = n-2; j >= 0; --j){
                int min = dungeon[i][j+1] < dungeon[i+1][j] ? dungeon[i][j+1] : dungeon[i+1][j];
                dungeon[i][j] = min - dungeon[i][j];
                if(dungeon[i][j] <= 0) dungeon[i][j] = 1;
            }
        }
        return dungeon[0][0];
    }
};
{% endhighlight %}


