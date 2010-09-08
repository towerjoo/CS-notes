.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-10-15 10:43

========================================
线程安全及Python中的GIL
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

抱歉,在正文中加入很多本博客的链接,主要是发现很多转载的朋友并未按照本声明来加入出处信息. 影响阅读,实在抱歉.


摘要
========================================

`作者博客链接`_.


什么是线程安全? 为什么python会使用GIL的机制?

在多核时代的到来的背景下,基于多线程来充分利用硬件的编程方法也不断发展起来, 但是一旦
牵扯到多线程,就必然会涉及到一个概念,即 **线程安全**, 本文就主要谈下笔者对线程安全的一些理解.

而Python为很多人所抱怨的一点就是GIL,那么python为什么选择使用GIL, 本文也就这个问题进行一些讨论.


.. contents::



引入
========================================

`作者博客链接`_.


你的PC或者笔记本还是单核吗? 如果是,那你已经out了.

随着纳米技术的不断进步, 计算机芯片的工艺也在进步,但是已经很难在工艺上的改进来提高
运算速度而满足 `摩尔定理`_, 所以intel, amd相继在采用横向的扩展即增加更多的CPU,
从而双核, 4核, N核不断推出,于是我们进入了多核时代.

于是一个问题出现了, 多核时代的出现对于我们程序员而言意味着什么, 我们如何利用多核的优势?

在回答这个问题之前,建议对 `进程`_ 和 `线程`_ 不熟悉的读者可以先补下相关的知识.

当然方案是,可以采用 **多进程**, 也可以采用 **多线程**. 二者的最大区别就是, 是否共享资源,
后者是共享资源的,而前者是独立的. 所以你也可能想起了google chrome为什么又开始使用独立的进程
来作为每个tab服务了(不共享数据,意味着有更好的安全性).

相对于进程的轻型特征,多线程环境有个最大的问题就是 **如何保证资源竞争,死锁, 数据修改等**.

于是,便有了 `线程安全`_ (thread safety)的提出.


线程安全
========================================

`作者博客链接`_.


::

    Thread safety is a computer programming concept applicable in the context of multi-threaded programs. 
    A piece of code is thread-safe if it functions correctly during simultaneous execution by multiple threads. 
    In particular, it must satisfy the need for multiple threads to access the same shared data,
    and the need for a shared piece of data to be accessed by only one thread at any given time.

上面是wikipedia中的解释, 换句话说, `线程安全`_ 是在多线程的环境下, 线程安全能够保证多个线程同时执行时程序依旧运行正确,
而且要保证对于共享的数据,可以由多个线程存取,但是同一时刻只能有一个线程进行存取.

既然,多线程环境下必须存在资源的竞争,那么如何才能保证同一时刻只有一个线程对共享资源进行存取?

**加锁**, 对, 加锁可以保证存取操作的唯一性, 从而保证同一时刻只有一个线程对共享数据存取.

通常加锁也有2种不同的粒度的锁:

#. fine-grained(所谓的细粒度), 那么程序员需要自行地加,解锁来保证线程安全
#. coarse-grained(所谓的粗粒度), 那么语言层面本身维护着一个全局的锁机制,用来保证线程安全

前一种方式比较典型的是 `java`_, `Jython`_ 等, 后一种方式比较典型的是 `CPython`_ (即Python).

前一种本文不进行讨论, 具体可参考 `java`_ 中的多线程编程部分.

至于Python中的全局锁机制,也即 `GIL`_ (Global Interpreter Lock), 下面主要进行一些讨论.

GIL
========================================


`作者博客链接`_.


什么是 `GIL`_ ? 答案可参考wikipedia中的说明, 简单地说就是:

**每一个interpreter进程,只能同时仅有一个线程来执行, 获得相关的锁, 存取相关的资源**.

那么很容易就会发现,如果一个interpreter进程只能有一个线程来执行, 多线程的并发则成为不可能, 
即使这几个线程之间不存在资源的竞争. 

从理论上讲,我们要尽可能地使程序更加并行, 能够充分利用多核的功能, 那么Python为什么要使用
全局的 `GIL`_ 来限制这种并行呢?

这个问题,其实已经得到了很多的讨论, 不止十年, 可以参考下面的文档:

反对 `GIL`_ 的声音:

#. `An open letter to Guido van Rossum`_ (这个文章值得一看,下面有很多的留言也值得一看)

认为 `GIL`_ 不能去除的:

#. `It isn't Easy to Remove the GIL`_ (这个文章来自python作者 `Guido`_, 他说明了什么要使用 `GIL`_)

其它的一些讨论很容易从Google来搜索得到, 譬如: `GIL at google <http://www.google.com/search?hl=en&newwindow=1&q=global+interpreter+lock&aq=0&oq=Global+interpreter&aqi=g3g-m6>`_.

那么,简单总结下双方的观点.

认为应该去除 `GIL`_ 的:

#. 不顺应计算机的发展潮流(多核时代已经到来, 而 `GIL`_ 会很影响多核的使用)
#. 大幅度提升多线程程序的速度

认为不应该去除 `GIL`_ 的(如果去掉,会):

#. 写python的扩展(module)时会遇到锁的问题,程序员需要繁琐地加解锁来保证线程安全
#. 会较大幅度地减低单线程程序的速度

后者是 `Guido`_ 最为关切的, 也是不去除 `GIL`_ 最重要的原因, 一个简单的尝试是在1999年(十年前),
最终的结果是导致单线程的程序速度下降了几乎2倍.


归根结底,其实就是多进程与多线程的选择问题, 有一段话比较有意思, 
可以参考 `http://www.artima.com/forums/flat.jsp?forum=106&thread=214235 <http://www.artima.com/forums/flat.jsp?forum=106&thread=214235>`_.

我引用如下:


::

    I actually don't think removing the GIL is a good solution. 
    But I don't think threads are a good solution, either. 
    They're too hard to get right, and I say that after spending literally years studying threading in both C++ and Java. 
    Brian Goetz has taken to saying that no one can get threading right.

引自 `Bruce Eckel`_ 对 `Guido`_ 的回复. 而 `Bruce Eckel`_ 是何许人, 如果你了解 `java`_ 或者 C++, 那么应该不会不知道他.

个人的观点
========================================


`作者博客链接`_.


那么,从我自己的角度来看(我没有太多的多线程编程经验), 先不论多线程的速度优势等,我更加喜欢多进程的是:

#. 简单,无需要人为(或者语言级别)的加解锁. 想想 `java`_ 中的多线程编程,程序员通常会在此处出错(java程序员可以思考下)
#. 安全, 这也是浏览器为什么开始使用多进程的一个原因

依照Python自身的哲学, **简单** 是一个很重要的原则,所以, 使用 `GIL`_ 也是很好理解的.

当然你真的需要充分利用多核的速度优势,此时python可能并非你最佳的选择,请考虑别的语言吧,如 `java`_, `erlang`_ 等.

参考资料
========================================

#. `GIL 介绍`_
#. `An open letter to Guido van Rossum`_
#. `It isn't Easy to Remove the GIL`_
#. `线程安全`_


本文的rst源码
========================================

本文的源码链接在 `这里`_ .




.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里: http://www.google.com
.. _线程安全: http://en.wikipedia.org/wiki/Thread_safety
.. _GIL 介绍: http://www.dabeaz.com/python/GIL.pdf
.. _An open letter to Guido van Rossum: http://blog.snaplogic.org/?p=94
.. _It isn't Easy to Remove the GIL: http://www.artima.com/weblogs/viewpost.jsp?thread=214235
.. _GIL: http://en.wikipedia.org/wiki/Global_Interpreter_Lock
.. _java: http://en.wikipedia.org/wiki/Java_(programming_language)
.. _线程: http://en.wikipedia.org/wiki/Thread_(computing)
.. _进程: http://en.wikipedia.org/wiki/Process_(computing)
.. _摩尔定理: http://en.wikipedia.org/wiki/Moore_Law
.. _CPython: http://en.wikipedia.org/wiki/Cpython
.. _Jython: http://en.wikipedia.org/wiki/Jython
.. _Bruce Eckel: http://en.wikipedia.org/wiki/Bruce_Eckel
.. _Guido: http://en.wikipedia.org/wiki/Guido_van_Rossum
.. _erlang: http://en.wikipedia.org/wiki/Erlang_(programming_language)
.. _作者博客链接: http://www.cnblogs.com/mindsbook
