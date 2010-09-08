.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-10-12 21:02

========================================
优化网站后台
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .

点击 `订阅`_ 来订阅本博客.(推荐使用 `google reader`_, 如果你的浏览器不支持直接订阅,请直接在 `google reader`_ 中手动添加).


摘要
========================================

本文通过实际的例子来对即将发布的一个网站服务进行压力测试并且进行相关的优化.

主要涉及的技术包括: `apache ab`_ , `memcached`_, `nginx`_, `fastcgi`_ 等 .


.. contents::





引入
========================================

最近做了一个基于 `python`_ / `django`_ 的服务网站, 目前已经进入了尾期, 也就在最近2周内会
进行第一版的发布. 在发布之前, 考虑到我们的目标用户的规模以及每日预估的PV数, 我们决定
做一些基本的优化.

大致的思路如下:

#. 对当前未优化的网站进行性能测试(使用 `apache ab`_)
#. 逐步进行优化处理
    
    * `memcached`_ 的使用
    * `nginx`_ 的使用
    * `fastcgi`_ 替代mod_python



使用ab对未优化的网站进行性能测试
========================================

`apache ab`_ 是一种对网站性能进行基准测试的工具, 由于简单易用, 并且免费开源, 
所以得到了较为广泛的使用.

本次优化所有的基准测试都是基于 `apache ab`_ 来进行的.

首先在未进行任何优化前, 当前的系统部署方式为: `apache`_, `mod_wsgi`_ , 而 `wsgi`_ 开了
4个进程.

#. 

使用如下命令:

`ab -c 1000 -n 1000 http://example.com`

得到如下的结果报告:

::

    Concurrency Level:      1000
    Time taken for tests:   92.486 seconds
    Complete requests:      1000
    Failed requests:        45
    (Connect: 0, Receive: 0, Length: 45, Exceptions: 0)
    Write errors:           0
    Non-2xx responses:      45
    Total transferred:      42878539 bytes
    HTML transferred:       42544689 bytes
    Requests per second:    10.81 [#/sec] (mean)
    Time per request:       92486.306 [ms] (mean)
    Time per request:       92.486 [ms] (mean, across all concurrent requests)
    Transfer rate:          452.75 [Kbytes/sec] received

    Connection Times (ms)
      min  mean[+/-sd] median   max
      Connect:      341 6908 9237.1   3347   49530
      Processing:   345 38764 21927.0  33709   91023
      Waiting:      345 35495 21708.6  29348   85495
      Total:        687 45672 25201.2  40139   92418

     Percentage of the requests served within a certain time (ms)
       50%  40139
       66%  59553
       75%  68183
       80%  72655
       90%  80972
       95%  87800
       98%  91287
       99%  91631
       100%  92418 (longest request)
   
那么我们就将上面的数据作为基准数据,并有后面优化的过程中比较优化的程度.


第一次优化(使用memcached)
========================================

在

后记
========================================

参考资料
========================================

本文的rst源码
========================================

本文的源码链接在 `这里`_ .





#. 
#. 
#. 
#. 


.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
.. _订阅: http://feed.feedsky.com/MindsbookTowerJoo
.. _google reader: http://reader.google.com
.. _这里:
.. _apache ab: http://httpd.apache.org/docs/2.0/programs/ab.html
