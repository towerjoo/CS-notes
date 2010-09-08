.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-06-21 10:10

========================================
平衡二叉搜索树
========================================

.. index::
    self_balancing

定义
==============

一个 **平衡二叉搜索树** (或者 **height-balanced binary search tree**)是一种二叉树,
这种二叉树尽量保持它的高度在任何时刻都是最小的.

如下图所示:

一个非平衡的树如下:

.. image:: ../../image/unbalanced.png

一个平衡的树如下:

.. image:: ../../image/balanced.png

常用的操作
============

=================        =====================
操作                        时间复杂度
=================        =====================
查找                        O(log *n*)
插入                        O(log *n*)
删除                        O(log *n*)
遍历                        O(log *n*)
=================        =====================

实现
=========

常用的平衡二叉树包括有:

* AA tree
* :ref:`AVL树<AVL>`
* :ref:`红黑树<red_black>`

红黑树和AVL树比较常用.



参考资料
========================================

#. `Self_balancing_search_tree <http://en.wikipedia.org/wiki/Self-balancing_binary_search_tree>`_





