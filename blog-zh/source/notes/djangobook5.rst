.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-09-08 23:24

========================================
djangobook5
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .


摘要
========================================



.. contents::






url conf
========================================

一个常规的处理流程为，

# urls.py
from django.conf.urls.defaults import *
from mysite import views
urlpatterns = patterns('',
    # ...
    (r'^somepage/$', views.some_page),
    # ...
    )

from django.http import Http404, HttpResponseRedirect
from django.shortcuts import render_to_response
def some_page(request):
    if request.method == 'POST':
        do_something_for_post()
        return HttpResponseRedirect('/someurl/')#对于post的处理，通常都会跳转到新的页面（post通常有副作用）
    elif request.method == 'GET':
        do_something_for_get()
        return render_to_response('page.html')
    else:
        raise Http404()

#. 
#. 
#. 
#. 

* 
* 
* 
* 






第二部分
========================================

结论
========================================

后记
========================================

参考资料
========================================

#. 
#. 
#. 
#. 


.. _朱涛: http://sites.google.com/site/towerjoo
.. _出处: http://www.cnblogs.com/mindsbook
