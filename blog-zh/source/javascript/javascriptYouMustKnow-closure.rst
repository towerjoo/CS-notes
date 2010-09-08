.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-09-20 16:35

========================================
javascript必知必会之closure
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

下面的代码片断缩进目前还不完善,你也可以选择 `下载pdf`_ 来阅读.


摘要
========================================

本系列博文主要谈一些在 `javascript`_ 使用中经常会混淆的高级应用,包括: `prototype`_, closure, scope, this关键字.
对于一个需要提高自己javascript水平的程序员,这些都是必须要掌握的.

本节主要介绍closure.


.. contents::





什么是closure
========================================

一种定义是:

A "closure" is an expression (typically a function) that can have free variables together with an environment that binds those variables (that "closes" the expression).

我的理解是: *closure* 是一个表达式(通常是一个函数), 这个表达式与一个 **环境** 共享着一些自由变量, 而这个 **环境** 则 **绑定** 
着那些自由变量(或者说 **结束** 这个表达式, 这也是所谓 *closure* 的名字由来). 所谓的 **环境** 就是一个更大的block, 所有的自由变量在这个 block 中
声明(有意义). 而 **绑定** 也就是指这些自由变量的作用域就是这个环境.

举个简单的例子.

.. sourcecode:: javascript

    var flag = false;   //调试开关
    // env 既是所谓的环境
    // 而inner就是所谓的表达式, name即是所谓的自由变量
    function env()  //整个env可以看作是一个closure
    {
        var name = "zhutao";

        function inner()
        {
            return name + " is a student.";
        }
        return inner;   //返回的是一个内部函数
    }//closure结束

    flag = true;

    if (flag)
    {
        // 此处是最神奇的地方, 代码执行在此处, inner函数其实已经出了env的body,
        // 而仍然能够被引用, 这就是所谓形成了一个 closure
        var inner_func_ref = env(); // 这时候inner_func_ref引用的就是inner()函数对象
        alert(inner_func_ref());   // zhutao is a student.
    }

而在上面的例子中, 函数env就是所谓的定义中的 **环境**, 函数inner就是定义中所谓的 **表达式**, 
而name即是所谓的 **自由变量**, **绑定** 在env这个 **环境** 中. env的结束也即closure的结束.

**而在javascript中,如果内部函数出了自己的所在的外部函数的body仍然能够引用,则会形成所谓的closure.**

在具体了解closure之前,我们需要了解一些其它的知识.

执行空间(执行上下文, Execution Context)
==========================================

在 `javascript`_ 中,每行可执行的代码都具有一定的 **执行空间**, 如全局的执行空间, 函数的执行空间,
递归后的函数执行空间等. 而一个完整的 `javascript`_ 执行过程,可以看作是有一个 **执行空间栈** ,不断地
进行 **执行空间** 的变化(出栈,进栈).

这个是很重要的概念,这个概念的理解与本系列的将要完成的另一篇文章 **this关键字** 的理解也是密切相关的.

详细解释请参考即将完成的 **this关键字** 的博文.
    
执行空间可以理解为具有属性的对象集, 但是通常这些属性都不是可随意访问的, 而这些对象集为代码的执行
提供了一定的上下文(空间).

当执行到一个函数时, 会建立此函数的执行空间(所谓进栈), 执行结束了, 从此执行空间退出返回到原来的执行空间(所谓
的出栈),而js解释器在运行过程中一起维护着这样一个 **执行空间栈** 来为不同的代码提供不同的执行空间.

那么执行空间与closure有什么关系?

简单地说,一定的执行空间对应着一定的closure, 只有位于同一个closure的方法才能访问同一closure的变量.

举个简单的例子:

.. sourcecode:: javascript

            // 关于context的例子

            flag = true;

            var tmpobj = {
                name : "zhutao",
                func : function(){
                    return "call by func " + this.name;
                }
            };
            if (flag)
            {
                // 代码执行在此处时context还是global
                alert(tmpobj.name);
                alert(tmpobj.func());   //进入func的context
                // 回到global的context
            }



closure的一些用法
=================

**当内部函数和自由变量位于同一closure时,可以随意访问,而声明顺序并不重要.**

几个常用的例子:

.. sourcecode:: javascript

            //一些应用

            flag = true;
            function OuterFun()
            {
                var num = 100;
                var printNum = function(){alert(num);}  //此处引用的num是引用,而不是值,所以后面改变num,此处的num同样生效
                num ++;
                return printNum;
            }
            var myfunc = OuterFun();
            myfunc();   //输出的是101,而不是100

            //另一个例子,下面的例子,可以看到匿名函数(内部函数)先于外部函数变量的声明,但是仍然能够访问外部函数的变量
            // 也就是说内部函数与外部函数的变量位于同一个closure, 所以可以访问

            function SameClosure()
            {
                var iCanAccess = function(){alert(name);};
                var name = "zhutao";
                return iCanAccess;
            }
            var testSameClosure = SameClosure();
            testSameClosure();// zhutao

            // 另一个应用,关于module pattern, 这样可以实际所谓的 private, public等方法和变量
            var module = (function Module(){
                var privateVar = "zhutao is private";   // private
                return {
                    publicGetPrivateVar : function(){
                    return privateVar;
                    },  // public method, 可以取所谓的private变量
                    publicVar : "I'm a public variable" // public variable
                };
            })();

            if (flag)
            {
                alert(module.publicGetPrivateVar());    // zhutao is private
                alert(module.publicVar);                // I'm a public variable
                alert(module.privateVar);               // undefined
            }





关于closure的效率
====================

因为在closure的实际应用可能会多次去生成一个内部函数(匿名),所以存在可能的效率问题.(对象的建立,内存管理释放等).

所以,应该尽量减少内部函数的生成, 而使用函数的引用.

例如:


.. sourcecode:: javascript

    // 关于效率的例子
    flag = false;
    // 这样,每次调用Outer时会产生匿名函数的开销
    function Outer(obj)
    {
        obj.fun = function(){
            alert("I am " + this.name);
            };
    }

    if (flag)
    {
        var obj = { name : "zhutao"};
        Outer(obj);
        obj.fun();
    }

    // 更好的处理方式

    function Outer_better(obj)
    {
        obj.fun = showme;   // 这样调用的只是函数的引用
    }

    function showme()
    {
        alert("I am " + this.name);
    }

    if (flag)
    {
        var obj2 = { name : "zhutao"};
        Outer_better(obj2);
        obj2.fun();
    }






应用建议
========================================


::

    Don't use closures unless you
    really need closure semantics.
    In most cases, nonnested
    functions are the right way to go.

        Eric Lippert, Microsoft

上面的论述是基于效率的考虑, 而 IE 4-6 在使用closure时可能会存在内存泄露的问题,参考 `JavaScript Closures`_ 中的相关部分.


而在某些场合,你可能必须要使用closure, 如 **循环问题**.

代码:

.. sourcecode:: javascript

    flag = true;

    // 向body中生成一些链接,然后绑定事件
    function addLink(num)
    {
        for(var i=0; i<num; i++)
        {
            var link = document.createElement('a');
            link.innerHTML = "Link " + i;
            link.onclick = function(){
                alert(i);
            };
            document.body.appendChild(link);
        }
    }   //可惜的是,当你点击每个链接时,输出的都是 Link 4


    // 使用closure 可以解决这个问题
    function addLink2(num)
    {
        for(var i=0; i<num; i++)
        {
            var link = document.createElement('a');
            link.innerHTML = "Link" + i;
            link.onclick = function(j){ //使用closure
                return function(){
                    alert(j);
                };//返回一个函数
            }(i);//调用这个函数
            document.body.appendChild(link);
        }
    }

    window.onload = addLink(4);
    window.onload = addLink2(4);

为什么会出现上面的这个问题?(事实在之前的的一个项目中,也遇到了相同的问题,但是当时还不懂closure, 也是一头雾水)

这是因为,对于addLink, 在退出addLink函数之前, i已经变成了4,所以无论后面的事件触发,输出的都是4.

但是后者,使用了closure.使得j引用了当前的循环中的i,所以对于每个后续触发事件,都会按照预期地得到相应的结果.

具体的讨论可见: `SO`_

这即是一个典型的closure应用场景, 而如果不使用, 就无法解决这个问题.

结论
========================================

下面这段摘抄自 `Summary of JavaScript closures <http://www.javascriptkit.com/javatutors/closures3.shtml>`_ :

#. 当你在一个函数中使用另一个函数时, 会产生一个closure
#. 当你使用eval()时, 会产生一个closure.
#. 最好认为closure总是在函数入口处产生,并且本地变量自动添加到closure中

其它的细节可参考上面的链接.

总之, 关于closure,你必须记住以下几点:

#. closure就是提供了一种变量共享的机制(内部函数可以访问外部函数的变量)
#. 注意closure可能引用的效率问题(如何避免,参见文中详述)
#. 具体的应用场景要熟悉

上篇博文讲的是 `prototype`_, 下篇博文预计会讲 **this关键字**, 欢迎大家讨论和留言.


    


参考资料
========================================

#. `JavaScript Closures`_
#. `Explaining JavaScript Scope And Closures`_
#. `JavaScript Closures 101`_ 
#. `JavaScript and memory leaks`_
#. `Closures in JavaScript`_

本文的rst源码
========================================

本文的源码链接在 `这里`_ .

本文中涉及的javascript代码可以在 `这儿`_ 下载. 

你也可以选择 `下载pdf`_ 来阅读.


 








.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里:
.. _Javascript Closures: http://www.jibbering.com/faq/faq_notes/closures.html
.. _Explaining JavaScript Scope And Closures: http://robertnyman.com/2008/10/09/explaining-javascript-scope-and-closures/
.. _SO : http://stackoverflow.com/questions/1451009/javascript-infamous-loop-problem
.. _JavaScript Closures 101: http://www.javascriptkit.com/javatutors/closures.shtml
.. _JavaScript and memory leaks: http://www.javascriptkit.com/javatutors/closuresleak/index.shtml
.. _Closures in JavaScript: http://james.padolsey.com/javascript/closures-in-javascript/
.. _javascript: http://en.wikipedia.org/wiki/JavaScript
.. _prototype: http://www.cnblogs.com/mindsbook/archive/2009/09/19/javascriptYouMustKnow1.html
.. _下载pdf: http://sites.google.com/site/towerjoo/download/javascript%E5%BF%85%E7%9F%A5%E5%BF%85%E4%BC%9A%E4%B9%8Bclosure.pdf?attredirects=0
.. _这儿: http://sites.google.com/site/towerjoo/download/closure.html?attredirects=0
