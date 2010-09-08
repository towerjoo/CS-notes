======================
C语言中指针的学习笔记
======================

.. index::
    pointer

.. highlight:: c


常见的注意问题
=================

#. *&* 是单目运算符,只能将 **内存中的对象** 进行赋值包括:
    
    * 变量
    * 数组元素

   它不能将下面的对象进行赋值,包括:

    * 常数
    * 表达式
    * *register* 变量

#. 指针的优先级:

    * 指针高于 **自述运算符**, 如 `y=*ip+1`, `*ip+=1`
    * 指针与自增自减运算符是向右结合的,如 `++*ip`, `(*ip)++`

指针与数组
============

#. **能使用数组下标完成的地方,都可以使用指针来替换完成**
#. 记住二者的区别:

    * 指针是个变量,可以 **被赋值**, **算术运算** 等变量适合的运算
    * 数组名, **不是变量**, 不能施加相关的运算

.. note::

    指针与字符数组的区别:

    ::

        //char array, it means declare a char array ,and initiate it with some chars
        char amessage[] = "now is the time"; 

        // a pointer which points to a string constant, and may chang later
        // so you can't change the string's content like this:
        // pmessage[0] = 'n';   //ERROR
        char \*pmessage = "now is the time";

指向函数的指针
===============

例如 `int (*comp)(void *, void*)` 指: *comp* 是指向具有两个 `void *` 参数的并返回一个 *int* 的函数的 **指针**.

指向函数的指针数组: `void (*func_table[])()={a,b,c,d,e}`, 其中,a,b,c,d,e是函数


指针数组与数组指针
====================

int (\*array)[4] : (, ) operators have higher priority because it is on the left of the [,]. So, it is a POINTER to [4].
Again.. It is a POINTER. So, it means it is a pointer to array.

int \*array[4] : [,] have heigher priority than \*, so, it is ARRAY of pointers.
It is not pointer, it is ARRAY.
