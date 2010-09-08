.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-09-19 16:56

========================================
javascript必知必会(一)
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `RSS <http://www.cnblogs.com/mindsbook/rss>`_ 进行订阅.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,
请直接在 `google reader`_ 中手动添加).


摘要
========================================

本系列博文主要谈一些在 `javascript`_ 使用中经常会混淆的高级应用,包括: prototype, closure, scope, this关键字.
对于一个需要提高自己javascript水平的程序员,这些都是必须要掌握的.

本节主要介绍prototype.



.. contents::





起由
========================================

最近在做一个项目,里面大量地使用 `javascript`_ 作为页面的动态生成脚本, 使用 `json`_ 与服务器进行通信.
在读之前遗留的代码时, 经常会弄不清楚, 作用域, this关键字在当前context下的指向等,于是便开始专门学习了
相关的知识,记录下来与大家分享.

下面的内容中会有一些代码,建议大家也去尝试修改和理解,这样更容易掌握. 点击 `这儿`_ 下载所涉及到的源码.

prototype
======================

`javascript`_ 是一种 `prototype based programming`_ 的语言, 而与我们通常的 `class based programming`_ 有很大
的区别,我列举重要的几点如下:

#. 函数是first class object, 也就是说函数与对象具有相同的语言地位
#. 没有类,只有对象
#. 函数也是一种对象,所谓的函数对象
#. 对象是按 **引用** 来传递的

那么这种 `prototype based programming`_ 的语言如何实现继承呢(OO的一大基本要素), 这也便是 *prototype* 的由来.

看下面的代码片断:

.. sourcecode:: javascript

    function foo(a, b, c)
    {
        return a*b*c;
    }

    alert(foo.length);
    alert(typeof foo.constructor);
    alert(typeof foo.call);
    alert(typeof foo.apply);
    alert(typeof foo.prototype);

对于上面的代码,用浏览器运行后你会发现:

#. length: 提供的是函数的参数个数
#. prototype: 是一个object
#. 其它三个都是function

而对于任何一个函数的声明,它都将会具有上面所述的5个property(方法或者属性).

下面我们主要看下prototype.

.. sourcecode:: javascript

    // prototype
    
    function Person(name, gender)
    {
        this.name = name;
        this.gender = gender;
        this.whoAreYou = function(){//这个也是所谓的closure, 内部函数可以访问外部函数的变量
            var res = "I'm " + this.name + " and I'm a " + this.gender +".";
            return res;
        };
    }
    // 那么在由Person创建的对象便具有了下面的几个属性
    Person.prototype.age = 24;
    Person.prototype.getAge = function(){
        return this.age;
    };
    flag = true;
    if (flag)
    {
        var fun = new Person("Tower", "male");
        alert(fun.name);
        alert(fun.gender);
        alert(fun.whoAreYou());
        alert(fun.getAge());
    }

    Person.prototype.salary = 10000;
    Person.prototype.getSalary = function(){
        return this.name + " can earn about " + this.salary + "RMB each month." ;
    };

    // 下面就是最神奇的地方, 我们改变了Person的prototype,而这个改变是在创建fun之后
    // 而这个改变使得fun也具有了相同的属性和方法
    // 继承的意味即此
    if (flag)
    {
        alert(fun.getSalary());
        alert(fun.constructor.prototype.age);//而这个相当于你直接调用 Person.prototype.age
        alert(Person.prototype.age);
    }

从上面的示例中我们可以发现,对于prototype的方法或者属性,我们可以 **动态地** 增加, 而由其创建的
对象自动会 **继承** 相关的方法和属性.

另外,每个对象都有一个 *constructor* 属性,用于指向创建其的函数对象,如上例中的 `fun.constructor` 指向的
就是  `Person`.

那么一个疑问就自然产生了, **函数对象中自身声明的方法和属性与prototype声明的对象有什么差别?**

有下面几个差别:

#. 自身声明的方法和属性是 **静态的**, 也就是说你在声明后,试图再去增加新的方法或者修改已有的方法,并不会
   对由其创建的对象产生影响, 也即 **继承** 失败
#. 而prototype可以动态地增加新的方法或者修改已有的方法, 从而是 **动态的** ,一旦 **父函数对象** 声明了相关
   的prototype属性,由其创建的对象会 **自动继承** 这些prototype的属性.

继续上面的例子:

.. sourcecode:: javascript

    flag = true;
    // 函数内部声明的方法是静态的,无法传递的
    Person.school = "ISCAS";
    Person.whoAreYou = function(){
        return "zhutao";
    };//动态更改声明期的方法,并不会影响由其创建的对象的方法, 即所谓的 静态
    if (flag)
    {
        alert(Person.school);
        alert(fun.school);//输出的是 "undefined"
        alert(Person.whoAreYou()); //输出 zhutao
        alert(fun.whoAreYou()); // I'm Tower and I'm a male.
    }

    Person.prototype.getSalary = function(){
        return "I can earn 1000000 USD";
    };
    if (flag)
    {
        alert(fun.getSalary());//已经继承了改变, 即所谓的 动态
    }

既然有函数对象本身的属性, 也有prototype的属性, 那么是由其创建的对象是如何搜索相应的属性的呢?

基本是按照下面的流程和顺序来进行.

#. 先去搜索函数对象本身的属性,如果找到立即执行
#. 如果1没有找到,则会去搜索prototype属性,有2种结果,找到则直接执行,否则继续搜索 **父对象** 的 **父对象**
   的prototype, 直至找到,或者到达 *prototype chain* 的结尾(结尾会是Object对象)

上面也回答如果函数对象本身的属性与prototype属性相同(重名)时的解决方式, 函数本身的对象 **优先** .

再看一个多重prototype链的例子:

.. sourcecode:: javascript

    // 多重prototype链的例子
    function Employee(name)
    {
        this.name = "";
        this.dept = "general";
        this.gender = "unknown";
    }

    function WorkerBee()
    {
        this.projects = [];
        this.hasCar = false;
    }
    WorkerBee.prototype = new Employee; // 第一层prototype链

    function Engineer()
    {
        this.dept = "engineer"; //覆盖了 "父对象" 
        this.language = "javascript";
    }
    Engineer.prototype = new WorkerBee; // 第二层prototype链

    var jay = new Engineer("Jay");
    if (flag)
    {
        alert(jay.dept);    //engineer, 找到的是自己的属性
        alert(jay.hasCar);  // false, 搜索到的是自己上一层的属性
        alert(jay.gender);  // unknown, 搜索到的是自己上二层的属性
    }


上面这个示例的对象关系如下:

.. image:: http://farm3.static.flickr.com/2585/3933273719_ccab4562d2.jpg


结论
========================================

`javascript`_ 的prototype给语言本身增加了很强的灵活性,但与 `class based programming`_
相比整个思维逻辑还是有很大的不同,所以需要更多地思考和揣摩.

而 **javascript是披着c语言外衣的函数式语言** 的理解自然也需要更多地思考.

下一节我会继续讨论下 `javascript`_ 的另一个重要而且比较容易弄错的知识 **closure**.

欢迎大家留言讨论.


参考资料
========================================

#. `json`_
#. `class based programming`_
#. `prototype based programming`_
#. `Using Prototype Property in JavaScript <http://www.packtpub.com/article/using-prototype-property-in-javascript>`_

本文的rst源码
========================================

本文的源码链接在 `这里`_ .

本文中涉及的javascript代码可以在 `这儿`_ 下载. 




.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _google reader: http://reader.google.com
.. _这里: http://sites.google.com/site/towerjoo/download/javascriptYouMustKnow.rst?attredirects=0
.. _prototype based programming: http://en.wikipedia.org/wiki/Prototype-based_programming
.. _class based programming: http://en.wikipedia.org/wiki/Class-based_programming
.. _javascript: http://en.wikipedia.org/wiki/JavaScript
.. _这儿: http://sites.google.com/site/towerjoo/download/codesnippet.html?attredirects=0
.. _json: http://en.wikipedia.org/wiki/Json
