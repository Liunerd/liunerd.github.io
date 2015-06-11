---
layout: post
title: "FHS 3.0发布"
date: 2015-06-10
comments: true
categories: Photos
---

FHS 3.0发布了，准备趁机复习一下FHS的各种要求。这个标准本身没有太多可以深挖的东西，已经非常浅显易懂了。重点还是简单介绍一下这个标准，并且看一下3.0比起上一个版本2.3来有什么更新。

- ####FHS是什么####

刚开始用Linux的时候总是对Linux的文件层次结构很头疼，不知道像dev，etc，mnt这些文件夹下具体都是些什么内容，靠着字面去理解，比如dev就是device，media是媒体文件等等，纯走的是野路子。后来才发现了FHS这个东西，原来这些文件夹有严格的标准，马上就清楚了很多。如果作为初学或者打算深入使用Linux，我觉得FHS是一个非常好的切入点。

[FHS](http://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard)是Filesystem Hierarchy Standard的缩写，是规定Linux文件夹结构和文件夹内容的标准。这个标准几天前刚刚更新到了3.0。想仔细研究FHS的同学可以戳[这里](http://refspecs.linuxfoundation.org/fhs.shtml)获得2.3和3.0版本的文档，2.3版本也有[中文版](https://www.gitbook.com/book/wylmer_cn/filesystem-hierarchy-standard/details)可以查阅。

具体内容就不详细说了，有兴趣有时间的可以将FHS作为一项完整的材料看一遍，也可以作为字典用时再查阅。

野路子有时候也挺管用，但是遇到历史遗留问题就不好办了，比如说usr，看到它又抓瞎了，user是啥的缩写？user吗？为啥usr下面还有一套自己的结构？[这里](http://www.ruanyifeng.com/blog/2012/02/a_history_of_unix_directory_structure.html)有一篇很好的文章可以告诉你答案。

- ####FHS 3.0更新了什么####

根据FHS 3.0的[Release Note](https://wiki.linuxfoundation.org/en/FHSReleaseNotes30)，FHS 3.0主要更新了以下内容：

- 新增了一个/run文件夹；
- 更新了一些软件的参考来源；
- 字符集从ISO更新到了Unicode；
- 明确了一些文件夹的具体作用，比如/opt, /usr/local, 和 /srv. 

- ####/run文件夹####

FHS 3.0最重要的一个更新就是在根目录下新增了/run文件夹。这个文件夹的作用是存放运行时可变数据（run-time variable data），具体来说就是自系统上次启动以来描述系统信息数据。曾经这个文件夹放在/var/run，现在对其进行了“升级”，但是要求基本没变，和2.3版本的var/run相同，包括：

- /run里的内容在系统每次启动时都会清空。
- 和/var/run的策略一样，程序也可以在run下建立自己的文件夹，并且鼓励程序使用多个数据文件。
- PID文件需要放到/run下面。PID文件的内部格式也和上一版本一样。
- utemp文件必须放在/run文件夹下。
- 维护暂时UNIX域socket的程序也必须放在这个文件夹下。

另外，为了向下兼容，程序可以继续使用/var/run。

除此以外对FHS 3.0感兴趣的同学可以去下载文档来看看，50页左右，很快就能看完。像这种比较基础的协议，一般变动都不会很频繁（比如个版本2.3就要追溯到十多年前的2004年），同样要得到厂商的支持估计也要等一段时间，几大主要Linux发行版的下一个版本应该都会慢慢迁移到FHS 3.0上。


