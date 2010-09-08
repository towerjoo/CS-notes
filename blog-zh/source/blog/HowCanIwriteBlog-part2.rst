.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-07-15 14:42

============================
我是如何写博客的-续(图片版)
============================

摘要
=====

几天前的一篇 `博客`_ 讨论了我是如何写博客的, 以及这样的写的好处,也有好多的朋友回复了自己的看法,
其中一个朋友希望看到有图片例证的过程,所以本篇博客将会按照上篇 `博客`_ 的思路以图片的形式来说明
写博客的整个过程,以及可能用到的一些脚本, 期待和大家共同讨论.



内容如下:

.. contents::

使用VIM来写博客源文档
============================================

作为程序员的一个好处就是可以避免一些恼人的重复,所以我在写博客的过程中会
尽量避免一些重复性工作.

由于我的博客通常有固定的框架,如摘要,正文,参考资料等,所以这部分可以使用脚本来完美地实现.

第一步,使用脚本生成博客的框架

在命令行中输入: `python makeheader.py HowCanIwriteBlog-part3`

这里便得到了整个文章的框架,如下:

.. image:: http://lh3.ggpht.com/_D8Zuh7hxOYQ/Sl2JiSIAkwI/AAAAAAAAB3U/lirJluDv-UA/s800/skeleton.png


使用SVN将新博客内容更新到google code服务器上
=================================================

`云计算`_ 带来的好处就是, 我们无论身处何处,我们所宝贵的数据资源总是位于云上, 而不用去更多考虑安全问题.

同样带来的数据同步等功能也是很可观的.

所以下面我们使用SVN将数据checkin到 `google code`_ 上(假设你已经有了相关的账号和repository, 没有可以很容易地得到), 
使用如下的svn命令即可:

`svn ci` 

接着输入相关的Log即可.

那么我们数据便 **安全** (我们认为google的服务是安全的,但为了防止意外,尽量在不同的机器上保持一份workcopy)地位于了 **云** 上.

任何时候我们需要修改之前的博客文章时,只需要回滚到相应的版本即可,而 **纯文本** 的 `restructuredText`_ 也让我们修改起来更加便利,
而无需考虑恼人的格式问题.

此方案的评价
=============

好处主要有:

#. 跨平台,只需要几个简单的软件 (`subversion`_ , `restructuredText`_) 和相关的服务( `google code`_. BSP)
#. 纯文本, 这是相当重要的, 使得你可以使用任意平台下的文本工具来处理
#. 云服务, 这便于异地同步和共享
#. 版本控制, 易于回滚,易于更新等, 易于协作
#. 无格式编辑的问题, 常用的格式在 `restructuredText`_ 已有原生的支持,对于程序员的博客而言,内容大于格式,所以只需对常用的如加粗,链接,标题等格式的支持即可,
   而这些在 `restructuredText`_ 中支持的很好.

不足也是明显的,主要有:

#. 上传至BSP(Blog Service Provider)时的有限支持,如图片,和附加文件(可以先上传到picasa,google site等地方存储即可解决)等
#. 与既有的格式的不相符,总体而言对于rich editor这样的编辑器,通常格式都能得到较好支持,所以更改的也不会太多.

本文相关的文件
===============

点击 `这里 <http://sites.google.com/site/towerjoo/download/HowCanIwriteBlog-part2.rst?attredirects=0>`_ 下载本文的 `restructuredText`_ 源文件.

点击 `此处 <http://sites.google.com/site/towerjoo/download/makeheader.py?attredirects=0>`_ 下载本文中使用到的生成不到博客框架的脚本.


参考资料
==============================
#. `VIM`_
#. `subversion`_
#. `google code`_
#. `restructuredText`_
#. `python`_
#. `reportlab`_
#. `docbook`_
#. `云计算`_
#. `我是如何写博客的-cnblogs`__

.. _VIM: http://vim.org
.. _google code: http://www.googlecode.com
.. _restructuredText: http://docutils.sourceforge.net/rst.html
.. _python: http://www.python.org
.. _reportlab: http://www.reportlab.com>
.. _docbook: http://www.docbook.org
.. _博客: http://www.cnblogs.com/mindsbook/archive/2009/07/09/how_do_i_write_blog.html
.. _云计算: http://en.wikipedia.org/wiki/Cloud_computing
.. _subversion: http://subversion.tigris.org/

__ 博客_
