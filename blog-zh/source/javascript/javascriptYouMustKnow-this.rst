.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-09-26 23:57

========================================
javascript必知必会之this关键字及scope 
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

下面的代码片断缩进目前还不完善,你也可以选择 `下载pdf`_ 来阅读.


摘要
========================================


本系列博文主要谈一些在 `javascript`_ 使用中经常会混淆的高级应用,包括: `prototype`_, `closure`_, scope, this关键字.
对于一个需要提高自己javascript水平的程序员,这些都是必须要掌握的.

本节主要介绍this关键字和scope.

本文的javascript源代码从 `这儿 <http://sites.google.com/site/towerjoo/download/this.html?attredirects=0>`_ 下载.



.. contents::


引入
========================================

作为一个程序员, 你可能早已经习惯于面向对象语言中指代当前对象的引用(或者指针),
如的c++中的this或者 `python`_ 中的self,当然具有OO属性( `javascript`_ 其实更多的是一种所谓的函数式语言)的 `javascript`_ 同样,
它也具有引用当前属性的对象的指针(或者引用), 也就是this关键字.

为了理解this关键字,如果你只想记住一句话,那应该是 **this关键字总是指向当前函数的所有者对象(执行空间)**, 至于这句话如何理解,
可以参见下面的详细说明.

那么什么是 `scope`_ 呢?

`wikipedia`_ 中的解释是 *In computer programming, scope is an enclosing context where values and expressions are associated.*
中文即是所谓的 **作用域**, 它指明的是一个数值或者表达式所关联的上下文(能够被引用的执行空间).

`scope`_ 与this有什么关系呢? 如果从上面的定义来看, this指向的总是当前引用此函数的对象,而当你要判断当前引用的对象时,
这时你就得弄清楚当前函数所在的 `scope`_. 具体可见下面的分析.

this关键字
=================

请看下面的几个例子.

一个 `python`_ 的例子:

.. sourcecode:: python

    class Person(object):
        """a person class
        """

        def __init__(self, name):
            self.name = name    #这里的self指向的是实例化后的对象,如下面中的zhutao

        def get_name(self):
            return self.name

    zhutao = Person("zhutao")   
    print zhutao.name

一个 `javascript`_ 的例子:

.. sourcecode:: javascript

    window.name = "zhutao from window"
    var get_name = function(){
            return this.name;   // this的具体指向只能在运行时才能确定,也就是确定运行时调用其的对象
    };

    alert(get_name());  // 输出zhutao from window, get_name调用的对象为window
    var obj = {}
    obj.name = "zhutao from obj";
    alert(get_name.apply(obj)); // 输出zhutao from obj, 我们强制地使用了 apply来更改调用的对象,使其指向obj

    var innerobj = {
                "name" : "zhutao from innerobj"
    };
    innerobj.get_name = get_name;   // 使得innerobj的get_name方法指向了global scope的get_name函数
    alert(innerobj.get_name()); // 输出zhutao from innerobj, 此时this指向的是innerobj


那么从上面的简单例子来看, **this** 总是在 **运行时** 才能确定其具体的指向, 也才能知道它的调用对象.而
这点也正是 **动态语言** 一个重要特性.

那么如何确定当前this指向的引用对象呢? 通常可以这样判断:

#. 如果在global的scope(可以参见下面的说明来明确什么是global scope)来调用,则指向的是bowser的顶级对象window
   例如: `get_name()`
#. 如果, 有类似于这样的引用, `innerobj.get_name()` 则很显然this指向的是innerobj
#. 如果我们使用了apply, call来进行强制的引用对象指向, 则也会很显然地指向强制的对象,如
   `get_name.apply(obj)`.


关于apply和call
===================

这2个关键字可以很简单地理解为 **进行this引用对象(运行空间)强制转换**, 二者的语法如下:

* fun.call(object, arg1, arg2, ...)
* fun.apply(object, [arg1, arg2, ...])

二者目的是相同的(动态更改函数的运行空间, 或者称作更改this指向的对象), 只是在提供给函数的参数上的调用方法不同.

示例代码如下:

.. sourcecode:: javascript

    var test_call_apply = function(name, gender, school){
                alert(this.age + name + gender + school);
    };
    test_call_apply.call({age:24}, "zhutao", "male", "ISCAS");
    test_call_apply.apply({age:24}, ["zhutao", "male", "ISCAS"]);


scope详述
==============

先看下面几个例子:

.. sourcecode:: javascript

    var global_scope = "I'm global";
    var fun = function(){
        var fun_scope = "I'm in fun scope";
        return innerfun(){
            var inner_func_scope = "I'm in the inner fun scope";
            return global_scope + fun_scope + inner_func_scope; //此处的引用是重要的,请特别注意
        };
    };
    alert(fun()());

请注意上面的代码,其中:

#. global_scope 它是global scope
#. fun_scope 它是 位于一个函数的scope
#. inner_func_scope 是一个位于一个函数内的函数的scope

你也可以继续内嵌函数, 那么会生成若干个scope.

于是有个问题出现了, 为什么innerfun方法可以引用不在它自身scope的变量?

在回答这个问题之前,需要引入一个概念 **scope chain**. 所谓的 **scope chain** 是指
在 `javascript`_ 的代码中形成的一个具有优先顺序, 相关的作用域的链.

以上面的代码为例, 

#. 对于global的scope而言,它会为自己建立一个global的scope chain(当然此时,这个链只有一个scope).
#. 对于fun函数的scope而言, 它首先建立一个与global相同的scope chain,然后再加入自己的scope(此时,这个
   链有2个scope), 类似于这样的结构: global==>fun
#. 对于innerfun而言,除了fun函数所具有的链外,它还会加入自己的scope(当然,此时这个链有3个scope),
   类似于这样的结构: global==>fun==>innerfun

scope chain具有下面的特征:

#. 有序
#. 每当建立一个函数时,会自动生成一个scope并加入自己的scope chain中
#. 这个chain类似于一种栈,在查找变量时总是先从顶端查起

参见下图:

.. image:: http://farm4.static.flickr.com/3425/3958796284_615f096470_o.png

上图的3个部分对应上面代码中的三个变量的scope, 并且在对每个变量求值时,是按照
图中的scope chain从上到下依次查找,找到即返回值或者直到穷举了scope chain返回undfined.


那么现在回答上面那个问题:

其实也很好理解, 在计算某个表达式时, 它会对自己的scope chain进行从上到下的查找,如果找到了
它会立即返回这个值,如果找完了整个chain也没有找到,则返回undefined.

这个查找机制也就决定了,通常位于chain的前端的scope有更高的优先级.

例如 `javascript`_ 在计算 `global_scope + fun_scope + inner_func_scope;` 这个表达式时,
它会查找上面图示中的scope chain,从而确定出最后的结果.



一些说明
========================================

如果你弄清楚了上面的论述, 应该说你对this关键字和scope已经具有完全的知识基础了,但是
我们需要在实际中更好地使用和理解这些概念,这样才能把能力上升到别一个层次,
这也即所谓的 **理论与实践** 的关系.

请看下面这个例子:

.. sourcecode:: javascript

    var change_color = function(){
                this.style.color = "red";
    };
    window.onload = function(){
        var text = document.getElementById("text");
        text.onclick = change_color;    //此时this指向的是text这个对象(dom对象)
    };
    // 下面这行代码是在body中
    <span id="another" onclick="change_color()">My color will be changed2.</span> //这点需要特别注意, inline script指向的是window,此处会无定义



需要特别注意的是:

#. inline event registration中的this并非指向的是自己的dom节点,而是global scope的window,这点可以从上面的例子中得到证明
#. 这种inline event registration是不可取的, 推荐的是 `Unobtrusive JavaScript`_ (处理逻辑和页面结构相分离)



结论
========================================

`javascript`_ 是一种非常强大的动态语言, 它是 **披着C语言外衣的函数式语言**, 如果你只当作它是一种
类C的命令式语言,那么你的知识层次还过于低, 而倘若你能够理解到 `javascript`_ 的函数式语言本质,
你在运用 `javascript`_ ,理解 `jQuery`_ 及其它的库, 甚至自己写一些 `javascript`_ 都会游刃有余的.


后记
========================================

本系列的计划的内容已经结束,除了这些而外, 我还想写一至二篇补遗的 `javascript`_ 的高级知识来作为本系列的终结.
可能会写的内容包括:

#. `javascript`_ 函数式语言特征探究
#. `javascript`_ 相关库的分析
#. *Unobtrusive JavaScript* 的一些理解和实践

总之, `JavaScript`_ 本身是很值得探究的一个语言, 也有很多的值得一书的地方, 我希望后续能够不断地完成这个计划.

其实,之前写过 `Django开发必知必会`_ 以及本系列的 **javascript必知必会**, 发现在写这些内容的同时,自己的相关
知识也有了很大的提高, 写的同时, 站的角度不只是作为一个 **自学者** ,而是作为一个 **教者** ,我希望能够看到这些
内容的读者也能够受益. 所以我想后续,我可能会写一些 **计算机科学** 的其它专题, 如:

#. python必知必会
#. 正则表达式必知必会
#. Web开发必知必会
#. 等等

如果这个"宏伟"的计划得以完成, 我想也就成就我自已定义的一个 **优秀程序员** 的知识基础.

这是一个初步的计划, 我会逐渐展开的. 希望大家能够不断反馈.

谢谢.



参考资料
========================================

#. `javascript必知必会之closure`_
#. `javascript必知必会之prototype`_
#. `Unobtrusive JavaScript`_
#. `The this keyword`_



本文的源码
========================================

本文的rst源码链接在 `这里`_ .

点击 `这儿 <http://sites.google.com/site/towerjoo/download/this.html?attredirects=0>`_ 下载文中涉及的javascript源码.

.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _google reader: http://reader.google.com
.. _这里: http://sites.google.com/site/towerjoo/download/javascriptYouMustKnow-this.rst?attredirects=0
.. _javascript: http://en.wikipedia.org/wiki/JavaScript
.. _scope: http://en.wikipedia.org/wiki/Scope_(programming)
.. _jQuery: http://jquery.com
.. _python: http://python.org
.. _wikipedia: http://wikipedia.org
.. _prototype: http://www.cnblogs.com/mindsbook/archive/2009/09/19/javascriptYouMustKnowPrototype.html
.. _The this keyword: http://www.quirksmode.org/js/this.html
.. _Unobtrusive JavaScript: http://en.wikipedia.org/wiki/Unobtrusive_JavaScript
.. _Django开发必知必会: http://www.cnblogs.com/mindsbook/archive/2009/08/17/DjangoMustKnow.html
.. _javascript必知必会之closure: http://www.cnblogs.com/mindsbook/archive/2009/09/21/javascriptYouMustKnowClosure.html
.. _javascript必知必会之prototype: http://www.cnblogs.com/mindsbook/archive/2009/09/19/javascriptYouMustKnowPrototype.html
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _closure: http://www.cnblogs.com/mindsbook/archive/2009/09/21/javascriptYouMustKnowClosure.html
.. _下载pdf: http://sites.google.com/site/towerjoo/download/javascript%E5%BF%85%E7%9F%A5%E5%BF%85%E4%BC%9A%E4%B9%8Bthis%E5%85%B3%E9%94%AE%E5%AD%97%E5%8F%8Ascope.pdf?attredirects=0
