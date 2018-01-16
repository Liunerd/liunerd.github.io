---
layout: post
title: "Leetcode: Design Log Storage System"
date:   2017-07-05
comments: true
categories: Leetcode
---

***
<br />

Leetcode: Design Log Storage System

You are given several logs that each log contains a unique id and timestamp. Timestamp is a string that has the following format: Year:Month:Day:Hour:Minute:Second, for example, 2017:01:01:23:59:59. All domains are zero-padded decimal numbers.

Design a log storage system to implement the following functions:

void Put(int id, string timestamp): Given a log's unique id and timestamp, store the log in your storage system.

int[] Retrieve(String start, String end, String granularity): Return the id of logs whose timestamps are within the range from start to end. Start and end all have the same format as timestamp. However, granularity means the time level for consideration. For example, start = "2017:01:01:23:59:59", end = "2017:01:02:23:59:59", granularity = "Day", it means that we need to find the logs within the range from Jan. 1st 2017 to Jan. 2nd 2017.

Example 1:

put(1, "2017:01:01:23:59:59");

put(2, "2017:01:01:22:59:59");

put(3, "2016:01:01:00:00:00");

retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Year"); // return [1,2,3], because you need to return all logs within 2016 and 2017.

retrieve("2016:01:01:01:01:01","2017:01:01:23:00:00","Hour"); // return [1,2], because you need to return all logs start from 2016:01:01:01 to 2017:01:01:23, where log 3 is left outside the range.

Note:

    There will be at most 300 operations of Put or Retrieve.

    Year ranges from [2000,2017]. Hour ranges from [00,23].

    Output for Retrieve has no order required.

***
<br />

这个题还是挺有意思的，首先一共只有18年的记录，所以时间长度不会无限长，可以在初始化的时候就先挖好坑，内容慢慢往里填；其次这里的时间一共有六级，年月日时分秒，其实可以简化成两级，年月一级，日时分秒一级，这样做的好处就是可以先按照月份数（18*12）初始化好存储空间，然后每个月份的内容按顺序插入即可，并且不需要考虑闰年和不同月份之间的日期差别；最后每条log可以使用`pair<int, int>`来存储，`first`位置放代表日时分秒的时间戳，`second`放`id`，这样可以直接用`<>`号来实现对两个不同log的比较，方便排序。

当然也可以第一级index只用年，第二级index使用月日时分秒，可是可以的。

最后要实现的其实就是一个遍历功能了，这个数据结构有点类似广义表但是深度只有2层，所以只需要维护两个index就可以了。

代码：

{% highlight c++ %}

#define MSIZE 18*12
#define VAL(s, i) ((s[i] - '0')*10 + (s[i+1] - '0'))
#define YEAR(s) VAL(s, 2)
#define MON(s) VAL(s, 5)
#define DAY(s) VAL(s, 8)
#define HOUR(s) VAL(s, 11)
#define MIN(s) VAL(s, 14)
#define SEC(s) VAL(s, 17)
#define DAY_MASK 1000000
#define HOUR_MASK 10000
#define MIN_MASK 100

class LogSystem {
public:
    LogSystem(): mlog(MSIZE, vector<pair<int, int> >()), mi(-1), li(-1) {
        
    }
    
    void put(int id, string timestamp) {
        pair<int, int> log(getSec(timestamp), id);
        int m = getMonth(timestamp);
        mlog[m].push_back(log);
        for(int i = mlog[m].size()-1; i > 0 && mlog[m][i] < mlog[m][i-1]; --i) swaplog(m, i, i-1);
    }
    
    vector<int> retrieve(string s, string e, string gra) {
        int sm = getMonth(s), ss = getSec(s), em = getMonth(e), es = getSec(e);
        if(gra == "Year"){
            ss = es = 0;
            sm = sm/12*12;
            em = (em/12+1)*12;
        }else if(gra == "Month"){
            ss = es = 0;
            ++em;
        }else if(gra == "Day"){
            ss = ss/DAY_MASK*DAY_MASK;
            es = (es/DAY_MASK+1)*DAY_MASK;
        }else if(gra == "Hour"){
            ss = ss/HOUR_MASK*HOUR_MASK;
            es = (es/HOUR_MASK+1)*HOUR_MASK;
        }else if(gra == "Minute"){
            ss = ss/MIN_MASK*MIN_MASK;
            es = (es/MIN_MASK+1)*MIN_MASK;
        }else if(gra == "Second"){
            ++es;
        }
        initIter(sm, ss);
        return until(em, es);
    }
    
private:
    vector<vector<pair<int, int> > > mlog;
    int mi, li; // month index and log index, -1 as illegal
    
    inline int getMonth(string ts){ return YEAR(ts)*12 + MON(ts) - 1; }
    inline int getSec(string ts){ return DAY(ts)*DAY_MASK + HOUR(ts)*HOUR_MASK + MIN(ts)*MIN_MASK + SEC(ts); }
    inline void swaplog(int m, int i, int j){
        pair<int, int> temp = mlog[m][i];
        mlog[m][i] = mlog[m][j];
        mlog[m][j] = temp;
    }
    
    inline bool iterLegal(){
        if(mi < 0 || li < 0 || mi >= MSIZE) return false;
        return true;
    }
    inline bool iterBefore(int m, int s){
        if(mi < m) return true;
        if(mi == m) return mlog[mi][li].first < s;
        return false;
    }
    
    void initIter(int m, int s){
        mi = m; li = 0;
        if(mlog[m].size() == 0) nextIter();
        while(iterLegal() && iterBefore(m, s)) nextIter();
    }
    void nextIter(){
        if(!iterLegal()) return;
        if(li + 1 < mlog[mi].size()) ++li;
        else{
            for(++mi; mi < mlog.size() && mlog[mi].size() == 0; ++mi);
            if(mi == mlog.size()){ mi = li = -1; return; }
            li = 0;
        }
    }
    
    vector<int> until(int em, int es){
        vector<int> ret;
        while(iterLegal() && iterBefore(em, es)){
            ret.push_back(mlog[mi][li].second);
            nextIter();
        }
        return ret;
    }
};

/**
 * Your LogSystem object will be instantiated and called as such:
 * LogSystem obj = new LogSystem();
 * obj.put(id,timestamp);
 * vector<int> param_2 = obj.retrieve(s,e,gra);
 */

{% endhighlight %}
