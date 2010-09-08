========================
learning python学习心得
========================

.. highlight:: python
   :linenothreshold: 5

到主页的链接
==============

   `回到主页 <http://learning-notebook.appspot.com>`_

   注意此处回到的是最初始页面，即 *http://learning-notebook.appspot.com*

关于learning python
=====================

.. note::

    [1]_ *learning python* 是亚马逊评价很高的一本书,讲得比较细致和全面,要好好学习.

    下面引用的页码都是pdf中的页码.

.. index::
    import

关于import
=============

.. note::

    p91,import一个module时发生的动作有:找到导入的文件,编译为字节码(byte code),运行生成的字节码.因而,Python的设计使得导入的行为只能执行一次所导入的代码(即使有多次导入行为).如:
    ::

        import testprint    
        #假设testprint module中有一个print语句,此时会输出print后的字符串
        # do some thing
        import testprint    #此时则不会输出

    如果真要使其在当前程序中执行导入的文件,则须使用 ``reload(moduleName)``

    同样可以使用 ``execfile('module.py')`` 来执行一个文件,与import不同的是,它没有导入模块,它只是 **将module.py中的代码拷贝到执行execfile处**. 因此它有覆盖当前变量的可能.


.. [1] learning python 3rd Edition

python类型继承关系(type hierarchies)
===========================================
.. note::

    python中的继承关系图.

.. image:: ../image/type-hierarchies.JPG
    :width: 700
    :height: 800

python中的函数
=================
.. note::

    p346.
    
    * def是可执行的代码.即是一个 [2]_ statement(语句), 它可以置于任何语句可以放置的位置.(与C/C++不同)
    * def生成了一个对象(函数对象),并将其赋值给一个名称(即函数名作为新的函数对象的一个引用)
    * return返回一个结果对象给调用者
    * 参数按照 **赋值** (对象引用)来传值

    python的哲学:在Python编程中,我们编制对象 **接口**, 而非 **数据类型**.
    ::

        def times(x, y):
            return x*y

        times(2, 4)     # return 8
        times("ok", 4)  # return "okokokok"
        #所谓的多态,即只要传入的参数支持 * 运算(接口),则函数times可用,而不用考虑数据类型.


.. [2] statement在计算机中是指一段无返回值的指令.

python中的作用域
=====================

.. note::

    python中的作用域,即变量的作用范围.

    Python变量作用域的查询规则(引用 X):

    * 首先在当前的local scope(function)中查找
    * 其次在其中的嵌套函数中查找
    * 然后在当前的global scope中(module file)
    * 最后在built-in scope(module __builtint__)中查找

    ::

        def f1():
            x = 88
            def f2():
                print x
            return f2

        action = f1()
        action()        # will print 88

    在这个例子中, ``print x`` 中的引用x,会首先在f2()中查找,失败;
    则在嵌套函数中查找,成功,此时x = 88.


python中两种类型的类
=======================

.. note::

   python中有两种类型的类，即classic class和new-style class
   它们在多重继承时的搜索顺序有较大差别，前者使用depth-first search
   后者使用broad-first search

classic class
-----------------

    ::

        class A:
            attr = 1
        class B(A):
            pass
        class C(A):
            attr = 2
        class D(B, C):
            pass

        x = D()
        print x.attr    #此处应该返回 1,因为classic class使用的是深度优先搜索
        # 搜索顺序是：从左到右，深度优先搜索

new-style class
--------------------

.. note::

   python中的new-style class是要么继承于build-in type，要么继承于object（任务的class都是object的子类）

   ::

        class A(object):
            attr = 1
        class B(A):
            pass
        class C(A):
            attr = 2
        class D(B, C):
            pass

        x = D()
        print x.attr    #此处应该返回 2,因为new-style class使用的是广度优先搜索
        #搜索顺序是，从左到右（根据继承顺序），广度优先

        #如果想在new-style class中模拟classic class，可以直接指定对应类中的变量，可以这样：
        class D(B, C):
            attr = B.attr
        x = D()
        print x.attr    #输出1
            

关于Python的伪私有变量（方法）
-------------------------------

.. note::

   伪私有变量是指在Python的类定义中以两个_开头，不以两个_结束的变量或者方法，
   在具体的使用中，其实例不能直接引用这些属性（所谓的 *伪* 是也），但是可通过
   间接的方法，即_类名+变量名（无+号）

   ::

        class test:
            """To test the pseudoprivate attribute in python
            """
            def __init__(self):
                self.__x = "zhutao"

        c = test()
        print c.__x #will raise error
        print c._test__x #will print 'zhutao'

    
python new-style类中的一些特别方法
---------------------------------------

.. note::

   可能某些部分也适合classic class,会特别指出。

.. index::
   slots

Instance slots
^^^^^^^^^^^^^^^^^^^

.. note::

   用来限制可供访问的属性集，这样可以避免拼写错误,也可以节省访问时间（slot中的属性存于tuple中而非dict中）等。使用特殊属性 ``__slots__``
   在继承了含有slots声明的父类的子类中，如果没有显式声明，则无slot特性，而是使用dict.

   ::

        class limiter(object):
            
            __slots__ = ['age', 'name', 'job']

        x = limiter()
        print x.age #error, 在使用前必须先赋值
        x.age = 4
        print x.age #ok

        x.sex = "female"  #error, no such attribute

        class Subclass(limiter):
            pass

        e = Subclass()
        e.sex = "female" #ok, subclass uses the dict, not slot

.. index::
   property

python property
^^^^^^^^^^^^^^^^^

.. note::

   property可以定义一个类的属性，很容易地定义getter, setter, deleter, 及docstring.
   property也可使用 :ref:`decorator` 来实现

   ::

        class C(object):
            def __init__(self):
                self._x = None

            def getter(self):
                return self._x
            
            def setter(self, value):
                self._x = value

            def deleter(self):
                del self._x

            #此处的参数名应与上面定义的部分相同，但具体使用什么方法名，不重要。
            x = property(getter, setter, deleter, None) 

            # 此处的getter, setter, deleter, docstring必须符合相应的协议（如参数列表，返回值等），
            #如果docstring为None,则使用getter的docstring

        #也可以按照下面的方法来使用property
        class D(object):

            def __init__(self):
                self._x = None

            @property
            def x(self):

                return self._x

            @x.setter
            def x(self, value):

                self._x = value

            @x.deleter
            def x(self):

                del self._x

        #此类实现了与C相同的功能，不过采用的方式是不一样的，decorator的方法更加灵活有效。
        #如果对x没有声明相应的setter和deleter，则属性x为只读的属性（可用于模拟类似c++中的const）
        

参考：

    1. `python property <http://docs.python.org/library/functions.html#property>`_
    2. `python decorator <http://docs.python.org/glossary.html#term-decorator>`_



.. index::
   decorator

.. _decorator:

python decorator
^^^^^^^^^^^^^^^^^^^

.. note::

   python decorator是函数的基础上执行一定的额外操作，通过@wrapper形式的语法。
   decorator返回的对象的唯一限制是：必须是callabe，所以function，class with __call__也是可以作为decorator

   ::

        class myDecorator(object):
            def __init__(self, f):
                print "inside myDecorator.__init__()"
                f() #Prove that function defination has completed
            def __call__(self):
                print "inside myDecorator.__call__()"

        @myDecorator
        def aFunction():
            print "inside aFunction()"

        print "Finished decorating aFunction()"
        aFunction()
        #执行结果如下：
        #   inside myDecorator.__init__()
        #   inside aFunction()
        #   Finished decorating aFunction()
        #   inside myDecorator.__call__()
        

从上面的例子的输出的结果来看，需要注意的是：

    * myDecorator的构造函数(__init__)是在被修饰的函数位置执行
    * 先会执行被修饰的函数的函数体
    * decorator会在构造函数中得到被修饰的函数对象
        

.. note::

    the @ is just a little syntax sugar meaning,
    "pass a function object through another function and 
    assign the result to the original function."
    
    **You can apply code to other code with decorator**

另外一个例子：

    ::

        class EntryExit(object):
            def __init__(self, f):
                self.f = f

            def __call__(self, *args, **kwag):
                print "Enter %s" % self.f.__name__
                self.f(*args, **kwag)
                print "Exit %s" % self.f.__name__

            @EntryExit
            def sum3(a, b):
                print a+b

            sum3(2,3)

        #输出为：
        #   Enter sum3
        #   5
        #   Exit sum3

        #因为function也是callable，所以上面的例子可改为：
        def entryexit(f):
            def new_f(*args, **kwag):
                print "Enter %s" % f.__name__
                f(*args, **kwag)
                print "Exit %s" % f.__name__
            return new_f

        @entryexit
        def sum4(a, b):
            print a+b

带参数的decorator的例子

    ::
        
        class EntryExit(object):
            def __init__(self, *args, **kwag):
                self.args = []
                for a in args:
                    self.args.append(a)
                for k,v in kwag.iteritems():
                    setattr(EntryExit, k, v)

            def __call__(self, f):
                def wrapper(*arg, **kw):
                    print self.args
                    f(*arg, **kw)
                return wrapper

        @EntryExit("zhutao")
        def zhutao(age=24):
            print age

        # will print: ['zhutao']\n24

同样也适用于函数的decorator
所以decorator可以方便地在一个函数之前或者之后加入相应的操作处理，类似于AOP.
参考：

    1. `Decorators I: Introduction to Python Decorators <http://www.artima.com/weblogs/viewpost.jsp?thread=240808>`_
    2. `PythonDecoratorLibrary <http://wiki.python.org/moin/PythonDecoratorLibrary>`_
        

.. index::
    abstract class

abstract superclass 抽象基类
==================================
.. note::

    抽象基类是指期待其部分行为由其子类来实现的基类（父类），如：
        

    ::

        # Super中无action的实现，它期待其子类实现
        class Super:
            def method(self):
                print "in Super.method"
            def delegate(self):
                self.action()

        class Provider(Super):
            def action(self):
                # do something here
                print "in Provider.action"


.. index::
    callback function

回调函数Callback function
==========================
.. note::

    使用回调函数来保持状态信息，可能是Python中最好的方法（相比于global变量，嵌套函数，可变类型等）。

    ::

        class Callback:
            def __init__(self, color):
                self.color = color
            def __call__(self):
                return "turn", self.color
        cb1 = Callback("blue")
        cb2 = Callback("red")

        B1 = Button(command = cb1)  #Register handlers
        B2 = Button(command = cb2)  #Register handlers
        #那么在响应相应的事件时，会调用回调函数（类）cb1(),cb2()，从而得到不同的处理

    常用的三种保持状态信息的方法：

    *   上述的方法
    *   使用缺省的lambda函数，如 ``cb3 = (lambda color='red':'turn' + color)``
    *   使用类中的bound method，例如：

    ::

        class Callback:
            def __init__(self, color):
                self.color = color
            def changeColor(self):
                print "turn", self.color

        cb1 = Callback("blue")
        cb2 = Callback("red")

        B1 = Button(command=cb1.changeColor)
        B2 = Button(command=cb2.changeColor)

    通常第三种方法没有第一种常用。

    
.. index::
   exception
   异常处理

异常处理总结
=============

.. note::

   使用异常，可以一步跳到异常处理部分，终止所有suspended函数。
   所以可以认为：异常是一各 *super-goto* .

异常处理的作用
--------------
在Python中异常处理的主要作用包括：

    1. 错误处理
    2. 事件通知
        可以使用异常来代替flag来进行事件通知。
    3. 特殊情形处理
    4. 终止动作
        使用try..finally可以在即使出现异常的情况下，也能够执行某些既定的终止动作。
    5. 特殊的控制流

具体的语法
-----------

    1. try..except结构
        工作原理：当一个try开始后，Python标记当前的程序上下文(context），所以当有异常
        发生时，可以返回。在try中的block先执行，如果：

        * 如果在try的block的执行过程发生异常，python则跳回到try，并且执行第一个匹配异常
          的except block中的操作。控制在整个try后继续进行。
        * 如果在try的block中发生异常，并且没有相应的except匹配，则异常得以传播（传播到上一个
          try或者进程的顶层）
        * 如果在try的block中无异常产生，则Python会执行else(如果有的话）中的语句
          然后控制在整个try后继续进行。
    2. try..(except..else..)..finally..结构
        finally后的block总会得以执行，无论是否有异常产生。

        *to serve as the cleanup action*

    3. raise产生异常

相关的代码
--------------

try..finally..

    ::

        class MyException(Exception):
            pass

        def action(file):
            raise MyException()

        file = open("hello.txt", "w")
        try:
            action(file)
        finally:
            file.close()                        #无论是否出现异常，文件都会被关闭
            print "file has been closed safely."    

raise with extra data

    ::

        class myException(Exception):
            pass

        def raise1():
            raise myException, "hello"
        def raise2():
            raise myException

        def tryer(func):
            try:
                func()
            except myException, extradata:
                print "got this:", extradata
        tryer(raise1)   #print: got this: hello
        tryer(raise2)   #print: got this:


