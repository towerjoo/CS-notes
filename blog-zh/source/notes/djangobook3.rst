.. Author: Tower Joo<zhutao.iscas@gmail.com>
.. Time: 2009-09-07 10:08

========================================
djangobook3
========================================


本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.
引用本内容时，请保留 `朱涛`_, `出处`_ ，并且 **非商业** .


摘要
========================================



.. contents::





admin
========================================

admin是如何工作的?

#. Django从urls.py中载入urlconf时,开始执行admin.autodiscover()
#. 而autodiscover这个函数会检查每个INSTALLED_APPS中的app,并在对应的目录下
   找到admin.py(如果有)
#. 如果找到了,执行对应app下的admin.py
#. 在admin.py中执行admin.site.register()来注册对应的model到admin中
#. 此时,admin会自动显示编辑/更改的接口


admin支持许多features(如搜索,排序,过滤等),但是前提是需要在admin.py中
显式地声明(具体请参考django的doc)


form
=================

send email

#. from django.core.mail import send_email
#. send_mail(subject, message, from_email, recipient_list, fail_silently=False, auth_user=None, auth_password=None)


from django.core.mail import send_mail, BadHeaderError

def send_email(request):
    subject = request.POST.get('subject', '')
    message = request.POST.get('message', '')
    from_email = request.POST.get('from_email', '')
    if subject and message and from_email:
        try:
            send_mail(subject, message, from_email, ['admin@example.com'])
        except BadHeaderError:
            return HttpResponse('Invalid header found.')
        return HttpResponseRedirect('/contact/thanks/')
    else:
        # In reality we'd use a form class
        # to get proper validation errors.
        return HttpResponse('Make sure all fields are entered and valid.')

**通常在成功提交了POST请求后,都要redirect到另一个页面,而不是当前页面,
因为,如果是当前页面,用户可能刷新页面,从而出现不期待的结果,如发送2次数据等**

django.forms

通常的处理流程是:

#. 通过froms.py中的定义,来确定所提交的表格数据是否有效,通常is_valid()来检验
#. 如果无效则在message中会有出错信息
#. 如果有效,则cleaned_data可用,它会将数据自动转换为python对应的格式,如日期等
#.

加入自己的数据验证:

**django会自动地对检查form的定义中是否有, clean_fieldname这样的方法,如果有
django会在验证特定的fieldname时,自动进行验证(执行clean_fieldname方法**


from django import forms

class ContactForm(forms.Form):

    subject = forms.CharField(max_length=100)
    e-mail = forms.EmailField(required=False)
    message = forms.CharField(widget=forms.Textarea)

    def clean_message(self):
        message = self.cleaned_data['message']
        num_words = len(message.split())
        if num_words < 4:
            raise forms.ValidationError("Not enough words!")
        return message

上面的例子,是加入了信息的长度必须大于4的验证,表单验证时会自动调用这个方法.

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
