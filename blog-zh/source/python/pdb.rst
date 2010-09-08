.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-07-18 23:22

========================================
使用PDB调试python程序
========================================


摘要
========================================

使用过C语言的程序员肯定对 `GDB`_ 不陌生, 它的单步调试等功能对于常常需要debug
的程序员而言是非常重要的, 而作为动态语言的 `python`_ , 它的动态性给单步调试
带来了一定的难度, 但是 `python`_ 的标准模块 `PDB`_ 则依照 `GDB`_ 的思路较好地解决了
这个问题.本文就简单地介绍如何使用 `PDB`_ 进行单步调试.

.. contents::






什么是PDB
========================================

根据 `PDB`_ 在 `python`_ 文档中的定义, 它是一种为 `python`_ 程序提供一种
交互的源码调试功能的模块.主要的特点(feature)包括:

* 条件断点
* 源码行级的单步调试
* 查看栈片断
* 在任意的栈片断的环境下对任意的代码进行求值(类似于 `GDB`_ )
* 代码列出　　
* 其它

使用PDB进行简单的调试
========================================

`python`_ 程序也可以实现类似于c/c++的单步调试功能，而 `python`_ 中的调试模块 `PDB`_ 类似于c中的 `GDB`_ （常用命令等），可以进行方便的调试。

下面是一个例子(debug_demo.py)：

::

    #!/usr/bin/env python
    _debug = True

    def debug_demo(val):
        if _debug:
            import pdb
            pdb.set_trace()           #引入相关的pdb模块
        if val < 10:
            print "less than 10"
        elif val<20:
            print "less than 20, but big than 10"
        else:
            print "other condition"

在命令行中按如下方法进行调试：

`python debug_demo.py`

这时会进入类似于gdb的界面，启动相关的调试

::

    > /home/tower/test/python/debug.py(9)debug_demo()
    -> if val <= 10:
    (Pdb)

可以输入h来查看可用的命令集（很类似于gdb）。
单步调试对于某些情况下的调试是非常有帮助的


结论
========================================

单步调试对于程序关键部分的逻辑跟踪是很有意义的,所以 `PDB`_ 之于 `python`_ 类似于 `GDB`_ 之于C/C++.
但是相比于 `GDB`_ 而言, `PDB`_ 的功能还稍显弱了许多, 所以还无法在 `PDB`_ 里使用到 `GDB`_ 的所有feature.
可以预期的是随着 `python`_ 转至3.0及至后面的版本升级, `PDB`_ 也会愈发完善.值得期待.

后记
========================================

博客园似乎是一个以MS的.net的技术为主的技术博客群, 不知道有多少人对 `python`_ 有兴趣, 不过 `IronPython`_ 做为
二者的结合已经是得到了很大的应用. 期待和你们交流.

参考资料
========================================

#. `python`_
#. `IronPython`_
#. `GDB`_
#. `PDB`_
#. `使用pdb调试Python程序 <http://blog.chinaunix.net/u2/63996/showart_1817104.html>`_


.. _IronPython: http://www.codeplex.com/IronPython
.. _python: http://www.python.org
.. _PDB: http://docs.python.org/library/pdb.html
.. _GDB: http://www.gnu.org/software/gdb/
