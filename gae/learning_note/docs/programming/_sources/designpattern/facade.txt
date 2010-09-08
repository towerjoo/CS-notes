.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-08 22:22

========================================
facade模式
========================================

.. index:: 
	facade

.. _facade:

facade模式定义
========================================

**The Facade Pattern** provides a unified interface to a set of interfaces
in a subsystem. Facade defines a higher-level interface that makes the 
subsystem easier to use.

**Facade模式** 为一个子系统的一系列接口提供一个统一的接口. 
Facade定义了使得子系统更容易使用的高级接口.



问题描述
========================================

家庭影院系统包括:功放,投影仪,DVD播放器等,
那么每次欣赏电影时,可以使用各自类的方法来完成,如,先打开投影仪,然后DVD播放器,然后
投影仪,然后功放等,欣赏完成后以相反的顺序关闭.但是这样显然比较麻烦,此时可使用
**Facade模式** 提供简单的接口,即播放电影和关闭电影.


Facade模式的类图:

.. image:: ../../image/facade_class.png


具体代码
========================================

下载请点击 :download:`这里 <../../code/facade.cpp>`

.. literalinclude:: ../../code/facade.cpp
	:language: c++
	:linenos:


输出结果为:

::

    ################# Non-facade Pattern ####################
    DVD is on.
    Projector is on.
    Amplifier is on.
    DVD is playing.
    ################# Facade Pattern ####################
    DVD is on.
    Projector is on.
    Amplifier is on.
    DVD is playing.


面对新的需要
========================================

只需要进行相关的封装即可.


更多注意
========================================

Decorator模式, Adapter模式, Facade模式的区别参见 :ref:`adapter`

设计准则:

**Principle of Least Knowledge-talk only to your immediate friends.**

此准则也称为 **Law of Demeter**, **迪米特准则**

.. note::

    米特法则有一些很形象的比喻： 
    如果你想让你的狗狗跑的话，你会对狗狗说还是对四条狗腿说？ 
    如果你去店里买东西，你会把钱交给店员，还是会把钱包交给店员让他自己拿？ 


这个准则告诉我们, 我们只能调用下列情形下的方法:

* 对象自身
* 作为参数对象传递传递给方法
* 方法创建或者实例化的任何对象
* 任何对象的部件

一个遵循此准则的例子:

.. image:: ../../image/least_knowledge_exp.png


参考更多
========================================

#. `Facade_Pattern <http://en.wikipedia.org/wiki/Facade_pattern>`_


