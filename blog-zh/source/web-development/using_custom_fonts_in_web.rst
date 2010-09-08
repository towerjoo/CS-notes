..  coding: utf-8
.. 1 tab = 4 spaces

.. 文件名: using_custom_fonts_in_web.rst
.. 作者: Tower Joo<zhutao.iscas@gmail.com>
.. 日期: 2009-11-20 18:26:50
.. 说明: 

=============================
在网站中使用自定义字体
=============================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)


摘要
========================================

本文主要介绍如何比较高效,优雅地在自己的web中使用自定义(用户本地没有的)字体,
从而提高自己网站的用户体验.

最后,简单分析了这种解决方案的优缺点,从而为这样的需求提供一种比较可靠而公正的选择参考.


.. contents::


引入
=========

最近在项目中有这样一个需求,就是我们要使用一些比较特殊的字体, 有多么特殊呢,不妨先睹为快, 请看下图:

.. image:: http://farm3.static.flickr.com/2547/4119641278_c733470b78_o.png

上图中,其中第一行,第三行是正常字体,二四行是使用的自定义字体. 效果的差异非常明显.

为了给用户留下比较深刻的印象(我们已经厌烦了千篇一律的字体?), 我们决定在网页的一部分元素上使用自定义的字体.

找寻解决方案
=================

根据我们自己的知识储备,我们确定了可能的几种方案:

#. 转换为图片
#. 在用户加载页面时,为用户下载相应的字体文件到本地
#. 其它.

我们直接排除了方案2,因为这里面会存在安全的问题,而且并非所有的用户都会允许服务器给他下载特殊格式的文件.

于是我们继续确定方案. 我们认为这并不是一个特别 **小众** 的需求,所以internet上应该有对应的解决方案.

于是我们有了第一次的尝试. **使用python的PIL库来实时地转换需要的字体, 以图片的形式呈现给用户.**.

转换为图片
---------------

我便写了下面一个用来生成对应内容的图片的类. 可以点击 `下载python源码`_ (注意如果想在本地运行,请指定相应的truetype字体路径).

.. sourcecode:: python

    import ImageFont, ImageDraw
    from PIL import Image

    class CustomFonts:
        """
        To generate the custom fonts using PIL
        """

        def __init__(self, text, mode="RGBA", font="TIVERTON.TTF", encoding="armn", font_color="red", \
                        font_width=7, h_w=3.5):
            """
            encoding=armn is the result of test, other encodings don't work. a little magic.
            text: the content to generate
            font_width: width of the font
            h_w : the value of height/width
            """
            self.mode = mode
            self.font = font
            self.font_size = (font_width, int(font_width*h_w))
            self.encoding = encoding
            self.font_color = font_color
            self.text = text
            self.image_size = (0, 0)

        def adjust(self, w_adjust=0, h_adjust=0):
            """
            adjust the width and height
            """
            self.image_size = (self.image_size[0] - w_adjust, self.image_size[1] - h_adjust)


        def gen_proper_image_size(self, w_adjust=0, h_adjust=0):
            """
            get the output image's size based on the length of text
            """
            size = self.font_size[0]
            self.image_size = (len(self.text.replace(" ", "")) * size, self.font_size[1])
            self.adjust(w_adjust, h_adjust)

        def gen_images(self, output=""):
            """
            generate the images based on the text
            if output="", the name of the file will be the text with replacing blank with _
            """
            if output == "":
                output = self.text.replace(" ", "_")
            if output.split(".")[-1].lower() not in ("jpg", "jpeg", "png", "gif"):
                output += ".png"

            image = Image.new(self.mode, self.image_size, (0, 0, 0, 0))
            draw = ImageDraw.Draw(image)

            font = ImageFont.truetype(self.font, self.font_size[1], encoding=self.encoding)

            draw.text((0,0), self.text, font=font, fill=self.font_color)
            
            image.save(output)


    if __name__ == "__main__":
        a = CustomFonts("this is for test output".lower())
        a.gen_proper_image_size()
        a.gen_images()

于是生成了类似于下面图片的文字:

.. image:: http://farm3.static.flickr.com/2576/4119657680_c3d2d02a74_o.png

图片有点小,不过你能够看到,还是可用的.

但是, 在后面要生成数字的图片时出现了异常情况, 生成的图片总是半边, 查找了半天原因没有找到(现在想起
还是挺庆幸没有找到,否则可能就不会有后来的方案了.).

总结下这种方案的优劣:

#. 涉及到图片的动态生成和加载(比较大的IO和内存开销)
#. 很难非常精确地生成图片(上面生成的例子并不完美,如果想要一个比较完美的结果,可能需要手动地调整参数不断观察)
#. 颜色和样式(因为直接生成的是图片,所以样式很难更改, 更不用说动态地去改变颜色等)
#. 用户体验(小图片作为菜单会出现不断加载的中间状态, 用户体验比较差)
#. 位于服务器端, 服务器的压力会增大

好处是, 可以比较灵活地订制.

使用js动态替换
------------------

当我无法找到那个数字问题的原因时,我开始尝试新的解决方案.

终于找到了篇博客, `HOW TO USE CUSTOM FONTS ON THE WEBSITE`_ , 于是终于发现了 `CUFON`_.

我们来看看它的feature:

* No plug-ins required – it can only use features natively supported by the client
* Compatibility – it has to work on every major browser on the market
* Ease of use – no or near-zero configuration needed for standard use cases
* Speed – it has to be fast, even for sufficiently large amounts of text

我们来看看它生成的效果:

.. image:: http://farm3.static.flickr.com/2730/4118905505_58bb76919a_o.png

我们来看看它是如何使用的:

.. sourcecode:: html

    <html>
    <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
    <script src="cufon-yui.js" type="text/javascript"></script>
    <script src="Tiverton_400.font.js" type="text/javascript"></script>
    <script type="text/javascript">
    Cufon.replace('div');
    </script>
    </head>
    <body>
    <div style="font-wight:bold;font-size:45px;color:green;" >
    For Test Only. 2009-11-20 
    <a href="http://www.cnblogs.com/mindsbook/">zhutao</a>
    </div>
    </body>
    </html>

非常简单, 需要注意的是:

#. 你需要根据字体文件来生成一个js文件,以便于CUFON查找
#. Cufon.replace('div'); 就是唯一的一句js用来动态地替换相应的文字
#. 可以为你的内容指定额外的样式.

那么 `CUFON`_ 有什么优缺点呢?

#. 对于生成好的字体对应的js文件,其并不依赖于客户端有相应的字体安装
#. 由于js是客户端文件,所以除了首次加载外, 后面会有较好的性能和用户体验
#. 生成的不是图片,所以能够指定额外的样式(具体看下文中的实现分析)
#. 灵活

缺点有: 字体的大小并不严格准确(问题不大),如果用户禁用了js这种方案会失效.

实现分析
===========

那么我们来逐一分析二种方案的实现方式.

转换为图片
--------------

我们使用的是 `PIL`_ , `PIL`_ 目前是支持truetype字体的. `PIL`_ 原理其实很简单, 
就是使用像素来绘制相应的格式的图片(如例子中的png), 为每个像素添加相应的属性值,
如色度,灰度等.

使用js动态替换
----------------------

详细地说明可以参考 `How it works? <http://wiki.github.com/sorccu/cufon/about>`_ 

简单地说, 就是:

#. 将字体文件(ttf)转换为svg font
#. svn font转换为 `VML`_ 
#. 而 `VML`_ 是浏览器所支持
#. `CUFON`_ 核心的js文件会屏蔽掉浏览器的差异,为不同的浏览器生成所支持的html

在Firefox下生成的html(上面例子中的日期)如下:

.. sourcecode:: html

    <cufon class="cufon cufon-canvas" alt="2009-11-20 " style="width: 169px; height: 45px;">
        <canvas width="189" height="63" style="width: 189px; height: 63px; top: -15px; left: 1px;"/>
            <cufontext>2009-11-20 </cufontext>
    </cufon>


结论
===============

使用 `CUFON`_ 已经能够很好地满足我们的项目需求, 简单,强大而灵活, 也不用生成图片,
对浏览器的支持也很好, 所以,如果你的项目中要使用自定义字体,
我强烈推荐 `CUFON`_. 

后记
=========

在本文的论述中并未对中文字体进行相关的调研, 但是笔者估计只要是truetype的字体应该
是没有问题的. 

哪位朋友有兴趣不妨尝试下,记得反馈下结果啊. 谢谢.

欢迎交流.



参考资料
========================================

#. `HOW TO USE CUSTOM FONTS ON THE WEBSITE`_
#. `CUFON`_
#. `VML`_
#. `PIL`_


本文的源码
========================================

本文的rst源码链接在 `这里`_ .

点击 `下载pdf阅读`_ (如果浏览器不支持直接打开,请点击右键另存)

可以点击 `下载python源码`_ (注意如果想在本地运行,请指定相应的truetype字体路径).


.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里: http://groups.google.com/group/python-share/web/using_custom_fonts_in_web.rst
.. _下载pdf阅读: http://groups.google.com/group/python-share/web/%E5%9C%A8%E7%BD%91%E7%AB%99%E4%B8%AD%E4%BD%BF%E7%94%A8%E8%87%AA%E5%AE%9A%E4%B9%89%E5%AD%97%E4%BD%93.pdf
.. _下载python源码: http://groups.google.com/group/python-share/web/custom_fonts.py
.. _HOW TO USE CUSTOM FONTS ON THE WEBSITE: http://www.libhound.com/web-development/user-interfaces/5-techniques-to-use-custom-fonts-on-the-website
.. _CUFON: http://wiki.github.com/sorccu/cufon/
.. _VML: http://www.w3.org/TR/NOTE-VML.html
.. _PIL: http://www.pythonware.com/products/pil/
