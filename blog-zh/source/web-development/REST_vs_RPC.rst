.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-11-16 22:16

========================================
Web Service实践之REST vs RPC
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

点击 `下载pdf阅读`_.

摘要
========================================

`Web Service`_ 已经不再新鲜, 而随后的 `SOA`_, `Cloud Computing`_ 也不断出现, 直到百度也
提出了自己的 `框计算`_, 我们尚且不管这些时髦的名词背后所蕴藏的实际的技术创新有多少, 
但是他们终究是逃不出一点, 即 **如何解决访问服务的问题**, 而此处的服务通常不在本地而是在
遥远的你不知道的美国或者印度.

本文想阐述标题中提到的两种解决远程服务访问的方法,优缺点及其一些实际的建议等.



.. contents::


引入
========================================

我们每天都在使用浏览器来上网冲浪, 在查找自己需要的资源, HTTP协议自然是我们使用的最多的
一种, 我们尽情地享受着这种信息高速路的快感,却没有试图去了解我们是如何获得这些资源的?
它是一种什么样的设计理念?

我们也偶尔会使用 Gtalk来和自己的同事或者朋友来聊天, 我们在给朋友提供资源(信息)的同时
也获取着朋友的资源(信息), 我们是否可曾想过, 这种交流背后又是一种什么过程呢?

在这互联网的时代,只要牵扯到获得非本地的资源, 都会面临一个问题:

**如何访问服务呢?**

让我们先看看什么是 `Web Service`_.

Web Service
========================================
`Web Service`_ 也提出了好久了, 那么究竟什么是 `Web Service`_ ?

简单地说, 也就是服务器如何向客户端提供服务.

常用的方法有:

#. `RPC`_ 所谓的远程过程调用 (面向方法)
#. `SOA`_ 所谓的面向服务的架构(面向消息)
#. `REST`_ 所谓的 **Representational state transfer** (面向资源)

`SOA`_ 是前几年炒的很火的一个词, 不亚于当前的 `Cloud Computing`_ , 如果说 `RPC`_
是基于方法调用(method),那么 `SOA`_ 则是基于 **消息**, 基于方法调用通常会与特定的程序语言
耦合起来,而后者则与具体的实现语言无关, 所以在一定程度上得到大公司的支持.

本文不会在 `SOA`_ 上着笔过多, 主要是因为笔者本人对这个没有多少研究, 怕误导读者. 另, 笔者
最近对 `RPC`_ 和 `REST`_ 方式的原理和实现有一些研究, 所以本文会主要集中在 `RPC`_ 和 `REST`_. 

RPC
============

`RPC`_ 即远程过程调用, 很简单的概念, **像调用本地服务(方法)一样调用服务器的服务(方法)**.

通常的实现有 `XML-RPC`_ , `JSON-RPC`_ , 通信方式基本相同, 所不同的只是传输数据的格式. 

(如果你已经习惯于XML繁重的尖括号,你不妨可以尝试下更加轻型,高效,传输效率高的 `JSON`_.)

一个简单的通信过程通常为:

Request

.. sourcecode:: xml

    <?xml version="1.0"?>
    <methodCall>
      <methodName>member.get_username_by_id</methodName>
      <params>
        <param>
            <value><i4>1</i4></value>
        </param>
      </params>
    </methodCall>
    

Response

.. sourcecode:: xml

    <?xml version="1.0"?>
    <methodResponse>
      <params>
        <param>
            <value><string>Zhu Tao</string></value>
        </param>
      </params>
    </methodResponse>


向服务器发送一个过程调用的方法及其参数, 得到服务器返回的方法执行的结果.

在 `XML-RPC`_ 之后又有了更加强大的 `SOAP`_ , 用于一些比较复杂的系统之上. 


REST
===========

终于我们来看 `REST`_ 了, 呵呵, 这个是我目前比较喜欢的一个远程通信方法(架构).

`REST`_ 不是一种协议,它是一种架构, 一种 `Web Service`_ 能够如果满足 `REST`_ 的几个条件,
通常就称这个系统是 *Restful* 的.

这里提到的条件包括: 

#. C/S结构 (这是Internet服务的一个基本特征)
#. 无状态 (很熟悉吧,呵呵)
#. 可以cache (想起了浏览器?)
#. 分层系统 (想起了无数的架构?)
#. 统一的接口 (如果这是可能的,程序员有福了, :D)
#. code on demand(可选, 其实是一种扩展性的要求) 

看了这几个特征后,你想起了什么?

你可能会破口而出: **HTTP**. 

我答: **You got it!**

HTTP是WWW的最核心的协议, 它将简单的分布于世界各个角落的资源都统一起来, 统一的地址, 
简单的方法, 和一定数量的表达方式.(你可能对这三点描述很模糊,请go ahead).

`REST`_ 的三个要素是 **唯一的资源标识**, **简单的方法** (此处的方法是个抽象的概念), **一定的表达方式**.

看下图:

.. image:: http://farm3.static.flickr.com/2707/4109518844_c77091c2c7.jpg

图一. REST的三角架构(摘自 `Restful User Experience`_ )

`REST`_ 是以 **资源** 为中心, 名词即资源的地址, 动词即施加于名词上的一些有限操作,
表达是对各种资源形态的抽象.

以HTTP为例, 名词即为URI(统一资源标识), 动词包括POST, GET, PUT, DELETE等(还有其它不常用的2个,所以
整个动词集合是有限的), 资源的形态(如text, html, image, pdf等)


RPC与REST的区别
===================

如果你想只记住一点,那么就请记住 **RPC是以动词为中心的, REST是以名词为中心的**, 此处的
动词指的是一些方法, 名词是指资源.

你会发现,以动词为中心,意味着,当你要需要加入新功能时,你必须要添加更多的动词, 这时候服务器端需要实现
相应的动词(方法), 客户端需要知道这个新的动词并进行调用.

而以名词为中心, 假使我请求的是 hostname/friends/, 无论这个URI对应的服务怎么变化,客户端是无需
关注和更新的,而这种变化对客户端也是透明的.

至于其它的区别,如对实现语言的依赖, 耦合性等,这些都是上面提到的这个根本区别所衍生的.

让我们回到引入部分的2个问题. 当你每天使用HTTP冲浪时,你都在使用 `REST`_ 与远程的服务器进行亲密接触.
当你使用Gtalk和同事朋友沟通时,你则是在享受着 `RPC`_ 的便利.

推荐阅读 `Restful User Experience`_ (这个slide是个人认为解释的最好的) 还有 `ReST vs SOA(P)`_.

如何选择?
==============

通常如果我们是客户端,我们基本上是没有选择的权利的, 服务提供商通常只有一种架构的服务.例如facebook, 人人
网开放的API(使用的是 `REST`_ ).

但是倘若我们有幸设计和实现自己的 `Web Service`_ 我们该如何选择呢?

根据笔者自己的经验和心得, 建议 **能够使用REST就尽量使用REST**, 主要基于下面几个考虑:

#. 扩展性
#. 松耦合(意味着,不用强制要求客户端去更新相应的代码)
#. 客户端实现语言无关
#. 性能
#. 安全性(例如HTTPS)

当然上述的几点也并非 `RPC`_ 都不满足,不过相对而言, `REST`_ 更加清晰和简洁, 再辅以 `JSON`_
相应的服务会在性能和稳定性(简单通常意味着robust)方面有很大的提高.


一个自己的项目例子
==================

我们公司正在做一个social game的项目, 我负责整个系统的后端架构和通信等, 所以仔细地学习和研究了
facebook/人人网开放的API, 由于facebook(人人网完全拷贝facebook)使用的是 `REST`_ 的架构,
所以即使facebook本身是PHP开发的,这也不妨碍我们使用python来开发, 还有更多的PHP, Java, .net, 
Perl等客户端API封装. (当然人人网是使用Java开发的,我们也使用python).

于是在想,倘若facebook的架构使用的不是 `REST`_ ,会有这样的灵活性吗? 如果使用的是 `RPC`_ 可能
目前我们的日子不会好过, 甚至我们的项目都不可能立项!

另外,因为我们的前端使用的是flash, 与后端的python通信采用的是 `djangoamf`_ , 有意思的是, 如果你了解
flash,你会知道AMF是一种二进制的flash数据交互协议, 而 **它是基于RPC** ! 当然这正如我上面说的,
某些架构不是我们能够选择的, 所以使用 `RPC`_ 的结果是如果我们想开放我们游戏的API(假如我们的游戏足够火,
有朋友想基于我们的游戏开发周边应用),这就变得很艰难了.但是目前来看,我们开放API的可能性不大.


结论
========================================

无论是基于 **动词**, **名词** 或者 **消息**, 这些都是为我们提供一个稳定,可靠,安全,易扩展的服务为目的的,
所以,如果你有机会为别的客户端提供开放API(如果你们公司是另一个facebook, twitter),你不妨多考虑下基于
你的平台的开发者们, 别让他们的日子不好过啊(同是程序员,相煎何太急?呵呵).

欢迎交流.


参考资料
========================================

#. `Web Service`_
#. `SOA`_
#. `REST`_
#. `RPC`_
#. `Cloud Computing`_
#. `框计算`_
#. `ReST vs SOA(P)`_
#. `Restful User Experience`_

本文的rst源码
========================================

本文的源码链接在 `这里`_ .

点击 `下载pdf阅读`_.




.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里: http://groups.google.com/group/python-share/web/REST_vs_RPC.rst
.. _RPC: http://en.wikipedia.org/wiki/Remote_procedure_call
.. _Cloud Computing: http://en.wikipedia.org/wiki/Cloud_computing
.. _框计算: http://boxcomputing.baidu.com/
.. _SOA: http://en.wikipedia.org/wiki/Service-oriented_architecture
.. _REST: http://en.wikipedia.org/wiki/Representational_State_Transfer
.. _Web Service: http://en.wikipedia.org/wiki/Web_Service
.. _ReST vs SOA(P): http://www.slideshare.net/ozten/rest-vs-soap-yawn
.. _Restful User Experience: http://www.slideshare.net/trilancer/restful-user-experience-1421793
.. _djangoamf: http://djangoamf.sourceforge.jp/index.php?DjangoAMF_en
.. _JSON: http://en.wikipedia.org/wiki/Json
.. _XML-RPC: http://en.wikipedia.org/wiki/Xml-rpc
.. _JSON-RPC: http://en.wikipedia.org/wiki/JSON-RPC
.. _SOAP: http://en.wikipedia.org/wiki/SOAP
.. _下载pdf阅读: http://groups.google.com/group/python-share/web/REST%20vs%20RPC.pdf
