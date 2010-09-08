======================
SCM和DSCM的对比学习
======================

.. note::

    SCM是指 *Source Code Management*, 本节主要介绍常用的SCM(以SVN为例)和DSCM(以Mercurial HG为例)的差别和各自的
    优势和劣势.而DSCM中的D是指 *Distributed* 即分布式的源代码管理.


SCM
========

从CVS到SVN都采用传统的C/S这样的架构,其原理如下:

.. .. image:: ../image/SCM.gif

那么,通常的交互如下:

#. 用户A checkout出一个副本
#. 用户A 在本地修改
#. 用户A 提交(commit)到repository

当用户有如下行为时就必须与server打交道:

* check in 
* check out
* log
* diff
* update(回滚到特定版本)
* 其它

所以在使用SVN过程会很依赖于网络,耗费大量的带宽.譬如看一个log可能会耗费较长时间(这个操作理应很快).

DSCM
=============

而DSCM是分布式的代码管理,即各个用户之间是对等的,亦即每个用户的working copy具有SVN中server的绝大部分功能.

那么常用的操作就可不与服务器打交道.

原理图如下:

.. .. image:: ../image/DSCM.gif


那么下面的操作可以不与服务器交互而在本地进行:

* log
* update(回滚)
* diff

而且,各个用户之间可以进行push,pull,方便代码的局部集成.
