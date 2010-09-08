.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-07 15:44

========================================
singleton模式
========================================

.. index:: 
	singleton

.. _singleton:

singleton模式定义
========================================

**Singleton** - Ensure a class only has one instance and provide
a global point to access it.

**单例模式** - 保证一个类只有一个实例,并且提供一个全局的访问方法.


问题描述
========================================

在实际中可能某些环境下,只需要 **唯一** 的一个类的实例存在,例如
**线程池**, **缓存**, **对话框**, **处理用户偏好,注册设置的对象**,
**用于日志的对象** 等等.此时就需要使用 **单例模式**

单例模式的类图如下:

.. image:: ../../image/singleton_class.png


具体代码
========================================

下载请点击 :download:`这里 <../../code/singleton.cpp>`

.. literalinclude:: ../../code/singleton.cpp
	:language: c++
	:linenos:


输出结果为:

::

    NUM:10
    NUM:10
    0x8928008
    0x8928008


面对新的需要
========================================
只需按需要添加相关的类即可.



更多注意
========================================
单例模式本身是很容易理解,但具体实现起来则比较难,需要
注意的点包括:

* 线程安全
* 多个 *class loaders* (例如, java)
* 因为引入了 *static* 变量,所以会使程序不是 *Reentrant* 
* 这是个存在争议的模式(维持了一个全局的状态,使用 *static* 等) ,但是在实际中有大量的使用
* **Easy understand but hard to impletment**

.. note::

    注意线程安全的问题:

    在实现 **线程安全** 的单例模式时,可以参考 **参考更多部分** 

    


参考更多
========================================

#. `Reentrant <http://en.wikipedia.org/wiki/Reentrant_(subroutine)>`_
#. `Thread_safety <http://en.wikipedia.org/wiki/Thread_safety`>`_
#. `Singleton_Pattern <http://en.wikipedia.org/wiki/Singleton_pattern>`_
#. `C++完美实现Singleton模式 <http://www.cppblog.com/dyj057/archive/2005/09/20/346.aspx>`_
#. `Double-checked locking <http://en.wikipedia.org/wiki/Double_checked_locking_pattern>`_



