.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-08 21:45

========================================
adapter模式
========================================

.. index:: 
	adapter

.. _adapter:

adapter模式定义
========================================

**Adapter Pattern** converts the interface of a class into another interface the clients expect.
Adapter lets classes work together that couldn't otherwise because of incompatible interfaces.

**适配器模式** 将一个类的接口转换为 **客户期待** 的另一个接口.
适配器使得本来由于接口不匹配而不能工作在一起的类可以工作在一起.



问题描述
========================================

鸭子和火鸡两个不同接口的类, 由于用户只知道鸭子类,所以当用户需要使用相同的接口来调用火鸡类时,
需要 **适配器模式** 来进行处理.

适配器模式的类图如下:

.. image:: ../../image/adapter_class.png

其中基于对象的 **适配器模式** 采用 **组合** 的方式,
而基于类的 **适配器模式** 采用 **继承** 的方式(多重继承).




具体代码
========================================

下载请点击 :download:`这里 <../../code/adapter.cpp>`

.. literalinclude:: ../../code/adapter.cpp
	:language: c++
	:linenos:


输出结果为:

::

    ############# The real duck start #####################
    Quack
    I'm flying
    ############# The real turkey start #####################
    Gobble gobble
    I'm flying a short distance.
    ############# The fake duck(turkey) start based on composition #####################
    Gobble gobble
    I'm flying a short distance.
    I'm flying a short distance.
    I'm flying a short distance.
    I'm flying a short distance.
    I'm flying a short distance.
    ############# The fake duck(turkey) start based on inheritance #####################
    Gobble gobble
    I'm flying a short distance.
    I'm flying a short distance.
    I'm flying a short distance.
    I'm flying a short distance.
    I'm flying a short distance.


面对新的需要
========================================

对于新的需要,如鸡要适配鸭的接口,只需:

* 使用 **基于组合** 或者 **基于继承** 的方式来实现鸭适配器的接口
* 实现鸭相应的函数

更多注意
========================================

:ref:`Decorator模式 <decorator>` 与 :ref:`Adapter模式 <adapter>` 及 :ref:`Facade模式 <facade>` 区别:

* Decorator模式 **不改变接口,但是增加了责任(功能)**
* Adapter模式 **将一个接口转换为另一个**
* Facade模式 **使得一个接口更加简单**



参考更多
========================================

#. `Adapter_Pattern <http://en.wikipedia.org/wiki/Adapter_pattern>`_


