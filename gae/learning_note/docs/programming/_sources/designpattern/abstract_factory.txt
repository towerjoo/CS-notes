.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-05 16:10

.. _abstract_factory:

========================================
abstract factory模式
========================================

.. index:: 
   abstract factory

abstract factory模式定义
========================================

**Abstract Factory** provide an interface for creating families of related or dependent
objects without specifying their concrete classes.

**抽象工厂** 提供了用来创建 **一族** 相关或者依赖的对象而无需指明它们的具体类的接口。


问题描述
========================================

在 :ref:`factory_method` 的例子中， 增加了如下的需求：

* 保证不同的地址的分厂生产的产品质量有保证，使用特定的原料
* 不同的地址可能原料不尽相同，但是需要指定

**抽象工厂** 的思路如下：

.. image:: ../../image/abstract_class.png

具体使用 **抽象工厂** 解决的类图如下：

.. image:: ../../image/abstract_factory_class.png


具体代码
========================================

下载请点击 :download:`这里 <../../code/abstract_factory.cpp>`

.. literalinclude:: ../../code/abstract_factory.cpp
	:language: c++
	:linenos:


输出结果为:

::




面对新的需要
========================================

需要增加新地点时，如california，可以按照如下进行：

* 继承 *Pizza* 类生成特定于california的Pizza类
* 继承 *PizzaStore* 类生成特定于california的工厂类



更多注意
========================================

需要注意的是：

* *Abstract Factory* 是基于类 **组合** 的（注意与 :ref:`factory_method` 的区别）
* *Abstract Factory* 模式实例化一类 **同族** 的相关或者依赖对象而无需依赖具体的类



参考更多
========================================

* `Abstract_Factory_Pattern <http://en.wikipedia.org/wiki/Abstract_factory_pattern>`_


