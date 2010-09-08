.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-11 19:29

========================================
proxy模式
========================================

.. index:: 
	proxy

.. _proxy: 
	

proxy模式定义
========================================

**The Proxy pattern** provides a surrogate or placeholder for 
another object to control access to it.

**代理模式** 为另一个对象提供了一个代理或者占位来控制对这个对象的访问.

使用代理模式来创建一个用于表示的对象来控制另一个对象的访问,
这个被控制的对象可能是 **远程的**, **创建起来成本很高**, **或者有安全需求**. 

问题描述
========================================

图片从本地硬盘(或者远程机器)读取并且显示.

为了 **控制访问** (控制对本地硬盘的访问),我们可以使用 **代理模式**,
当所请求的图片还未载入时,我们创建新的真正图片的实例,并且载入,
如果已经载入,则直接显示即可.

具体的实现类图如下:

.. image:: ../../image/image_class.jpg


**代理模式** 的类图:

.. image:: ../../image/proxy_class.png


具体代码
========================================

下载请点击 :download:`这里 <../../code/proxy.cpp>`

.. literalinclude:: ../../code/proxy.cpp
	:language: c++
	:linenos:


输出结果为:

::

    Loading image1
    Displaying Image image1
    Loading image2
    Displaying Image image2
    Displaying Image image1



面对新的需要
========================================



更多注意
========================================

通常有多种 **代理模式** 的变种,常用的包括:

* Remote Proxy : 作为远程的代理
* Virtual Proxy: 对一些expensive resource的访问访问控制
* Protection Proxy: 根据权限提供特定的服务(方法)


:ref:`Decorator Pattern<decorator>`, :ref:`Facade Pattern<facade>`, :ref:`Proxy Pattern<proxy>`, :ref:`Adapter Pattern<adapter>`
的比较:

* **Decorator** - Wraps another object and provides additional behavior for it
* **Facade** - Wraps a bunch of objects to simplify their interface
* **Proxy** - Wraps another object to control access to it
* **Adapter** - Wraps another object and provides a different interface to it

**proxy pattern** 同样也会增加类的数目.

参考更多
========================================

#. `Proxy_Pattern <http://en.wikipedia.org/wiki/Proxy_pattern>`_


