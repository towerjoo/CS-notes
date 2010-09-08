.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-17 22:51

========================================
设计模式总结
========================================

.. index:: 
	summary

一些定义
=======================

A **Pattern** is a *solution* to a *problem* in a *context*.

设计模式的分类
===============

主要分为三类: **Creational**, **Behavioral**, **Structural**

**Creational** 的模式是指:包含有对象的实例化又及提供一种方式来解耦合客户和所需实例化的对象.
包括有:

* :ref:`Singleton <singleton>`
* :ref:`Abstract Factory<abstract_factory>`
* :ref:`Factory <factory>`
* Builder
* Prototype

**Behavioral** 的模式是指: 主要关心类和对象之间的交互及如何分配责任.
包括有:

* :ref:`Template Method <template>`
* :ref:`Command <command>`
* :ref:`Iterator <iterator>`
* :ref:`Observer <observer>`
* :ref:`State <state>`
* :ref:`Strategy <strategy>`
* Mediator
* Vistor
* Memento
* Interpreter
* Chain of Responsibility

**Structural** 模式是指:使得组合类或者对象为了个更大的结构.
包括有:

* :ref:`Decorator <decorator>`
* :ref:`Composite <composite>`
* :ref:`Adapter <adapter>`
* :ref:`Facade <facade>`
* :ref:`Proxy <proxy>`
* Flyweight
* Bridge


一些设计上的原则
=================

要尽量使得设计简单,尽量不使用设计模式就不使用,除非真正需要.

* Keep It Simple and Stupid(KISS)
* Design Patterns are not a magic bullet; in fact they're not even a bullet
* Use a design pattern when you really need it
* Refactoring time is Patterns time!
* Take out what you don't realy need. Don't be afraid to remove a Design Pattern from your design
* If you don't need it now, don't do it now

设计模式简单小结
=================

* :ref:`Decorator <decorator>` : Wraps an object to provide new behavior
* :ref:`State <state>` : Encapsulates state-based behaviors and uses delegation to decide which one to use
* :ref:`Iterator <iterator>` : Provides a way to traverse a collection of objects without exposing its implementation
* :ref:`Facade <facade>`: Simplifies the interface of a set of classes
* :ref:`Strategy <strategy>` : Encapsulates interchaangable behaviors and uses delegation to decide which one to use
* :ref:`Proxy <proxy>` : Wraps an object to control access to it
* :ref:`Factory <factory>` : Subclasses decide which concrete classes to create
* :ref:`Adapter <adapter>`: Wraps an object and provides a different interface to it
* :ref:`Observer <observer>` : Allows  objects to be notified when state changes
* :ref:`Template Method <template>` : Subclasses decide how to implement steps in an algorithm
* :ref:`Composite <composite>` : Clients treat collections of objects and individual objects uniformly
* :ref:`Singleton <singleton>` : Ensures one and only object is created
* :ref:`Abstract Factory<abstract_factory>` : Allows a client to create families of objects without specifying their concrete classes
* :ref:`Command <command>` : Encapsulates a request as an object




参考更多
========================================

#. `The Porland Patterns Repository <http://c2.com/cgi/wiki?WelcomeVisitors>`_
#. `The Hillside Group <http://hillside.net>`_


