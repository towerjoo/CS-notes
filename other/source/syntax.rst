=============================
python一些重要但不熟悉的语法
=============================

.. highlight:: python
   :linenothreshold: 5

字符串相关
===========================

.. note::

    这部分很基础,但自己还不是十分熟悉,所要要特别注意.

1. raw string

   * 例如, ``s = r"hello world\n"``, 那么此处相当于 ``s = "hello world\\n"```
     也就是说,转义失去意义,只保留**原始(raw)**的字符
   * 还有就是常用于*正则表达式*中,如
     ::

        import re
        s = "hello world"
        rx = re.compile("[^ ]* ([a-z]*)")
        result = rx.sub(r"\1 is mine", s) #输出为 *world is mine*
        #如果上面不使用r打头的字符串,则可使用如下替换:
        result = rx.sub("\\1 is mine", s)

2. 三单引号字符串

   * 常用于多行的字符串,如
     ::

        s = '''hello, this is 
        Mrs. Brown.'''
        print s # 输出为二行的字符串

3. 字符串逆转

.. note::

    要得到一个字符串的逆序,可直接使用[]操作,如:

    ::
        
        s = "zhutao"
        t = s[::-1]
        #操作方法是,如果第三个选项为负数,即此处的-1,则表明采用逆转,那么,则从原字符串的最后一个字符开始,以此处的数为步进(step)来操作,得到结果,此处得到 oatuhz
        t = s[::-2]
        # 此处得到 t= 'oth'
        t = s[::3]  
        # 此处得到 t = 'zt'
        t = s[5:1:-1]   #返回oatu

    注意:list, tuple也适应此种操作.

4. 字符代码转换(char<->int)

.. note::

    * ord: 把一个字符转换为对应的ASCII整数代码
    * chr: 与ord相反,把一个ASCII整数代码转换为对应的字符


控制流相关
===============

while语句
    
    *   除了通常的while语法以外,还允许条件不为真时(即跳出while语句时)执行else语句,如:
        ::

            i = 10
            while i > 0:
                print i
                i -= 1
            else:
                print "i is less than 0" #输出为:10 9 8 7 6 5 4 3 2 1     i is less than 0

    .. note::

        如果在while循环体中使用break提前中断循环,则else不会执行

        **同样for语句也有类似的else分支语法**

数据结构
=========

字典
    *   注意的是,如果引用某个键重新赋值时,当此键不存在时,则会 **自动添加一个新键-值**
        如:
        ::

            x = {"name":"zhutao"}
            x['name'] = "yaya"  # x = {'name':'yaya'}
            x ['age'] = 24      # x = {'age':24, 'name':'yaya'}


赋值操作
===========

.. note::
    
    赋值操作只是复制了一次 **引用(reference)** 而不是拷贝,即二者 **依旧指向同一个内存地址**

    所以,

    ::

        x = [12,23,34]
        y = x   # 此时,x,y指向同一块内存
        del y[0]
        print x # [23,34]
        print y # [23,34]

    因而,要真正创建一个新的对象时,需要使用**切片操作**,即 ``y = x[:]``

类的变量和对象的变量
=====================

.. note::

    类的变量,是指在类的定义中以类名来引用的变量,此变量 **在各个实例中是共享的** , 相当于c++类中的静态变量

    对象变量,是指在类的定义中以self来引用的变量,此变量 **在各个实例中是独立的,各自有自己的存储空间**
    ::

        class Person:
            population = 0
            def __init__(self, name):
                self.name = name        #对象的变量,为各个实例单独引用
                Person.population += 1  #类的变量,在各个实例中共享
                #注:此处也可以使用 ``self.__class__.population += 1`` 替代,实现相同功能

            def __del__(self):
                print "%s says goodbye" % self.name
                Person.population -= 1
                if Person.population == 0:
                    print "I am the last one here"
                else:
                    print "we have %d persons left" % Person.population

            def howMany(self):
                if Person.population == 1:
                    print "I am the only person here"
                else:
                    print "There are %d persons here" % Person.population

        zhutao = Person("zhutao")
        zhutao.howMany()

        yaya = Person("yaya")
        yaya.howMany()
        #输出结果为:
        #I am the only person here
        #There are 2 persons here
        #zhutao says goodbye. we have 1 persons left
        #yaya says goodbye. I am the last one.

异常处理
============

.. note::

    对于某些即使发生异常,某些操作仍须执行时,可采用try...finally语句,例如:

    ::
        
        import time

        fh = file("test.data")  #假设存在文件test.data
        try:
            while(True):
                line = fh.readline()
                if len(line) == 0:  #认为文件结束
                    break
                print line,
                time.sleep(2)

        finally:
            fh.close()
            print "file has been closed!"
        #所以在执行过程中,如果在执行完毕前,按了ctrl+c中止目前程序的运行
        #fh.close()文件关闭动作依然会得以执行

类中的特殊语法
================

==========================  ============================================================================
特殊函数                        相关说明
==========================  ============================================================================
__init__(self, ..)              相当于c/c++中的构造函数,这个方法在新建对象恰好要被返回使用之前被调用
__del__(self)                   相当于c/c++中的析构函数,这个方法在对象删除之前被调用
__str__(self)                   在我们对对象使用print语句或者使用str()时调用
__lt__(self, other)             当使用 **小于** 运算符(<)调用,类似地,对于所有的运算符都有特殊的方法
__getitem__(self,key)           使用x[key]索引操作时调用
__len__(str)                    对序列对象使用内建的len()函数时调用
==========================  ============================================================================

可变长参数函数的使用
=========================

.. note::

    这是Python一个非常强大的功能,可使用元组(tuple)和字典(dict)两种变长参数函数.
    如:
    ::

        def max(*args):
            m = args[0]
            for s in args:
                if m<s:
                    m = s
            return m

        def test(**argv):
            for k,v in argv.items():
                print k,v

        #那么在调用时,可按如下方法
        max(1,2,3,0)
        max(3,4)
        test(name="zhutao", age=24)
        test(x = 1, y=2, z=3)


lambda语法
===================

.. note::

    lambda语法只能使用单个表达式作为函数体,而通常的语句是不能出现在lambda函数体中的,如print函数
    ::
        
        def make_repeater(n):
            return lambda s: s*n    #此处的函数体只是一个表达式,而且返回的是一个函数

        twice = make_repeater(2)    #那么此处twice即是一个函数
        print twice('world')
        print twice(5)

    *   lambda函数是一个表达式,而不是一个语句
    *   lambda函数:之后只能有一个表达式,亦即此处只能是一个返回值
    *   lambda函数虽然不能使用if, while等语句,但可以使用布尔短路来实现if,使用map来实现循环等,
        如 ```x and func(a) or func(b)``, 即,如果x为真则返回func(a),否则返回func(b)

嵌套函数
=============

.. note::

    嵌套函数适用于nested scope,即嵌套作用域,嵌套函数可以使用被嵌套函数的相关局部变量,如

    ::

        def f():
            x = 8
            def f2():
                x = 3
                print x
            return f2       #返回函数

        printx = f()
        printx()
        #此时输出为3,即在嵌套函数中改变了x的值,此语句也可写为 ``f()()``             

exec和eval
===============

.. note::
    
    exec用来执行储存在字符串中的Python语句,我们可以在运行时动态生成一个python代码的字符串,从而使用exec执行.
    如,
    ::

        exec("print 'hello world'")
        #输出为hello world

    eval用来计算存储在字符串中的Python表达式,如
    ::

        eval("2*3") #输出6

assert语句
==============

.. note::

    用于声明某个条件是真的.如果此条件不为真,则会引起一个错误,即AssertionError.
    如:
    ::
        
        mylist = ['item']
        assert len(mylist)>=1   #不为真则会引发AssertionError
        mylist.pop()
        assert len(mylist)>=1   #引发AssertionError
        
        eval('2*3')
        #输出为6

.. index::
    getattr

getattr的分发作用
=======================

.. note::

    getattr具有分发对象属性的作用,可以间接地使用此方法来使用相关接口.
    如:
    ::

        d = {"name":"zhutao", "age":24}
        getattr(d, "get")("name")       #此时则返回的是zhutao,相当于d.get("name")

    此方法同样可以使用在module,对象等


类中的私有属性
========================

.. note::

    在Python中类中的私有属性,通常是采用命名的方式来加以区分,即在属性前加 **2个下划线**

    但,此处的私有并非绝对私有,它只是一种习惯上的私有,而非强迫的私有,可以使用如下方式访问:
    ::

        class test:
            def __hello(self):  #习惯上的私有,而非强迫
                print "hello"

        x = test()
        x.__hello()     #报错,"test中无此方法"
        x._test__hello()    #正常输出hello, 但在实际代码中不要这么使用

松散(verbose)的正则表达式
===========================

.. note::

    python默认使用紧凑的正则表达式(即普通的正则表达式),但为了提高正则表达式的可读性,我们可以使用松散的,如:
    ::

        import re

        pattern = """
        ^               #匹配开始
        [0-9]{3,4}      #匹配3个或者4个数字
        -?              #匹配0个或者1个-符号
        [0-9]{7,8}      #匹配7个或者8个数字
        $               #匹配结束
        """
        #很显然上面的匹配式是用来匹配诸如029-82682345这样的中国电话号码的
        re.search(pattern, '029-3456789', re.VERBOSE)   
        #注意:此处的re.VERBOSE是用来标记此处用到的正则表达式是松散的,如果不加则会匹配失败

8进制与16进制
==================

.. note::

    在python中可以使用8进制和16进制的整数,使用方法如下:
    ::

        octal = 0123    #以0打头的整数,python认为其为8进制数
        hex = 0x123     #以0x或者0X打头的整数,python认为其为16进制数
        Hex = 0X123

    但在使用过程中,python会自动将其转换为10进制表达.
    也可以使用oct,hex函数来显式得到十进制数的字符表达( **返回的是str类型** )
    ::

        a = 255         #十进制整数
        b = hex(a)      #转换为16进制字符串
        c = int(b, 16)  #将b又转换为十进制整数

names, reference and objects
================================

.. note::

    python是一种动态类型语言,无需事前声明一个变量的类型.
    例如, ``a = 3`` 这条语句,在python中发生了如下几个步骤:

    * 生成一个表示3的对象
    * 生成变量a,如果a不存在
    * 将变量a **链接** 到新的对象3

    此时a则是对象3的一个引用(reference),在python内部采用指针来实现.
    类型信息存放于对象中,而非变量中,所以,
    ::

        a = 23
        a = [1,2]
        a = "spam"
        #在python中,只是a分别指向了不同的三个对象,而a本身是没有类型的
        #对象除了相关数据外,还通常包括:类型域,引用计数(即,多少个变量来引用自己)

    那么在指向了另一个对象后,前一个对象如何处理?

    因为对象本身有个引用计数域,所以当对象自己的引用计数为0时,则自动回收该对象,如上述中的23,[1,2]

.. image:: ../image/names-reference-object.JPG
    :width: 800
    :height: 250

==和is
=========
.. note::

    在python中可以用来判断二个变量是否 *相等* 的操作符,区别如下:

    * **==** 是比较二个变量的值(即二个变量所引用的对象的值)是否相等
    * **is** 是比较二个变量所指的对象是否相同

    ::

        a = [1,2,3]
        b = a
        a==b        # True
        a is b      # True
        c = [1,2,3]
        a==c        # True
        a is c      # False

    但是对于一小整数或者短的字符串,系统不会立即回收其对象的内存,而是进行了缓存(cache)留待后用,如:
    ::

        a = 42
        b = 42
        a == b  # True
        a is b  # True, 42被复用

    可以使用sys.getrefcount(object)来得到一个对象的引用计数.
    因为整数和字符串是不可更改的对象,所以大量的引用并不成问题,这样也能够提高性能.


关于增量赋值
===============

.. note::

    增量赋值指的是使用"+="操作符的一种操作.
    
    * 对于 **不可更改(immutable)** 的对象,如int,string,tuple等, s += a, 就等于 s=s+a, s+a会生成一个新的对象,
      而s是对此新对象的一个引用
    * 对于 **可更改(mutable)** 的对象,如list, dict等, s += a,则不会生成新对象,是对s **就地(in place)** 更新,
      如list, s+=a 相当于 s.extend(a), 那么改变a中的值会影响到新的s的值.

generator object相关
=======================

enumerate方法
--------------
.. note::

    在遍历一个iterable对象时,通常需要获得值和偏移量(value and offset), 可以使用位置计数, 但更常用的是enumerate.
    ::

        a = "spam"
        for (offset, value) in enumerate(a):
            print value, ' appears at offset', offset

    enumerate每次返回的是一个(offset, value)的tuple,它是一种generator对象

常见的错误
===============

关于append, update等函数
-------------------------

.. note::

    对于list, dict等类型,属于它们的方法如append,  extend, update等,它们的返回值为None,而不是变量本身,如:
    ::

        a = [1,2]
        a.append(3)         # a = [1,2,3]
        a = a.append(4)     # a = None

