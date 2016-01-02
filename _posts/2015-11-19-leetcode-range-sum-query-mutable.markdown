---
layout: post
title: "Leetcode: Range Sum Query - Mutable"
date:   2015-11-19
comments: true
categories: Leetcode
---

***
<br />
[*Range Sum Query - Mutable*](https://leetcode.com/problems/range-sum-query-mutable/)

*Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.*

*The update(i, val) function modifies nums by updating the element at index i to val.*

*Example:*

{% highlight c++ %}
Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
{% endhighlight %}

*Note:*

*-The array is only modifiable by the update function.*

*-You may assume the number of calls to update and sumRange function is distributed evenly.*

***
<br />

这题首先想到的做法是可以在[Range Sum Query - Immutable]({{ site.url }}/leetcode/2015/11/19/leetcode-range-sum-query-immutable.html)的基础上改进一下，当调用update的时候更新一下两个数组。

*代码：*

{% highlight c++ %}
class NumArray {
public:
    NumArray(vector<int> &nums) {
        len = nums.size();
        sum = 0;
        for(int i = 0; i < len; ++i){
            sum += nums[i];
            sum_left.push_back(sum);
        }
        if(sum) sum_right.push_back(sum);
        for(int i = 1; i < len; ++i) sum_right.push_back(sum - sum_left[i-1]);
    }

    void update(int i, int val) {
        int diff = val - (sum_left[i] - sum + sum_right[i]);
        if(diff){ // diff not eqal to 0
            for(int j = i; j < len; ++j) sum_left[j] += diff;
            for(int j = 0; j <= i; ++j) sum_right[j] += diff;
            sum += diff;
        }
    }

    int sumRange(int i, int j) {
        return sum_left[j] - sum + sum_right[i];
    }
    
    vector<int> sum_left, sum_right;
    int sum, len;
};
{% endhighlight %}

新建数据结构和update的复杂度是O(n)，sumRange的复杂度是O(1)。这种方法会TLE。。。

在仔细看一下，有一句提示：

*You may assume the number of calls to update and sumRange function is distributed evenly.*

说明调用update并不是一个小概率事件，如果是，则之前的做法可能还行得通。这样看来，就需要sumRange分担一部分时间复杂度了。

比O(n)小的复杂度很自然就想到了O(logn)。这种复杂度往往又是在树型的数据结构里出现的。这里可以选择使用一个平衡二叉树，其中叶子结点顺序对应每一个元素，中间节点记录其子树中的所有叶子结点值的和。因为输入是一个vector，我们已经知道了有多少个元素，所以可以直接构造一个满二叉树出来，多出来的叶子结点置为0。如果在空间上更加精简一点，完全可以用一个数组来存放所有的元素。

*代码：*

{% highlight c++ %}
class NumArray {
public:
    NumArray(vector<int> &nums): len(nums.size()), talen(0), level(1) {
        int n = len;
        while(n){
            ++level;
            n = n >> 1;
        }
        talen = (1 << level) - 1;
        ta.resize(talen, 0);
        for(int i = 0; i < len; ++i) ta[talen/2 + i] = nums[i];
        for(int i = talen/2 - 1; i >= 0; --i) ta[i] = ta[i*2+1] + ta[i*2+2];
    }

    void update(int i, int val) {
        i += talen/2;
        int diff = val - ta[i];
        ta[i] = val;
        if(!diff) return;
        do{
            i = (i-1)/2;
            ta[i] += diff;
        }while(i);
    }

    int sumRange(int i, int j) {
        int cover = 1 << (level - 1);
        if(j == len-1) j = cover - 1;
        int p = helper(i, cover, j - i + 1);
        if(i + cover == j + 1) return ta[p];
        else return ta[p] + sumRange(i + cover, j);
    }

    int helper(int i, int& cover, int range){
        int p = 0, lml = 0;
        while(lml != i){
            if(i < lml + cover/2) p = p * 2 + 1;
            else{
                p = p * 2 + 2;
                lml += cover/2;
            }
            cover /= 2;
        }
        while(cover > range){
            p = p * 2 + 1;
            cover /= 2;
        }
        return p;
    }

    vector<int> ta;
    int len, talen, level;
};
{% endhighlight %}

为了操作方便直接构造了满二叉树，这样就可以不用判断是否会有子节点超出数组范围导致非法访问，空间复杂度上，假设nums的长度为n，则为了构造满二叉树而补0的叶子结点最多是n-1个，所有叶子结点的个数的worst-case是2*n-1，根据满二叉树的定义，非叶子结点的个数是叶子结点的个数-1，也就是说整个数组所占的空间大小为(2*n-1)+(2*n-1-1) = 4*n-3，所以空间复杂度为O(n)。

时间复杂度方面，新建数据结构仍然是O(n)，这个算法在调用update的时候，会找到对应的叶子结点位置，更新值之后一路向上更新parent的值，因为只有这条路径上的节点受到了影响，其他节点的值并不需要更新，所以update的复杂度为O(logn)。

sumRange的方法是，从根节点往下找，直到找到满足以下两个条件的某个节点为止：

- 1，该节点的最左叶子结点为i或者其就是i本身；

- 2，该节点的最右孩子节点（如果有的话）在i到j这个范围内。
在找这个节点的过程中，维护一个cover值，表示当前节点下的所有叶子结点的范围。找到符合上述两个条件的节点以后，对cover和ij之间的范围做一下判断，如果刚好覆盖，则直接返回节点的值，如果不够，则需要递归调用sumRange处理剩下的部分。

sumRange的时间复杂度，调用一次helper的复杂度为O(logn)，但是sumRange有一个递归调用，这个递归调用的深度与i和j之间的范围有关，假设这个范围是m，可以画个图分析一下worst-case，调用深度应该是O(logm)。所以其实sumRange的复杂度为O(logn*logm)。

继续分析，可以尝试降低树的高度，办法就是提高每个节点的度。2-3-4树是一个可行的办法，或者进一步简化成类似skip list的结构。这个场景有一个很重要的点就是没有插入操作，整个数组的长度是不变的，可以尽量去除掉动态数据结构中的那些动态和随机元素，直接设定好元素的具体组织形式。在这种设定下，每层节点数是固定的，所以仍然可以使用数组来实现底层数据结构的存储。参考一下Wiki上的Skip List的图：

![figure](https://upload.wikimedia.org/wikipedia/commons/thumb/8/86/Skip_list.svg/500px-Skip_list.svg.png)

现在需要解决的问题有：

- 1，应该有多少层；

- 2，每一层有多少个元素。

已知最底层有n个元素，一共有L层，节点的度还不能过小，则第k层应该有n^(k/L)个元素。在这里设定了两个参数，MAX_LEVEL来限制整个树的最大层数，MIN_SEG来限制每一个segment最少有几个元素。从策略方面看就是保留一定的线性，来降低树的高度。

代码：

{% highlight c++ %}
class NumArray {
public:
    NumArray(vector<int> &nums): len(nums.size()), talen(0), level(1), seg(0) {
        level = MAX_LEVEL;
        if(len <= MIN_SEG){
            seg = MIN_SEG;
            level = 1;
        }else while(1){
            seg = pow((double)len, 1.0/level);
            if(seg >= MIN_SEG) break;
            --level;
        }
        int n = len, l = level;
        level_len.resize(level);
        while(l--){
            level_len[l] = n;
            n = n / seg + 1;
        }
        talen = level_len[0];
        for(int i = 1; i < level; ++i){
            level_len[i] = level_len[i-1] * seg;
            talen += level_len[i];
        }
        ta.resize(talen, 0);
        int data_start = talen-level_len[level-1];
        for(int i = 0; i < len; ++i) ta[data_start+i] = nums[i];
        for(int i = level - 2; i >= 0; --i){
            data_start -= level_len[i];
            for(int j = 0; j < level_len[i]; ++j) for(int k = 0; k < seg; ++k) ta[data_start+j] += ta[data_start+level_len[i]+j*seg+k];
        }
    }

    void update(int i, int val) {
        int data_start = talen - level_len[level - 1];
        int diff = val - ta[data_start + i];
        if(diff){
            ta[data_start + i] = val;
            int l = level;
            while(--l){
                data_start -= level_len[l-1];
                i /= seg;
                ta[data_start+i] += diff;
            }
        }
    }

    int sumRange(int i, int j) {
        int ret = 0, data_start = talen, l = level;
        while(l--){
            data_start -= level_len[l];
            for(; i <= j && i % seg != 0; ++i) ret += ta[data_start + i];
            for(; i <= j && j % seg != seg-1; --j) ret += ta[data_start + j];
            if(l == 0) for(; i <= j; ++i) ret += ta[data_start+i];
            if(i > j) break;
            i /= seg;
            j /= seg;
        }
        return ret;
    }
    
    static const int MAX_LEVEL = 5;
    static const int MIN_SEG = 3;
    vector<int> ta;
    vector<int> level_len;
    int len, talen, level, seg;
};
{% endhighlight %}

在这个结构中，只有最高一层的节点个数没有限制，每个节点的度都是seg，整个数据结构的高度是level。每次update，只需一路寻找更新parent，需要操作的节点个数是level个，复杂度为O(L)；sumRange的复杂度为

空间复杂度方面，总的空间占用是一个等比数列n^(i/L)的和，这个和为n^(1/L) * (n-1) / (n^(1/L) - 1)。其中n^(1/L)其实就是seg，所以就变成了seg/(seg - 1) *(n-1)。不难看出来空间占用也是O(n)。
