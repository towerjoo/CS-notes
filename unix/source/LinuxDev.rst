=====================
Linux下的程序开发
=====================


使用getopt和getopt_long来处理命令行参数
=======================================

Linux下常用的CUI( *Command User Interface* )通常都含有以 - 开头的命令行参数,
因而处理这些参数则是常遇到的问题,而 **getopt** 和 **getopt_long** 则极大地方便
了编程者.

.. note::

    使用getopt来处理命令行的例子 
    :download:`使用getopt来处理命令行参数的例子 <../download/getopt_test.c>`

    .. literalinclude:: ../download/getopt_test.c
        :language: c
        :linenos:
