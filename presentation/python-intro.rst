.. include:: <s5defs.txt>

==============================
Python语言及其一些应用
==============================

:Author: 朱涛
:Date:   2009-09-25


.. contents::
   :class: handout

什么是Python
=============

.. class:: incremental

    `Python`_ 是一种 **通用** ( *general purpose*) 语言, 它已经在各种领域都有
    了很广泛的应用.譬如:

    * 大型的软件构建( `openerp`_, `Zope`_ 等)
    * Web框架 (`Django`_, `Web.py`_, 等)
    * 自然语言处理( `NLTK`_ )
    * 科学计算 (`NumPy`_)
    * 日常的脚本使用 (写写脚本, 分析日志等)
    * 等等
    
    `Python`_ 目前是 *Google* 的第二大开发语言.

什么是Python(续)
=================

`Python`_ 是 *Guido van Rossum* 于1991的发明的.

主要借鉴的语言包括:

* ABC
* Lisp
* Java
* C
* Perl
* Haskell


什么是Python(续)
=================

Python语言的流行度排名.

.. image:: ranking.png


Python有什么特点
=======================

.. class:: incremental

    * 语法
        
        * 简洁
        * 优美
        * 可读
        * 强大(具有优秀语言的大量特征,如namespace, dynamic, functional)
        * 跨平台

Python有什么特点(续)
=======================

.. class:: incremental

    * 哲学
        
        * KISS
        * DIY
        * battery-included(所谓的自省)

Python有什么特点(续)
=======================

.. class:: incremental

    * 支持
      
        * 大量的第三方应用支持

Python有什么特点(续)
=======================

.. class:: incremental
   
    * 社区
        
        * 国内: `CPyUG`_
        * 国外: python mailing list


Python代码片断
==============

.. code-block:: python

    import os
    import shutil

    def rmsvn(path, target):
        """
        remove the .svn directories recursively

        >>> curdir = os.path.abspath(os.path.dirname(__file__))
        >>> path = os.path.join(curdir, "testfolder")
        >>> target = ".svn"
        >>> rmsvn(path, target)
        """

Python代码片断(续)
========================

.. code-block:: python

        filename = path.split(os.path.sep)[-1]
        if os.path.isdir(path):
            if filename == target:
                shutil.rmtree(path)
            else:
                for file in os.listdir(path):
                    rmsvn(os.path.join(path, file), target)



    if __name__ == "__main__":
        import doctest
        doctest.testmod()



Python的应用
==============

.. class:: incremental

    `Python`_ 在各种生产环境中有大量的应用,本次我简单地介绍如下的几种应用:

    * Web 开发 Django
    * 日常的使用 

关于Django
==============

`Django`_ 是一种高效, 简洁, 适合快速开发的web框架.

它有如下的特点:

#. MTV(Model, Template, View, 和MVC对应)
#. ORM(独立于特定数据库, 高层封装)
#. url dispatch(使用与此正则表达式来进行url映射)
#. 集成的应用(如admin, auth等)

Django的一个简单例子
=====================

日常的使用
================

如果你喜欢文本,你可以选择使用 `restructuredText`_ 来写文档,
或者Presentation.

如果你需要分析日志, `Python`_ 提供强大的系统module和正则表达式的支持,
让你很容易进行日志的分析和处理.

如果你需要自动化测试, `Python`_ 可以很方便地写出测试用倒来简化你的开发
进程.

等等.

一个例子即, 本演示即是用 `Python`_ 的 `restructuredText`_ 写成的.

Q&A
========

无论你做哪方面的应用, `Python`_ 都能够给你以足够的支持.

所以我特别向大家推荐!

问题??


Links
=====

* `Python`_
* `Django`_
* `restructuredText`_
* `CPyUG`_
* `openerp`_
* `Zope`_
* `Web.py`_
* `NumPy`_
* `NLTK`_



.. _Python: http://www.python.org
.. _restructuredText: http://docutils.sourceforge.net/rst.html
.. _Django: http://djangoproject.com
.. _CPyUG: http://groups-beta.google.com/group/python-cn
.. _openerp: http://www.openerp.com/
.. _Zope: http://www.zope.org/
.. _Web.py: http://webpy.org/
.. _NLTK: http://www.nltk.org/
.. _NumPy: http://numpy.scipy.org/
