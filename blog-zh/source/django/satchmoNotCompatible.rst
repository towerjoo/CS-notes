.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-09-18 22:32

========================================
satchmo并非严格向后兼容的,请大家小心
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .


摘要
========================================

今天在为新同事搭建运行环境时,发现了这个问题,satchmo存在较大的向后兼容问题,
为了解决那个问题,花了3个多小时的跟踪,最终找到的原因和解决方案.


.. contents::





问题来由
========================================

2个月前开始使用 `satchmo`_ 和 `django`_ 来完成当前的项目,当时使用的 `satchmo`_ 版本是0.9 pre,
我们是用 `hg`_ 检出的最新代码,然后一切正常.

直至,我们开始有了新的同事,如果是 `python`_ 开发人员还好,他们会很快地配置好开发环境(其实是比较
简单的,只是有很多的依赖程序),但是如果是html开发人员则会困难很多,他们通常没有 `python`_ 的背景,
所以,很难在短时间内搭建起我们的开发环境.

于是,我便试图协助他们一起搭建开发环境.一切正常,直至今天出现的问题.

我依旧按照旧有的步骤进行,不过出现下面怪异的现象:

当你同步完数据库后,此时系统会很好地运行,你能够访问admin和settings,但是在你配置完成后(我们需要
配置相关的支付模块), `django`_ 会报下面的错.

::

    Template error

    In template d:\freshfanatic\templates\default_header_footer.html, error at line 100
    Caught an exception while rendering: Could not import payments.modules.authorizenet_custom.views. 
    Error was: No module named signals

当然上面是我的出错信息,你的可能会有所不同.但是核心的是, signals这个模块出错了, `django`_ 找不到
相应的模块.

更费解的是, 我们之前同事的代码都是正常的,而最新的代码总是出问题.


解决之道
================

于是开始着手解决, 其实我一直是有个假设 **就是satchmo本身是向后兼容的** ,但是回过头来看
这个假设是错误的.

我大致介绍下我追踪问题的方法.

#. 隔离出错代码:提示是authorizenet_custom.views代码出错,于是我把所有payments的模块和app全部隔离(注释掉)
   结果是: **同样的错误**
#. 从 `satchmo`_ 本身开始入手,从相关的资源寻求答案(官网,邮件列表,源码管理网站等)
   结果是: **没有充足的信息让我定位错误**
#. 重新开始分析:既然是 **相同的代码** 而出现不同的结果,只可能是环境配置的问题.于是想到了 `satchmo`_ 本身
   的向后兼容问题.
   结果: **果然,在某个版本后satchmo加入了新的feature signal,与我们之前的代码不兼容**

于是方案便出来了,我们决定不使用版本库中最新的 `satchmo`_ 代码,而是使用我们之前的代码.经过简单的配置,
果然如期地工作了.

整个过程花费了3个多小时, 几次失败后, 终于算是成功了. 而且对于自己的处理流程,现在想起也是有些质疑(具体
可见下文的结论部分). 


结论
========================================

于是,我便有了如下的结论:

#. 开源的产品的版本的一致性,兼容性方面并不是十分的严格,可以参见 `django`_, `satchmo`_ 的那些不兼容的说明
#. 在依赖产品的v1.0版本前,一定要基于同一个版本,而非最新的版本(实际上作为production的级别,要尽量使用稳定版,而非最新版)
#. 追踪问题的方式,从可能性的逆序进行,当然如何判断可能性,这才是真正能力和经验的体现

`satchmo`_ 本身是一个十分优秀的基于 `django`_ 开源在线商店的框架, 如果某个朋友有相关的需求可以去
参考这个框架, **值得一试**. 


本文的rst源码
========================================

本文的源码链接在 `这里`_ .






.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _django: http://www.djangoproject.com
.. _satchmo: http://www.satchmoproject.com
.. _python: http://www.python.org
.. _hg: http://www.selenic.com/mercurial/
.. _这里: http://sites.google.com/site/towerjoo/download/satchmoNotCompatible.rst?attredirects=0
