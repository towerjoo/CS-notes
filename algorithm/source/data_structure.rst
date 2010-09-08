.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-18 14:58

========================================
常用的数据结构总结
========================================


文档概要
========================================

本文档主要对计算机中常用的数据结构进行相关的总结,并
根据下面的框架进行,即:

* 定义
* 实现
* 注意问题


.. index::
   container

    
container 容器
========================================

定义
----------------------------------------

A **container** is a class, a data structure, or an abstract data type(ADT), whose instances are collections
of other objects. They are used to store objects in an organized way following specific access rules.

通常包括两类:

* 基于值(存储的是对象的拷贝,访问时返回的是拷贝)
* 基于引用(存储的是引用或者指针,访问时返回的是引用, 更改时有副作用)

具体参见 :ref:`container容器 <container_detail>`

常用的操作
------------

* 创建
* 大小
* 清空
* 插入新的元素
* 删除元素
* 访问容器对象


注意问题
----------------------------------------

#. 基于值的容器,对于访问时的数据进行更改 **不会** 影响容器的内容
#. 基于引用的容器,对于访问时的数据进行更改 **会** 影响容器中的内容




Tree 树
==========

参考: :ref:`tree`

参考资料
========================================

#. `Container <http://en.wikipedia.org/wiki/Container_(data_structure)>`_
#. `Double-Ended Queue <http://en.wikipedia.org/wiki/Deque>`_
#. `List <http://en.wikipedia.org/wiki/List_(computing)>`_
#. `Map <http://en.wikipedia.org/wiki/Associative_array>`_
#. `Multimap <http://en.wikipedia.org/wiki/Multimap>`_
#. `Multiset <http://en.wikipedia.org/wiki/Set_(computer_science)#Multiset>`_
#. `Priority_queue <http://en.wikipedia.org/wiki/Priority_queue>`_
#. `Priority <http://en.wikipedia.org/wiki/Queue_(data_structure)>`_
#. `Set <http://en.wikipedia.org/wiki/Set_(computer_science)>`_
#. `Stack <http://en.wikipedia.org/wiki/Stack_(data_structure)>`_
#. `String <http://en.wikipedia.org/wiki/String_(computer_science)>`_
#. `Tree <http://en.wikipedia.org/wiki/Tree_(computer_science)>`_





