.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-12-13 21:54

========================================
社交游戏框架讨论及其基于Django的方案介绍
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)

摘要
========================================

社交游戏是新出现的一种新型的基于浏览器的游戏形式, 通常具有简单, 易玩, 互动性高等特点.

本文主要简单介绍了下社交游戏的一些基本知识, 并且探讨了两种不同的架构方式,最后
简单谈了下基于 `Django`_ 的社交游戏框架的思路和实现.


.. contents::





引入
========================================

"今天你偷菜了吗?" 当这句话成为隔壁大妈每日的口头禅时, 你就能够设想出来这款游戏的火爆程度.

自从<<开心农场>>开始风靡中国的 `开心网`_ ,  `人人网`_ ,  `QQ`_ 时,  `五分钟`_ (开心农场的开发公司)也在 `facebook`_ 
上取得了一定的成就.

近期我也踏上了 `social game`_ 的这个行业, 并在游戏的架构方面做了一定的工作, 这篇博文会在大的层面
和大家探讨下 `social game`_ 游戏的架构设计(本文不会细节到出现商业机密泄露的程度, 请不要向我索取
游戏框架的源代码.)

背景介绍
=============

什么是社交游戏? 这是我们首要了解的问题. 我给出的定义是: 社交游戏是基于社交平台( `facebook`_ ,  `人人网`_ )
的相关资源(好友关系等)之上建立起的以用户互动为基础, 以购买道具或者植入广告为赢利模式的
网页游戏.

从全球的行业来看, 世界上的巨头有 `playfish`_, `zynga`_, 中国的开拓者有 `五分钟`_  等. 

社交游戏是最早出现在 `facebook`_ ,  `myspace`_ 这样的SNS网站上作为独立或者由网站自己开发的小型游戏(相比
于传统网游), 到今年 `五分钟`_ 成功地将开心农场做到极致, 社交游戏才为中国的网民所熟知.

如果你了解 `EA`_ 花了多少钱收购了 `playfish`_ , 也了解 `zynga`_ 和 `五分钟`_ 的季度收入, 你就会知道目前这个市场有
多大.不妨去google下吧.

与传统网游相比, 社交游戏有如下几个特点:

#. 用户互动性高
#. 用户归属感强(通常是自己圈子里的好友)
#. 用户沉溺的可能性较小(当然更多取决于个人)
#. 准入门槛较低(不需要太多的烧钱)
#. 平台分成很高(像 `facebook`_ ,  `myspace`_ ,  `人人网`_ 的分成会占到整个游戏收入的很大一部分)
#. 迭代开发周期短(更好地响应用户的需求)

了解了社交游戏的基本的知识,我们来看本文的重点: 社交游戏的架构.

社交游戏的架构
====================

因为社交游戏是内建于sns平台的一种应用,所以,它需要依赖于整个sns平台, 会调用sns平台的API,
整体架构如下:

.. image:: http://farm3.static.flickr.com/2500/4181865986_fa4eb0291c_o.jpg

上面架构图是基于 `facebook`_ 的, `人人网`_ 与 `facebook`_ 的架构完全相同(基本上是完全拷贝).

下面的讨论中会主要集中在上图Your Server这个模块的架构, 与sns平台的接口的通信可以参考特定
平台的相关文档.

另外社交游戏是一种网页游戏, 所以它具有网页游戏架构的所有特征.

通常社交游戏有两种技术方案, 一种是前端基于flash, 一种是前端基于javascript, 后端可以任意选择
技术方案, 如PHP, java,  `Python`_ 等.

从目前来看, 基于flash的架构方案因为其良好的用户UI和较好的用户响应在整个市场上占据更多的
份额,如<<开心农场>>等. 但是因为flash容易被破解, 所以通常很容易会被后续公司所克隆. 

下面我们主要分别介绍两种主流的架构方案, 以及以 `Python`_ / `Django`_ 作为后端的实现方案.

基于flash的架构方案
=====================

.. image:: http://farm3.static.flickr.com/2749/4181705394_746548aee4_o.png

此架构方案比较重要的一块是 `AMF`_ , 这是flash的一种通信协议(二进制), 主流的后端语言都对这种
协议有支持,如 `pyamf`_ (for  `Python`_ ), `AMFPHP`_ (for php)等等.

而 `AMF`_ 是一种RPC的调用, 后面提到的基于javascript的方案可以认为是REST的方式, RPC和REST的差别
可以参考 `Web Service实践之REST vs RPC`_.

这种方案需要重点强调的是关于flash通信加密的问题, 记得不久之前园子里有人写过开心农场的外挂. 所以
安全性是很重要的一块内容.

可以参考的文档有: 

#. `Flash应用安全规范`_
#. `How To Decompile Actionscript Code In Swf`_ (了解下如何被别人反编译也是预防基础)
#. `关于flash封装JS代码的一些TIPS`_



基于javascript的架构方案
==================================

.. image:: http://farm3.static.flickr.com/2518/4180942191_ed170cd55c_o.png

相比于基于flash的架构方案,这种方式最大的不同是前端与后端的通信使用的是ajax/json的方式, 
每次通信都是异步地使用ajax来调用后端的RESTful的URI, 并且使用json作为通信交互数据格式.

这里面需要注意的几个问题是:

#. 安全性(来自前端的请求都是需要在后端验证的)
#. 性能(优化ajax请求,对于静态的内容只请求一次)
#. lazy loading(尽量将请求后置, 只有当用户真正请求时才去load)


基于javascript的方案可以认为是REST的方式, RPC和REST的差别可以参考 `Web Service实践之REST vs RPC`_.

两种方案的比较
===================

用户体验方面
------------

目前我们的项目同时有两种方案的产品在研发之中, 相比而言, 对于一个新立项的项目, 我更倾向于使用flash, 因为
无论是从用户体验等各个方面,它都有更好的表现, 而且这种简单易操作的界面通常能够更加赢得用户的青睐.

但是通常第一次的load时间会比较久(或者可以称其为pre-load的一种思路).

技术层面
-------------
但是如果单就技术层面而言,我更加倾向于使用javascript的方式, 基于REST的架构在扩展性方面会有
更多优势.

人力资源
--------------

相比于javascript程序员, 一个优秀的flash程序员更加稀缺, 所以在开发团队方面
也会有一定的折中.


其它诸如部署, 开发成本核算等方面,也应该有更多的权衡.


关于Django的后台方案
========================================

最后我再谈谈,基于 `Django`_ 的后台解决方案.

目前, 我所知道的使用 `Django`_ 来作为后台解决方案的产品包括:  `人人网`_ 上的 `泡泡鱼`_ ,
 `五分钟`_ 的部分产品(参考他们的 `招聘帖`_)等.

使用 `Django`_ 作为后台的方案有如下的好处:

#. `Python`_ 本身的优秀
#. 敏捷开发(通常是将 `Django`_ 和RoR作为敏捷开发的典范框架)
#. 清晰的框架
#. 资源(社区,第三方插件等等)

基于 `Django`_ 简单地进行一些封装,使其更加适合社交游戏的开发, 如何封装, 就看个人的
经验和能力了. 祝好运!


结论
========================================

文中没有提到一些比较隐私的数据,当然这些数据你也能够从某些途径获取(如收入, 和平台的
分成比例等), 也没有谈具体的架构细节(我希望某一天可以开源和大家分享),
但是整体的架构思路应该还是很清楚的.

作为一个优秀的社交游戏产品,无论 **前期的游戏策划** , **中期的游戏开发**, 和 **后期的游戏推广** ,各个环节的
成功才能铸就一个成功的游戏.

当别人问你"今天你偷菜了吗?", 我则想问 "今天你了解social game吗?"

期待和朋友们交流.

后记
========================================

后面可能还会谈一些关于社交游戏安全性的一些内容, 所谓 **防人之心不可无, 害人之心不可有**, 
防范的工作还是要做好的.

参考资料
========================================

#. `Web Service实践之REST vs RPC`_
#. `pyamf`_
#. `Django`_
#. `Python`_
#. `insidesocialgames.com`_

本文的rst源码
========================================

本文的源码链接在 `这里`_ .

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)



.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里: http://groups.google.com/group/python-share/web/social_game_framework.rst
.. _AMF: http://en.wikipedia.org/wiki/Action_Message_Format
.. _pyamf: http://pyamf.org/
.. _AMFPHP: http://www.amfphp.org/
.. _Web Service实践之REST vs RPC: http://www.cnblogs.com/mindsbook/archive/2009/11/17/web_service_RESTvsRPC.htmlttp://www.cnblogs.com/mindsbook/archive/2009/11/17/web_service_RESTvsRPC.html
.. _Flash应用安全规范: http://huaidan.org/archives/3396.html
.. _How To Decompile Actionscript Code In Swf: http://huaidan.org/archives/3277.html
.. _关于flash封装JS代码的一些TIPS: http://huaidan.org/archives/3328.html
.. _泡泡鱼: http://apps.renren.com/paopaoyu/
.. _招聘帖: http://groups.google.com/group/ `Python`_ -cn/msg/b0fb84a46d914901
.. _下载pdf阅读: http://groups.google.com/group/python-share/web/social_game_arch_and_django_based_solution.pdf

.. _playfish: http://en.wikipedia.org/wiki/Playfish
.. _zynga: http://en.wikipedia.org/wiki/Zynga
.. _五分钟: http://www.fminutes.com/
.. _facebook: http://www.facebook.com/
.. _myspace: http://myspace.com
.. _人人网: http://www.renren.com
.. _QQ: http://www.qq.com
.. _Python: http://www.python.org
.. _Django: http://www.djangoproject.com
.. _开心网: http://www.kaixin001.com
.. _social game: http://www.socialtimes.com/2008/07/social-games/

.. _insidesocialgames.com: http://www.insidesocialgames.com/
.. _EA: http://en.wikipedia.org/wiki/Electronic_Arts
