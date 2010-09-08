

模板中关于方法调用的说明:

* 方法调用只能调用没有参数的方法,否则系统会进入下一个匹配(参见上面的匹配顺序)
* 对于一些更改数据(side effect)的方法,则需要谨慎,可以在view中声明alters_data = True
  ,django对于这个声明的方法则不用进行实际执行, 而是安静地失败(silently fail)


常用的标签

for .. empty是等价于 if .. for .. else ..,但是前者效率更高

comment: 单行可以使用 {# this is comment #},
多行可以使用 {% comment %} this is comment in multilines {% endcomment %}


addslashes: 这个filter可以在反斜杠,单引号,双引号之前添加一个反斜杠,这样可以用来
**过滤javascript注入**


在view中可以按照如下来进行模板的使用:

#. t = get_template(the_tpl) 来载入模板
#. html = t.render(Context({var:"var"}) 生成html
#. return HttpResponse(html) render模板

这个过程可以使用render_to_response来简化为, 
render_to_response(the_tpl, {var:"var"})

include标签用来包含一些重复的html片断(代码), 其中include的变量可以是模板变量或者字符串.


关于模板继承

通常对于一个实际的站点,可以有三级的继承方式:

#. 全局的父模板(整站的布局,导航等), site.html
#. 特定模块的父模板,例如博客,照片,如site_photo.html, 这个确定这个模块下的页面的布局和导航
#. 特定的单个页面,则会实现具体页面的内容和风格

在子模板中,可以使用 {{ block.super }}来调用父模板中的内容.
