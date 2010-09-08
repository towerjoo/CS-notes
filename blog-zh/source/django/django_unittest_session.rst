..  coding: utf-8
.. 1 tab = 4 spaces

.. 文件名: django_unittest_session.rst
.. 作者: Tower Joo<zhutao.iscas@gmail.com>
.. 日期: 2010-01-15 17:11:17
.. 说明: 

=============================
关于Django的单元测试之session
=============================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)


摘要
========================================

.. contents::

本文主要介绍如何在django的单元测试中模拟,更改session来完成测试的目的.


引入
=========

不知道读者是否写 `单元测试`_, 是否使用 `django`_ ,但是作为 `敏捷开发`_ 重要方法的 `测试驱动开发`_ (TDD)最为强调测试,
甚至极端到先测试后程序的地步, 我个人不是TDD的热烈粉丝,我只是做出一种适合自己的开发模式--关键逻辑的单元测试.

回到 `django`_ 可能会有人说 `django`_ 已经有了 `完整的测试框架`_, 有doctest和unittest两种模型的测试, 这倒是不假, 不过,
测试不仅局限于业务逻辑的测试(读写数据库),还包括应用逻辑的测试(模拟浏览器请求等),而且往往后者更加重要和复杂,
还好 `django`_ 有相应的封装和基础构件,所以处理起来也还是比较方便的.

我们很愉快地使用着 `django`_ 的测试框架,直到一天,我们开始不再使用 `django`_ 内置的用户验证系统,而是使用session来维持一个
用户的登录状态,这便涉及到了本文的论题,即:

**如何在单元测试中测试,修改django的session?**

说明,

#. 如果文中没有特别说明,所有的session都是采用存储在数据库中的方式.
#. 存储于用户本地浏览器中的cookie的key不一定是"sessionid",取决于用户在settings.py中的设置, 但是这个值是默认的

简单示例
=============

有如下的一段代码:

.. sourcecode:: python

    def setUp(self):
        self.client = Client()
        # 请求首页后，会建立相应的user和session, 此处只是为了enable session
        self.client.get(reverse("game_main"))   #假设得到的session为  self.client.session['player'] = "demo1"
        self.client.session['player'] = "demo2" #试图更新session
        self.assertEquals(self.client.session.get("player", "demo2")    #在单元测试执行时会出错
        self.player = self.client.session.get('player', None)


如上的代码中,试图使用 `self.client.session['player'] = some_player` 来修改session的值,但是在运行单元测试时会出错.

第一次尝试失败!

第二次,我们试图为session重新赋值后,再存储下, 即添加一行 `self.client.session.save()`,很可惜,依旧失败!

于是只好hack源码了, 我尝试跟踪了相关的单元测试的源码,终于通过下面的方法解决了:

.. sourcecode:: python

    def _set_player_session(self, player=None):
        """
        hack the session code to change it to the right one
        """
        from django.contrib.sessions.models import Session
        from django.contrib.sessions.backends.db import SessionStore
        session = Session.objects.get(pk=self.client.cookies['sessionid'].value)
        newsession = {"player" : player }
        session.session_data = SessionStore().encode(newsession)
        session.save()

在上面的hack中,其实就是我们显式地去取出session,更改,再存储,所有的操作都是低层的修改.

注意上面的hack假设你将session设置为存储在db中,存储于内存,文件等其它方式类似.

相关的知识
================

为了更好地理解整个操作,我们来研究下 `django`_ 的相关机制.

django的session
===================

请参考 `django session`_ 部分.

重要点总结如下:

#. session可以存储在数据库,内存,文件中
#. 对于来自一个请求的用户,只使用一个session记录(准确地说,就是来自同一个浏览器,因为在浏览器中记录有sessionid),而session的值是一个序列化的字典
#. 需要浏览器cookie的支持

我们来看看,假如我在一个request的view中设置了如下2个session:

::

    request.session['user'] = "zhutao"
    request.session['last_login_time'] = "256525850"

那么,当一个用户请求这个view时,django会为其浏览器存储一个名字为"sessionid"的字符串,如: **b2db4c1a01286c0b175dfad873b57b37**.

这个sessionid同时也存储在数据库中作为session_key,来索引某个浏览器的session.而在数据库中, django会把session的值以字典的形式的序列化
方式存储于数据库中,简单的可理解为:

::

    session_data = 序列化({"user" : "zhutao", "last_login_time" : "256525850"})

例如可能得到这样一个序列化后的字符串:

::


    gAJ9cQEoVQR0ZXN0cQJVBnpodXRhb3EDVQZwbGF5ZXJxBGNhcHBzLm1lbWJlci5tb2RlbHMKTWVt\nYmVyCnEFKVJxBn1xByhVDGNoYXJhY3Rlcl9pZHEISwFVDmNoYXJhY3Rlcl90eXBlcQlYAQAAAEhV\nEm1pc3Npb25zX2NvbXBsZXRlZHEKS/dVCGNvb2xuZXNzcQtLYVULbWF4X3N0YW1pbmFxDEt4VQh0\nZWFtc2l6ZXENS+JVCG51bV9raWxscQ5NoQFVCm1heF9oZWFsdGhxD0t4VQJpZHEQSwJVB3N0YW1p\nbmFxEUvGVQpudW1fa2lsbGVkcRJLm1UGaGVhbHRocRNN4QFVA3dpbnEUS29VB2ltZ191cmxxFVgA\nAAAAVQptYXhfc3Bpcml0cRZLHlUQY3VycmVudF9wYXJ0eV9pZHEXSwBVBnNuc19pZHEYSwJVBnNw\naXJpdHEZS0pVBGxvc3NxGkt8VQRuYW1lcRtYBQAAAGRlbW8ycRxVBWxldmVscR1LAVUGZ2VuZGVy\ncR5YAQAAAE1VBGNhc2hxH006AVUKZXhwZXJpZW5jZXEgS6hVEWN1cnJlbnRfY2hhcmFjdGVycSFL\nAVUMZGF0ZV9jcmVhdGVkcSJjZGF0ZXRpbWUKZGF0ZXRpbWUKcSNVCgfZCxwDIS4AAACFUnEkVQdo\nb3RuZXNzcSVN3QF1YnUuNjI5YjVmYzc1MTFkNzJkMmE2NDVlNjg4ODg2MjQ5MjQ=\n


然后,当你去获取相应的session的值时, django会:

#. 从你的cookie中取出名为sessionid的cookie值
#. 将取到的cookie值来作为key来查询相应的数据库记录,即session_data
#. django对取到的session_data进行反序列化,得到了相应的字典
#. 此时用户可以很简单地获得相应的值

几个细节:

**关于session的序列化**

.. sourcecode:: python

    pickled = pickle.dumps(session_dict) #使用pickle来序列化session的字典
    pickled_md5 = md5.new(pickled + settings.SECRET_KEY).hexdigest()    #使用md5进行加密,注意key是pickle过的字符串和settings.SECRET_KEY,后者通常只有你知道



**关于session的反序列化**

知道SECRET_KEY后会很容易得到相应的反序列化的原始字典,所以 **settings.SECRET_KEY** 是非常重要的.

**关于sessionid的生成**

.. sourcecode:: python

    def _get_new_session_key(self):

          "Returns session key that isn't being used."
          # The random module is seeded when this Apache child is created.
          # Use settings.SECRET_KEY as added salt.
          try:
              pid = os.getpid()
          except AttributeError:
              # No getpid() in Jython, for example
              pid = 1
          while 1:
              session_key = md5.new("%s%s%s%s" % (random.randint(0, sys.maxint - 1),
                                    pid, time.time(), settings.SECRET_KEY)).hexdigest()
              if not self.exists(session_key):
                  break
          return session_key

这是位于 `django.contrib.sessions.backend.base.py` 中的代码,能够看到, 生成的sessionid是table唯一的,且使用md5加密的.

**关于session的失效**

在session的数据库中,只有4个字段即: *id*, *session_key*, *session_data*, *expire_date*, 而且在向用户的浏览器
写入cookie时,同样会设置相应的 *expire_date*, 那么在查找相应的session时:

#. 如果客户端没有了sessionid的cookie, 则说明session已经失效(失效后的动作,如引导到登录页面等)
#. 如果客户端没有失效, 而数据库中的expire_date已经到期,则同样说明session失效(防止恶意修改cookie)
#. 甚至你可以手动地去删除某个session,从而导致session失效




单元测试中的session
======================

在 `django`_ 的测试组件中有TestClient来作为测试的基础类,其中提供Client.session来模板运行时的session,但是二者又不完全相同,
主要差别有:

#. TestClient不是与request.session对等的
#. TestClient中的session并不能自动完成相应的session的DB存储, 所以需要像上面的示例中的手动存储

所以要在单元测试中操作session,需要:

#. 得到当前的sessionid(从cookie中得到)
#. 查相应的session表,取得相应的对象,修改后,重新存储


结论
===============

`django`_ 的单元测试并不完善,特别是session,需要额外的工作来完成相关的工作, 另外, 从session的工作原理来看,
`django`_ 的session安全性主要取决于session_dict和SECRET_KEY两个,所以要特别注意自己的SECRET_KEY.


后记
==============

其实我个人比较希望单元测试的session和view中的session操作能够完全相同,如:

.. sourcecode:: python

    self.client.session['player'] = "demo1"  #创建
    del self.client.session['player']   # 删除
    self.client.session['player'] = "demo2"  #更新


后续我会向 `django`_ 提出一个ticket(其实已经有了), 并且提供相应的patch.

参考资料
========================================

#. `session`_
#. `django`_
#. `Cookieless Django Sessions and authentication without cookies`_


本文的源码
========================================

本文的rst源码链接在 `这里`_ .

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)


.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里: http://cn.drop.io/download/4b505797/44fc2405ce8d4781761479717331f16226c670b5/94d68560-e3f9-012c-720c-ffe5f39c2f49/1c294c10-e3fa-012c-47b6-f85af4b26eb3/v2/original_content
.. _下载pdf阅读: http://cn.drop.io/download/4b505764/3f2ef96636f6037995ae5d23d1c231ead58770af/94d68560-e3f9-012c-720c-ffe5f39c2f49/97c42820-e3f9-012c-a999-f4d9d7fd044b/v2/original_content
.. _单元测试: http://en.wikipedia.org/wiki/Unit_testing
.. _django: http://djangoproject.com
.. _敏捷开发: http://en.wikipedia.org/wiki/Agile_software_development
.. _测试驱动开发: http://en.wikipedia.org/wiki/Test-driven_development
.. _Cookieless Django Sessions and authentication without cookies: http://www.stereoplex.com/2007/nov/7/cookieless-django-sessions-and-authentication-with/
.. _session: http://en.wikipedia.org/wiki/Session_(computer_science)#HTTP_session_token
.. _django session: http://docs.djangoproject.com/en/dev/topics/http/sessions/
.. _完整的测试框架: http://docs.djangoproject.com/en/dev/topics/testing/
