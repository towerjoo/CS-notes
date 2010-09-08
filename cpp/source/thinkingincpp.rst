============================
Thinking in c++学习笔记
============================

.. highlight:: cpp

关于函数
===========

``int func2()`` 这样的函数声明在c中表示 **可带任意参数的函数**
,而在c++中表示 **不带参数的函数**

在c和c++中可声明 ``int func2(void)`` 这样的函数用来定义不带参数的函数。

关于变量的声明与定义
=========================

::
        
        extern int x; //表明是一个变量的声明，而非定义
        int y;      //既是声明又是定义


类型转换
============

类型转换会强制编译器将一个数据看做比它实际上更大（或者更小）的类型，
所以会占用更多（或者更少）的内存空间，可能会破坏其它数据。
如：

::
        
        int b=200;
        unsigned long a = (unsigned long int)b; //c language style

c++的显式类型转换

常用关键字包括：

  * static_cast
  * const_cast
  * reinterpret_cast
  * dynamic_cast




        
