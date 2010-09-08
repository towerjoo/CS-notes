========================
我是如何写博客的
========================

摘要
=====

本文主要介绍了如何使用 `restructuredText`_ (简称为reST)来写博客，
并且介绍了使用 `google code`_ 来管理博客源文件的方法。

内容如下:

.. contents::

使用restructuredText作为格式化文档的源文件
============================================

根据 *restructuredText* 网站的介绍， *restructuredText*  是一种 **所见即所得** 的 **纯文本** 标记语法。

*restructuredText* 是基于 `python`_ 写的，目前支持的目标格式转换工具也比较丰富，包括：

* rst2html  这个应该是最常用的
* rst2s5    生成基于浏览器的slide，效果还是不错的，不过有简单的非标准的 *restructuredText* 语法
* rst2latex  生成latex，再可生成pdf
* rst2pdf   生成pdf，这个需要 `reportlab`_ pdf库的支持,目前对中文支持不太好
* rst2man   这个是生成*nux下帮助文档的一种parser

其它的可能还包括：转换为 `docbook`_ 、转换为xml等。

目前的不足包括：

* 对中文的支持不好（主要是在生成pdf时，但是，
  已经有可参考的相关解决方案，如 `这里 <http://cle.linux.org.tw/~edt1023/vim/vst/index.html>`_ )
* 生成的默认格式不太美观（这个可以通过指定相应的css文档来生成）


使用google code作为文档的源代码服务器
======================================

使用SVN可以方便地对 **纯文本** 的文件进行集中化管理和版本化管理，方便定期的 **更新** 和 **roll back** 等。
而 `google code`_ 的高可用性和性能，也就很适合作为博客源文件的服务器。

那么完成上面这些步骤后，我通常是这样来写博客：

#. 用 **VIM** 编辑所要写的内容(符合reST的规范)
#. 使用 **rst2html** 生成相应的html文件（指定我特定的CSS格式）
#. 将生成的html内容复制后粘贴到博客园的写博客编辑器中，完成相应操作并提交
#. 一个完整的博客书写过程完成

在上述的步骤中，对于步骤2，若需要使其更加 **自动化** ，还需作如下的修改，包括:

* 写一个模拟登录博客园的脚本
* 将rst2html生成的html相应部分自动抓取并提交给博客园
* 上面的过程还会提交相应的分类,标签等

用户只需要：

* 完成 *restructuredText* 文档的书写
* 运行脚本

但是我通常觉得上面提到的自动化意义不大, 因为

#. 通常直接复制到编辑器,即可预览等操作,以避免格式的问题
#. 自动化的脚本也会可能因为博客园的服务做出相应的调整(如链接地址等)而失效

参考资料
==============================
#. `VIM`_
#. `google code`_
#. `restructuredText`_
#. `python`_
#. `reportlab`_
#. `docbook`_

.. _VIM: http://vim.org
.. _google code: http://www.googlecode.com
.. _restructuredText: http://docutils.sourceforge.net/rst.html
.. _python: http://www.python.org
.. _reportlab: http://www.reportlab.com>
.. _docbook: http://www.docbook.org
