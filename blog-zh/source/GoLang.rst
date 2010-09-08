..  coding: utf-8
.. 1 tab = 4 spaces

.. 文件名: GoLang.rst
.. 作者: Tower Joo<zhutao.iscas@gmail.com>
.. 日期: 2009-12-07 14:25:53
.. 说明: 

=============================
GoLang
=============================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)




摘要
========================================

.. contents::


引入
=========

因为最近一个 `朋友`_ 聊天时, 聊起了一些新的技术, 便扯起了Google推出的 `GoLang`_,
在他痴迷的感召下和阅读完 `Go@Googlecode`_ 下面这个有趣帖子:

`I have already used the name for *MY* programming language`_ (居然有个印度人已经之前公开命名和使用过GO作为语言名称了)

于是,想看看 `GoLang`_ 究竟有哪些不同的地方. 

你可能会说是否这样太 "不务正业" 了, 我不多做解释和认证,我来搬出经典,
不知道你是否有阅读过 `The Pragmatic Programmer`_ ,里面提到了下面几个投资知识的观点,
可以作为参考(括号中是我的一点注解):

::

    Learn at least one new language every year.(每年新学一种语言)
    Read a technical book each quarter.(每季度读一本技术书, 我觉得可能要求还是低些)
    Read nontechnical books, too. (也要读非技术类的书籍, 因为我们的用户通常是非技术类的人,和他们有共同语言很重要)
    Take classes. (去参加一些讲座或者培训)
    Participate in local user groups.  (参加一些邮件列表的线下活动)
    Experiment with different enviroments. (去尝试新的环境,如你习惯了win,不防试试linux)
    Stay current.(订阅业内的一些最新资讯, 如可以看看csdn的首页等, 不过csdn的内容已经不敢恭维了)
    Get wired. (读一些邮件列表中别人发现的奇怪的事情)

让我们不妨在09年的年末来开始学习一门新的语言吧.

第一次的亲密接触
=================

(如果你是80后,想必有读过这个标题的书吧, 还记得美丽的轻舞飞扬? 倘若没有读过,100多页会让你在轻松中享受文字的优美的. 
`第一次的亲密接触`_)

我向来认为 **后出现的语言比先出现的语言,在语言层面会有一定的优势, 至少同一类型的语言**, 这里的同一类型语言是指
**强类型** 和 **弱类型** 语言.

如果用一句话来概括, Robert Griesemer, Rob Pike and Ken Thompson为什么要设计和实现这个语言, 那就是:

**要兼有静态类型,编译型语言的安全和动态类型,解释型语言的简单**.

要了解如何在linux下安装,可以参考这里: `GoLang How to install Go (GoLang) compiler on Ubuntu`_

一个简单的hello world如下:

.. sourcecode:: go

    package main

    import "fmt"

    func main()
    {
            fmt.Printf("Hello world!\n");
    }


个人体验总结
===============

写一个快速排序为例
======================

相关的参考
==============





结论
===============

后记
==============

参考资料
========================================

#. `Go@Googlecode`_
#. `GoLang How to install Go (GoLang) compiler on Ubuntu`_
#. 


本文的源码
========================================

本文的rst源码链接在 `这里`_ .

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)


.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里: 
.. _下载pdf阅读: 
.. _朋友: http://blog.lvscar.info/
.. _Go@Googlecode: http://code.google.com/p/go/
.. _I have already used the name for *MY* programming language: 
.. _The Pragmatic Programmer: http://www.douban.com/subject/1152111/

.. _第一次的亲密接触: http://www.douban.com/subject/1024217/
.. _GoLang How to install Go (GoLang) compiler on Ubuntu: http://google-go-lang.blogspot.com/2009/11/how-to-install-go-golang-compiler-on.html
