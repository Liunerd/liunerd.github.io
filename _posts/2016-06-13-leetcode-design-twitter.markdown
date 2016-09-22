---
layout: post
title: "Leetcode: Design Twitter"
date:   2016-06-13
comments: true
categories: Leetcode
---

***
<br />
[*Design Twitter*](https://leetcode.com/problems/design-twitter/)

*Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:*

- *postTweet(userId, tweetId): Compose a new tweet.*

- *getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.*

- *follow(followerId, followeeId): Follower follows a followee.*

- *unfollow(followerId, followeeId): Follower unfollows a followee.*

*Example:*

{% highlight c++ %}

Twitter twitter = new Twitter();

// User 1 posts a new tweet (id = 5).
twitter.postTweet(1, 5);

// User 1's news feed should return a list with 1 tweet id -> [5].
twitter.getNewsFeed(1);

// User 1 follows user 2.
twitter.follow(1, 2);

// User 2 posts a new tweet (id = 6).
twitter.postTweet(2, 6);

// User 1's news feed should return a list with 2 tweet ids -> [6, 5].
// Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
twitter.getNewsFeed(1);

// User 1 unfollows user 2.
twitter.unfollow(1, 2);

// User 1's news feed should return a list with 1 tweet id -> [5],
// since user 1 is no longer following user 2.
twitter.getNewsFeed(1);

{% endhighlight %}

***
<br />

这题的核心还是要设计出合适的数据结构来存储信息。从题目可以知道我们需要维护两种信息，一个是用户关系，一个是汇总了所有用户所发tweet的feed流。放在实际生产中前者估计就是一个SQL表了（考虑到缓存肯定会更加复杂，但是从调用者的角度来看应该是抽象成一个表），后者搭建feed流也有一些开源工具（这里不谈对这两者的优化，其一作为局外人确实不了解，其二也不是这篇文章的重点），这里也分开来存储，但是要简单的多。用户关系可以用一个二维bool矩阵来记录，feed流直接可以用一个vector来保存，其中需要在一个feed里同时保存发tweet者信息和tweetId，可以把二者绑定在一个`pair<int, int>`里。数据结构解决了四种方法的逻辑也都比较简单，post需要把userId和tweetId绑定起来push到feed流里；get从feed流尾部开始读取至多10条相关的tweets；follow和unfo只要把用户关系表里对应的位置置为true/false即可。

需要注意的点首先还是老生常谈的数组访问越界的问题。因为这里的用户不是一次性全部添加的，我们只能根据当前的实际情况来确定用户关系表中行的长度。比如新添加一个用户的时候，可以把对应的行至少扩展到userId位，当post的时候需要为不存在的用户新建其在关系表中的位置，get的时候要先判断关系表是否有[followerId][followeeId]这一位，等等。其次就是twitter产品自身的特点：一个用户必须follow且无法unfo自己。第一次提交就是遗漏了无法unfo自己这个问题而WA。

代码：

{% highlight c++ %}
class Twitter {
public:
    /** Initialize your data structure here. */
    Twitter() {
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        add_user(userId);
        fs.push_back(pair<int, int>(userId, tweetId));
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        int count = 0;
        vector<int> ret;
        for(int i = fs.size()-1; i >= 0 && count < 10; --i)
            if(is_follow.size() > userId && is_follow[userId].size() > fs[i].first && is_follow[userId][fs[i].first]){
                ret.push_back(fs[i].second);
                ++count;
            }
        return ret;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        add_user(followerId);
        add_user(followeeId);
        if(is_follow[followerId].size() < followeeId+1) is_follow[followerId].resize(followeeId+1, false);
        is_follow[followerId][followeeId] = true;
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(followerId == followeeId) return;
        if(is_follow.size() > followerId && is_follow[followerId].size() > followeeId)
            is_follow[followerId][followeeId] = false;
    }
private:
    vector<vector<bool> > is_follow;
    vector<pair<int, int> > fs;
    void add_user(int userId){
        if(is_follow.size() < userId+1) is_follow.resize(userId+1, vector<bool>());
        if(is_follow[userId].size() < userId+1) is_follow[userId].resize(userId+1, false);
        is_follow[userId][userId] = true;
    }
};
{% endhighlight %}

P.S. 我觉得这题的注释还是有点问题，follow和unfo函数前提到的no-op容易让人产生误解，当一个用户follow一个之前没有提过的用户时，是否是invalid的行为呢？我觉得应该是invalid，毕竟不能因为我胡乱去follow一个用户系统就为我创建一个对应的用户，那还不乱套了。Anyway，就题论题这点搞清楚了就好，实际生产应该不会出现这种问题，毕竟用户都是搜索或者通过其他途径看到的已存在的账户，但想得更多一些总没有坏处。;)
