.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-09 11:31

========================================
template模式
========================================

.. index:: 
	template

.. _template:

template模式定义
========================================

**The Template Method pattern** defines the skeleton of an algorithm in a method,
deferring some steps to subclasses. **Template Method** lets subclasses redefine
certain steps of an algorithm without changing the algorithm's structure.

**模板方法模式** 在一个方法中定义了一个算法的框架(骨架), 把一些步骤推给子类.
**模板方法** 使得子类能够重新定义算法中的某些步骤而无须更改算法结构.



问题描述
========================================

对于一个兼营咖啡和茶的店,两种饮品的烹饪方式是相同的:

* 煮水
* 将饮品放入水中
* 倒入杯中
* 加入辅料

可以使用 **模板模式** 来完成.

具体的实现类图如下:

.. image:: ../../image/template_beverage.png

Template模式的类图如下:

.. image:: ../../image/template_class.png



具体代码
========================================

下载请点击 :download:`这里 <../../code/template.cpp>`

.. literalinclude:: ../../code/template.cpp
	:language: c++
	:linenos:


输出结果为:

::

    ##### Preparing the Coffee ######
    Boiling water.
    Dripping Coffee through filter.
    Pouring into cup.
    Whether you wanna add sugar and milk?(y/n)
    y
    Adding sugar and Milk
    ##### Preparing the Tea ######
    Boiling water.
    Dripping Tea through filter.
    Pouring into cup.
    Whether you wanna add lemon?(y/n)
    n




面对新的需要
========================================

如果需要更改算法具体的实现,则无须更改具体的算法类,只需要更改相应的实现即可.


更多注意
========================================

设计准则:

**The Hollywood Principle: Don't call us, We'll call you.**

:ref:`Template模式<template>` vs. :ref:`Strategy模式<strategy>` vs. :ref:`Factory模式<factory>`:

* **Template模式** 子类决定如何实现一个算法的步骤
* **Strategy模式** 封装了变化的行为并使用 **委托** 决定使用哪个行为
* **Factory模式** 子类决定哪个具体类实例化

在 **模板模式** 中注意 **hook** 的使用(hook是一些方法,它们在抽象类默认无功能或者有默认功能,但可以在子类中重载)

参考更多
========================================

#. `Template_Method_Pattern <http://en.wikipedia.org/wiki/Template_method_pattern>`_

