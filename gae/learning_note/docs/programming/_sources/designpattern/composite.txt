.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-09 18:56

========================================
composite模式
========================================

.. index:: 
	composite

.. _composite: 
	

composite模式定义
========================================

**The Composite Pattern** allows you to compose objects into tree structures to
represent part-whole hierarchies. Composite lets clients treat individual objects and
compositions of objects uniformly.

**组合模式** 使得可以将对象组合为 **树** 结构来表示 **部分-整体** 的层级关系.
组合使得用户能够 **统一** 地对待单一对象和多个对象的组合.


问题描述
========================================

与 :ref:`iterator` 中的场景类似,现在的菜单不只是单一的条目,还可能包含子菜单,即:

* 菜单中可能包含菜单
* 菜单中可能包含菜单条目

整个关系即是一种 **树形** 的结构.

可用下图来表示:

.. image:: ../../image/composite_exp.png

实现时使用的类图为:

.. image:: ../../image/composite_exp_class.png


**composite模式** 类图如下:

.. image:: ../../image/composite_class.png


具体代码
========================================

下载请点击 :download:`这里 <../../code/composite.cpp>`

.. literalinclude:: ../../code/composite.cpp
	:language: c++
	:linenos:


输出结果为:

::

    Name:  Menu1
    --------------------------
    Name:  leaf1  Price:23.2
    Name:  leaf2  Price:2.2
    Name:  Menu2
    --------------------------
    Name:  leaf1  Price:23.2
    Name:  leaf2  Price:2.2
    ######### Handle composite and leaf uniformly ########
    Name: Menu1
    Name: leaf1  Price:23.2




面对新的需要
========================================

实现Composite基类中的相应接口即可.


更多注意
========================================

**Composite模式** 通常与 :ref:`Iterator模式<iterator>` 一起使用.


参考更多
========================================

#. `Composite_Pattern <http://en.wikipedia.org/wiki/Composite_pattern>`_


