.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-09 15:15

========================================
iterator模式
========================================

.. index:: 
	iterator

.. _iterator: 
	

iterator模式定义
========================================

**The Iterator Pattern** provides a way to access the elements of an aggregate object sequentially 
without exposing its underlying representation.

**迭代器模式** 提供了一种对一种聚合体无需暴露其内部表示而又能顺序存取其元素的方法.



问题描述
========================================

有两种不同的菜单,菜单的条目是相同的类型,但是每个菜单的条目所用的表示方式不同,一个为数组,一个为vector,
这时为了更好地提供统一的接口,我们可以使用 **Iterator模式** 来完成.

类图如下:

.. image:: ../../image/iterator_exp.png

**迭代器模式** 类图如下:

.. image:: ../../image/iterator_class.JPG


具体代码
========================================

下载请点击 :download:`这里 <../../code/iterator.cpp>`

.. literalinclude:: ../../code/iterator.cpp
	:language: c++
	:linenos:


输出结果为:

::

    Potato
    Noodle
    ####### Waitress start ###############
    Name: Potato   Price:13.5
    Name: tomato   Price:33.5
    Name: pancake   Price:3.5
    Name: Noodle   Price:45.5
    Name: Rice   Price:32.4

面对新的需要
========================================

如果有新内部实现不同的集合,则只需:

* 继承 **Iterator** 类
* 实现相应的接口即可



更多注意
========================================

设计准则:

**A class should have only one reason to change.**

也就是说一个类只能有一个 **责任**.这也是提高 **内聚** 的一种方法.


参考更多
========================================

#. `Iterator_Pattern <http://en.wikipedia.org/wiki/Iterator_pattern>`_


