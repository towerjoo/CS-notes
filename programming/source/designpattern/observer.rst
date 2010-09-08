===================
observer模式
===================

.. index:: observer

.. _observer:

observer模式定义
===================

**observer** 在对象之间定义了一个 **一对多** 的关系,所以
当一个对象状态变化时,其它的所有依赖对象会得到通知,并且
自动更新.

问题描述
==========

一个天气预报的服务商请你开发不同呈现形式的天气服务,可能包括:

* 当前的天气状态
* 天气预报
* 其它

参见下图:

.. image:: ../../image/weather.png

最初我们可能会按照如下的思路进行:

.. code-block:: c++

    class WeatherData
    {
        void measurementsChanged()
        {
            float temp = getTemperature();
            float humi = getHumidity();
            float pres =  getPression();

            currentConditionDisplay.update(temp, humi, pres);   //更新当前的显示
            forcastDisplay.update(temp, humi, pres);    //更新天气预报
        }
    }

但是存在的问题是明显的:

* 显然不同的显示属于所谓 **变化** 的部分, 所以我们应该将其封装
* 当增加新的显示方式时, 需要更改 **WeatherData** 的代码,这是我们不希望的
* 其它

因此我们使用 **observer** 模式来完成,使得 **subject** 和 **observer** 松耦合.

.. note::

    **subject** 即被依赖者,亦即 **被观察者**, 它的变化会影响 **观察者** 的状态
    **observer** 即依赖者,亦即 **观察者**, 它的会依赖于 **subject** 的变化

具体的 **observer** 类图如下:

.. image:: ../../image/observer.png

具体的代码
============

.. note::

    需要注意的是下面的实现采用的是 **push** 的方法,即 *subject* 将所有的信息
    **push** 给 **观察者**, 当然 **观察者** 也可以实现 **pull** 来获取自己
    感兴趣的变化. 

    可以参见p67页的讨论.

下载请点击 :download:`这里 <../../code/observer.cpp>`

.. literalinclude:: ../../code/observer.cpp
    :language: c++
    :linenos:

输出结果为:

::
    
    Current Conditions
    temperature:80
    humidity:62%


    Current Conditions
    temperature:80
    humidity:62%


    Forcast
    temperature:80
    humidity:62%
    pressure:30.4

    Current Conditions  //移除了一个观察者,则不再对其更新状态
    temperature:80
    humidity:62%


    Forcast
    temperature:80
    humidity:62%
    pressure:30.4

面对新的需要
==============

如果这时要增加新的显示方法,可以这样应对:

* 增加一个继承自 **Observer** 和 **DisplayElement** 的新类
* 在新类中实现 **update** 和 **display** 方法即可

 
更多注意
==========

设计准则
----------

**Strive for loosely coupled designs between objects that interact.**


参考更多
===========

#. `C and C++ are not the same language <http://blog.directededge.com/2009/05/21/c-and-c-are-not-the-same-language/>`_ 
   这篇文章使用C/C++/java分别实现了 **observer** 模式
#. `Observer Pattern, Done Differently <http://fsfoundry.org/codefreak/2009/05/24/observer-done-differently/>`_ 
   使用 **boost** 库实现 **observer**
#. `wikipedia Observer Pattern <http://en.wikipedia.org/wiki/Observer_pattern>`_

