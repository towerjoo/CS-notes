.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-05 11:39

========================================
decorator模式
========================================

.. index:: 
   decorator

.. _decorator:

decorator模式定义
========================================
Decorator: Attach additional responsibilities to an object dynamically.
Decorators provide a flexible alternative to subclassing for
extending functionality.

Decorators: 向一个对象 **动态** 地绑定额外的 **功能（责任）**. 
Decorators 向为了实现扩展功能而提供一种除继承外更加 **灵活** 的方法。


问题描述
========================================

一家咖啡店随着规模扩大，除了提供常见的咖啡外，还向顾客提供诸如加 *mocha*, *whip*, *soy* 等
辅料，所以现在需要解决

* 如果增加辅料的类型如何处理
* 如果增加咖啡的类型如何处理等

最开始的设计如下(完全使用继承）：

.. image:: ../../image/all_inheritance.png

更好的办法是使用 **Decorators** 模式，那么会很好地满足需求。

使用 **Decorators** 后的类图如下：

.. image:: ../../image/decorator.png

现实中的例子包括，java中的IO，
如下图所示：

.. image:: ../../image/javaio.png


具体代码
========================================

下载请点击 :download:`这里 <../../code/decorator.cpp>`

.. literalinclude:: ../../code/decorator.cpp
	:language: c++
	:linenos:


输出结果为:

::

    medium  DarkRoast, Mocha, Whip, Soy, Whip  costs:3.08



面对新的需要
========================================

当需要增加新的辅料时，只需要：

* 继承 **CondimentDecorator** 类，
* 实现其中的相关操作


更多注意
========================================

* **Decorators** 会导致出现很多一些小类（装饰类），导致类特别多。
* 如果要在具体的 *Component* 类中有相关的行为，则可能不适用（如在DarkRoast中有打折相关的行为）
* **DarkRoast** 模式通常会和 **Factory** 或者 **Builder** 模式一起使用

新的设计原则：

**Classed should be open for extension but closed for modification.**


参考更多
========================================

* `Decorator_Pattern <http://en.wikipedia.org/wiki/Decorator_pattern>`_



