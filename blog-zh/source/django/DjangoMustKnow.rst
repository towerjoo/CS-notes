.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-08-15 02:37

========================================
Django开发必知必会
========================================

版权说明
==================

由于最近发现很多转载笔者的文章而没有说明作者和出处,所以特别在些声明.

本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 **朱涛**, **出处** ，并且 **非商业** .



摘要
========================================

`Django`_ 作为 `python`_ 社区中最流利的web框架,它所强调的就是 **快速开发**, **复用**, **可读**.
本文主要介绍使用 `Django`_ 来开发所需要了解的知识,其中也包含了一些指导性的原则以及笔者的一些经验之谈.


.. contents::





基本知识
========================================

熟悉python和django
---------------------

`Django`_ 是基于 `python`_ 的,所以在开发前需要熟悉相关的技术.

`python`_ 推荐几本比较好的书,包括:

#. `learning python`_
#. `python cookbook`_

熟读 `Django`_ 的  `官方文档`_ 和相关的书籍，这些都是必须。比较好的书籍有：

#. `Django Book`_
#. `Pro Django`_
#. `Practical Django Projects`_

更多参考 `django相关资源`_.

其它的相关技术
-------------------

作为web开发的程序员,还需要了解其它的相关技术,包括:

* `html`_
* `css`_
* `javascript`_ ( `jquery`_ 等)
* `ajax`_
* 网络知识和标准,如 `http`_ 协议, TCP/IP网络架构等.


可用的资源
===============

掌握了上面提到的基本知识外,我们对 `python`_, `Django`_ 及web开发的相关技术有了一定的熟悉,也对 `python`_ 和 `Django`_ 的
哲学也有一定的了解,如 *Don't Repeat Yourself*, *Keep It Simple, Stupid*, *Don't Reinvent Wheels* 等.

所以,在开始一个项目之前我们需要了解已有哪些可用的资源.

而在可用的资源中,最需要跟踪的一个项目就是 `pinax`_ ，它提供了站点所必须的一些常用功能，而
所采用的方式便是提供一些 **可复用的app**, 使得我们很容易集成到我们的环境中，
或者基于 `pinax`_ 二次开发。

除此之外，还需要了解一些特定领域的相关资源，如：

* 商店 `satchmo`_
* 地理 `GeoDjango`_
* OpenId `django-openid`_
* 等等

在获得特定领域的相关资源后，会大大地提高开发的效率，从而降低成本。

高级知识
========================================

掌握上面提到的技术,这时就基本上是一个合格的 `Django`_ 程序员了,但是除此之外,还需要了解一些高级的知识.

使用virtualenv+pip来构建独立的开发环境
--------------------------------------

`virtualenv`_ 用于建立一个独立的（与其它module)的虚拟环境，从而使得不同的虚拟环境下的
程序可以依赖于不同版本的module,例如某个django project是基于0.96的，而另外的project是基于
1.1的，所以就必须有不同的虚拟环境。
了解更多参考： `pip and virtualenv`_ 

使用 `pip`_ 来 **复制** 已有的依赖。 `pip`_ 是用来取代 `easy_install`_ 的，除此而外，
我们还可以很方便地使用 `pip`_ 来 **复制** 我们当前的工作环境。例如，我们建立一个 *requirements.txt* 文件
来记录我们当前工作环境中的相关依赖程序，然后输入 `pip install -r /path/to/requirements.txt`, 那么相应的
依赖软件会自动安装。前提是你的系统已经安装了 `pip`_.

除此而外，当你需要部署一个django项目时，可以使用 `wsgi`_ 很方便地进行部署，具体参考 `virtualenv and wsgi <http://code.google.com/p/modwsgi/wiki/VirtualEnvironments>`_.

使用fabric进行部署
----------------------

参考 `Deploying Python Web Applications <http://lucumr.pocoo.org/2008/7/17/deploying-python-web-applications>`_


另外,我们还可以使用 `python`_ 的强大功能,来实现例如配置文件的路径自适应, 利用调试状态来设定特定的属性等.


推荐的开发流程
========================================


可使用下面的开发流程来进行 `Django`_ 的开发(假设是从新开始一个项目的)：

#. 使用 `virtualenv`_ 建立相应的独立环境
#. 使用 `easy_install`_ 和 `pip`_ 安装相应的依赖模块
#. 多人开发时可将当前的所有模块 **复制** 给同事( `pip` 有 *feeze* 命令来输出当前环境下的所有依赖模块及版本,以保证所有的开发人员使用相同的代码库)
#. 为服务器也建立相应的独立环境,并使用 `fabric`_ 进行自动化部署.
#. 最后,使用 `wsgi`_ 和web服务器来发布产品

结论
========================================

利用 `Django`_ 的 **复用**, **快速开发** 等特性来进行Web开发, 其实是有一定的规律可循的,
除了上面介绍的一些开发知识(技巧)外,如果在开发中你发现某个过程很繁琐,你这时候就要考虑去调研
是否已经存在相关的解决方案.而不要一味地,耗时地去完成.


参考资料
========================================

#. `Notes on using pip and virtualenv with Django <http://www.saltycrane.com/blog/2009/05/notes-using-pip-and-virtualenv-django/>`_ 
#. `啄木鸟社区 <http://wiki.woodpecker.org.cn/moin/首页>`_ 
#. `django相关资源`_

.. _pip and virtualenv: http://mathematism.com/2009/jul/30/presentation-pip-and-virtualenv/
.. _Django Book: http://www.djangobook.com/en/2.0/
.. _Pro Django: http://www.amazon.com/Pro-Django-Experts-Voice-Development/product-reviews/1430210478/ref=dp_top_cm_cr_acr_txt?ie=UTF8&showViewpoints=1
.. _Practical Django Projects: http://www.amazon.com/Practical-Django-Projects-Pratical/product-reviews/1590599969/ref=dp_top_cm_cr_acr_txt?ie=UTF8&showViewpoints=1
.. _Django: http://www.djangoproject.com
.. _satchmo: http://www.satchmoproject.com
.. _GeoDjango: http://code.djangoproject.com/wiki/GeoDjango
.. _django-openid: http://code.google.com/p/django-openid/
.. _virtualenv: http://pypi.python.org/pypi/virtualenv
.. _pip: http://pypi.python.org/pypi/pip/0.4
.. _easy_install: http://pypi.python.org/pypi/setuptools
.. _官方文档: http://docs.djangoproject.com/en/dev/
.. _pinax: http://www.pinaxproject.com
.. _wsgi: http://en.wikipedia.org/wiki/Web_Server_Gateway_Interface
.. _python: http://www.python.org
.. _learning python: http://www.amazon.com/Learning-Python-Animal-Guide-Mark/dp/0596158068/ref=sr_1_1?ie=UTF8&qid=1250496322&sr=8-1
.. _python cookbook: http://www.amazon.com/Python-Cookbook-Alex-Martelli/product-reviews/0596007973/ref=sr_1_3_cm_cr_acr_img?ie=UTF8&showViewpoints=1
.. _django相关资源: http://vik.haoluobo.com/trac/wiki/Django
.. _fabric: http://www.nongnu.org/fab/
.. _html: http://en.wikipedia.org/wiki/HTML
.. _css: http://en.wikipedia.org/wiki/Cascading_Style_Sheets
.. _javascript: http://en.wikipedia.org/wiki/JavaScript
.. _jquery: http://jquery.com/
.. _ajax: http://en.wikipedia.org/wiki/Ajax_(programming)
.. _http: http://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol
