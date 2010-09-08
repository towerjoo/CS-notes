.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-10-27 16:34

========================================
django拾遗之signal
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).


摘要
========================================

突然发现自己比较喜欢写系列类型的文章, 因为通常类似的一些文章都具有相同的特征,但
一篇很难完全覆盖,所以往往写系列的文章比较合适.

**拾遗** 系列的文章主要是一些 **常被程序员忽略**, 但 **又特别有意义** 的一些内容.

所以, 从本文起, 我会开始不定期地更新一些类似的文章. 作为自己学习的总结也和朋友们一起分享.


.. contents::





引入
========================================

在web开发中, 你可能会遇到下面这种场景:


::

    在用户完成某个操作后, 自动去执行一些后续的操作. 譬如用户完成修改密码后,
    你要发送一份确认邮件.

当然你可以把逻辑写在一起, 但是有个问题是, 通常前置动作(触发操作)会不止一种(如用户更改了其它信息的确认邮件),
这时候这个逻辑会需要写多次, 所以你可能会想着DRY, 于是你把它写到了一个函数中,每次调用. 当然这是没问题的.

但是, 如果你换个思路你会发现另一个完全不同的方案, 即:

#. 类似于daemon的程序监听着特定的事件
#. 前置操作来触发相应的事件
#. 监听程序执行对应的操作

这样的好处是什么呢?

#. 松耦合(不用把后续操作写在主逻辑中)
#. 便于复用(这也是为什么 `django`_ 本身, 及第三方应用如 `pinax`_ 大量使用此技术的原因)

在各种高级语言中都会有类似的特性,如java, javascript等.而在 `django`_ 中我们使用 **signal**.

本文会着重介绍 `django`_ 的 *signal* 相关知识.


django的signal定义
========================================

什么是signal?

`django`_ 包含一个称为 *signal dispatcher*, 用来解耦合框架中发生的事件与 
**得到通知的应用** 之间的逻辑. 简单地说, 在特定事件发生时,  使用signal **发送者** 
能够通知一系列 **接收者** (一个或者多个).

`python`_ 本身没有类似机制的支持, 但是 `django`_ 基于 `PyDispatcher`_ 进行了性能
和代码结构上的优化来增加了signal功能.


如何使用django的signal
=======================

在使用signal之前,我们先了解下django signal的处理流程.

参考下图:

.. image:: http://farm3.static.flickr.com/2468/4048888885_23bf82c838_o.png

那么我们来逐步完成我们简单的signal.

场景
-----
我们有2个页面 ,一个是文章显示页面,一个是文章增加页面, 文章只有title,content及is_public三个域.

我们使用signal是完成,当用户添加一个文章后,我们置其is_public=False, 我们使用signal来实现此功能.

注册signal
--------------
下面是测试用的project的文件结构,具体可以 `下载源代码`_ 来在本地运行.

::

    .
    |-- __init__.py
    |-- __init__.pyc
    |-- logs
    |   `-- filelog.log
    |-- manage.py
    |-- settings.py
    |-- settings.pyc
    |-- signal.db
    |-- testsignal
    |   |-- __init__.py
    |   |-- __init__.pyc
    |   |-- models.py
    |   |-- models.pyc
    |   |-- signals.py
    |   |-- signals.pyc
    |   |-- templates
    |   |   |-- add.html
    |   |   |-- base.html
    |   |   `-- index.html
    |   |-- tests.py
    |   |-- urls.py
    |   |-- urls.pyc
    |   |-- views.py
    |   `-- views.pyc
    |-- urls.py
    `-- urls.pyc

testsignal是我们建立的示例app, 我们首先要注册signal,
具体代码如下(testsignal/signals.py):


.. sourcecode:: python


    import django.dispatch
    delete_done = django.dispatch.Signal(providing_args=['obj'])


引入django的包, 并且注册 delete_done为我们将要使用的signal.

关联signal对应的listener
---------------------------

然后我们关联对应的listener, 代码如下: (testsignal/models.py)

.. sourcecode:: python

    from django.db.models.signals import pre_save
    from django.db import models
    import logging
    import signals

    # Create your models here.


    class Article(models.Model):
        title = models.CharField(max_length=200)
        content = models.TextField()
        is_public = models.BooleanField(default=True, blank=True)

        def delete(self):
            #self.is_public = False
            signals.delete_done.send(sender=Article, obj=self)

        def __unicode__(self):
            return self.title


    def zhutao(sender, kwargs):
        logging.debug(kwargs)
        if "obj" in kwargs:
            obj = kwargs.get("obj")
            logging.debug(obj.is_public)
            obj.is_public = False
            obj.save()
            logging.debug("signal recieved! zhutao is called.")
            logging.debug(obj.is_public)

    signals.delete_done.connect(zhutao, sender=Article)


我们来看最后一行, `signals.delete_done.connect(zhutao, sender=Article)`, 即将
我们上面注册的 `delete_done` 和 监听函数 `zhutao` 关联了起来, 而
这里的 sender=Article, 则是用来限制只有当Article有更新时我们才会触发这个事件.

触发监听事件
------------

最后,我们要在特定操作发生时触发相应的监听函数, 具体代码如下(testsignal/views.py):

.. sourcecode:: python

    from django.http import HttpResponse,HttpResponseRedirect
    from django.core.urlresolvers import reverse
    from django.shortcuts import render_to_response

    import signals

    from models import *


    def index(request):
       articles = Article.objects.all().order_by("-id")
       return render_to_response("index.html", {"articles":articles})

    def add(request):
        if request.method == "POST":
            title = request.POST.get("title", "")
            content = request.POST.get("content", "")
            if title and content:
                article = Article(title=title, content=content)
                article.save()
                article.delete()
                return HttpResponseRedirect(reverse(index))
        return render_to_response("add.html", {})


其它的只是django的普通views.py中的方法,我们主要来看 `article.delete()` 这行代码,
执行这个后,我们会调用models.py中的delete方法,见上面的models.py中的代码,
它会执行下面一行代码:

`signals.delete_done.send(sender=Article, obj=self)`

面这行代码正是向delete_done发送了事件的触发,此时,对应的监听函数 `zhutao` 会得到执行,

从而将 is_public 置为False.

我们的任务也得以完成.

具体的说明可以 `下载源代码`_ 来运行,你会在logs/filelog.log文件中看到对应的log输出.

示例输出为:


::

    2009-10-27 03:28:27,202 DEBUG models.zhutao Line:26 {'signal': <django.dispatch.dispatcher.Signal object at 0x9523e4c>, 'obj': <Article: aaa>}
    2009-10-27 03:28:27,203 DEBUG models.zhutao Line:29 True
    2009-10-27 03:28:27,209 DEBUG models.zhutao Line:32 signal recieved! zhutao is called.
    2009-10-27 03:28:27,209 DEBUG models.zhutao Line:33 False


一些其它的应用
==================

我们上面提到过 `django`_, `pinax`_ 也大量地使用了signal技术,那我们下面简要看看, `django`_ 中有哪些具体的应用.

在 `django`_ 中, 主要有下面几类:

#. Model signals

    * pre_init
    * post_init
    * pre_save
    * post_save
    * pre_delete
    * post_delete
    * class_prepared

#. Management signals

    * post_syncdb
    
#. Request/response signals

    * request_started
    * request_finished
    * got_request_exception

#. Test signals

    * template_rendered

这些都是 `django`_ 内置的signals来方便用户来进行一些特定的操作,具体的介绍可以参考:
`built-in signals <http://docs.djangoproject.com/en/dev/ref/signals/#ref-signals>`_.

至于 `pinax`_ 可以下载其源代码来具体查看.

可能的应用场景
================

那么signals有哪些可能的应用场景呢?我们能够在什么样的场景下使用呢?

从定义来看,其实已经很明确了,  **如果一个操作可能会触发多个后续事件, 此时使用signals会非常方便**.

那么具体的应用可以考虑:

#. sns中的事件通知, 如用户发表了一篇博文, 然后通知所有的好友
#. 用户信息的更改的邮件通知
#. 用户订制信息的邮件通知等


结论
========================================

`django`_ 的signals是非常强大的, 如果我们能够很好地使用,则能够大大地提高代码的可维护性, 
复用性,以及减少耦合等.


参考资料
========================================

#. `django`_
#. `pinax`_
#. `Django signals`_

本文的rst源码
========================================

本文的源码链接在 `这里`_ .

你也可以在 `下载源代码`_ (程序). 

你也可以选择 `下载pdf`_ 来阅读.



.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _django: http://djangoproject.com
.. _PyDispatcher: http://pydispatcher.sourceforge.net/
.. _Django signals: http://www.mercurytide.co.uk/news/article/django-signals/
.. _pinax: http://pinaxproject.com/
.. _下载源代码: http://groups.google.com/group/python-share/web/mysignal.zip
.. _python: http://python.org
.. _这里: http://groups.google.com/group/python-share/web/django-signal.rst
.. _下载pdf: http://groups.google.com/group/python-share/web/django%E6%8B%BE%E9%81%97%E4%B9%8Bsignal.pdf
