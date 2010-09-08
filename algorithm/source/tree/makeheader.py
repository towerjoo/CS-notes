# coding:utf-8
#! /usr/bin/env python

def add_suffix_if_needed(name, suffix):
    if name.split(".")[-1] == suffix:
        return name
    else:
        return name + ".%s" % suffix

def gen_rst_header(name):
    from datetime import datetime
    name = ".".join(name.split(".")[:-1])
    cont = ""
    cont += ".. Author: Tower Joo<zhutao.iscas@gmail.com>\n"
    cont += ".. Time: %s\n\n" % datetime.now().strftime("%Y-%m-%d %H:%M")
    cont += "="*40 + "\n"
    cont += "%s\n" % name
    cont += "="*40 + "\n"

    cont += "\n\n"

    cont += ".. warning::\n\n"
    cont += "\t本博客所有内容采用 `Creative Commons Licenses <http://creativecommons.org/about/licenses/meet-the-licenses>`_  许可使用.\n"
    cont += "\t引用本内容时，请保留 **朱涛**, **出处** ，并且 **非商业** .\n"

    cont += "\n\n"

    cont += "摘要\n"
    cont += "=" * 40 + "\n"
    cont += "\n"*6

    cont += "第一部分\n"
    cont += "=" * 40 + "\n\n"
    cont += "#. \n"*4
    cont += "\n"
    cont += "* \n"*4

    cont += "\n"*6

    cont += "第二部分\n"
    cont += "=" * 40 + "\n\n"
    return cont

def gen_doc_rst_header(name):
    """生成一个逐步完善的文档的模板
    包括:更新列表等.
    """
    from datetime import datetime
    name = ".".join(name.split(".")[:-1])
    cont = ""
    cont += ".. Author: Tower Joo<zhutao.iscas@gmail.com>\n"
    cont += ".. Time: %s\n\n" % datetime.now().strftime("%Y-%m-%d %H:%M")
    cont += "="*40 + "\n"
    cont += "%s\n" % name
    cont += "="*40 + "\n"

    cont += "\n\n"

    table = """
============= ==============   ===================   ====================  ===============
时间            版本号          更新内容                更新人              其它
============= ==============   ===================   ====================  ===============
%s     0.1             创建文档                朱涛                

============= ==============   ===================   ====================  ===============
    """ % datetime.now().strftime("%Y-%m-%d")

    cont += table

    cont += "\n\n"

    cont += "文档概要\n"
    cont += "="*40 + "\n"
    cont += "\n"*6

    cont += "第一部分\n"
    cont += "="*40 + "\n"
    cont += "\n"*6

    cont += "第二部分\n"
    cont += "="*40 + "\n"
    cont += "\n"*6

    cont += "参考资料\n"
    cont += "="*40 + "\n"
    cont += "\n#."
    cont += "\n#."
    cont += "\n#."
    cont += "\n#."

    cont += "\n"*6
    return cont

def gen_algorithm_header(name):
    """
    生成算法笔记的模板
    """
    from datetime import datetime
    name = ".".join(name.split(".")[:-1])
    cont = ""
    cont += ".. Author: Tower Joo<zhutao.iscas@gmail.com>\n"
    cont += ".. Time: %s\n\n" % datetime.now().strftime("%Y-%m-%d %H:%M")
    cont += "="*40 + "\n"
    cont += "%s\n" % name
    cont += "="*40 + "\n"

    cont += "\n\n"
    cont += ".. index::\n\t%s\n\n" % name
    cont += ".. _%s:\n\n" % name


    cont += "定义\n"
    cont += "="*40 + "\n"
    cont += "\n"*4

    cont += "实现\n"
    cont += "="*40 + "\n"
    cont += "\n"
    cont += "具体代码\n"
    cont += "="*40
    cont += "\n\n"

    cont += "下载请点击 :download:`这里 <../../code/%s.cpp>`" % name
    cont += "\n\n"
    cont += ".. literalinclude:: ../../code/%s.cpp" % name
    cont += "\n"
    cont += "\t:language: c++\n"
    cont += "\t:linenos:\n"
    cont += "\n\n"
    cont += "输出结果为:\n\n::\n\n"
    cont += "\n\n"


    cont += "\n"*4

    cont += "注意问题\n"
    cont += "="*40 + "\n"
    cont += "\n"*4

    cont += "\n"*6



    cont += "参考资料\n"
    cont += "="*40 + "\n"
    cont += "\n#."
    cont += "\n#."
    cont += "\n#."
    cont += "\n#."

    cont += "\n"*6
    return cont




def gen_py_header(name):
    comment_len = 60
    from datetime import datetime
    cont = ""
    cont += "# coding: utf-8\n"
    cont += "#! /usr/bin/env python\n"
    cont += "\n" * 2
    cont += "#" * comment_len + "\n"
    cont += "## filename: %s\n" % name
    cont += "## Author: Tower Joo<zhutao.iscas@gmail.com>\n"
    cont += "## version: $Id\n"
    cont += "## created time: %s\n" % datetime.now().strftime("%Y-%m-%d %H:%M")
    cont += "## description: The description of the file should be detailed here.\n"
    cont += "#" * comment_len + "\n"
    cont += "\n" * 2
    name = ".".join(name.split(".")[:-1])
    classname = name[0].upper() + name[1:] 
    cont += "class %s(object):\n" % classname
    cont += "\t" + "\""*3 + "\n"
    cont += "\t>>> d = %s\n" % classname
    cont += "\t>>> print d.method()\n"
    cont += "\tvalue\n"
    cont += "\t" + "\""*3 + "\n"
    cont += "\tdef __init__(self):\n"
    cont += "\t\tpass\n"
    cont += "\n" * 3
    cont += "if __name__ == '__main__':\n"
    cont += "\timport doctest\n"
    cont += "\tdoctest.testmod(verbose=True)"

    return cont


def makeheader(gen_content, suffix):
    """
    用于生成相关的文件头,gen_content是个生成特定文件头的函数
    """
    tip = "\npython makeheader.py filename\nfilename是你要新生成的文件名\n\n"
    import sys
    if len(sys.argv) !=2:
        print tip
        outstr = "输入你要新生成的文件名（默认文件后缀为.%s）：\n" % suffix
        name = raw_input(outstr)
    else:
        name = sys.argv[1]
    name = add_suffix_if_needed(name, suffix)
    import os
    while name in os.listdir(os.getcwd()):
        name = raw_input("你要生成新文件在当前目录下已经有重名的文档，请输入新的文件名\n")
        name = add_suffix_if_needed(name, suffix)
    fh = open(name, "w")
    cont = ""
    cont = gen_content(name)
    fh.write(cont)
    fh.close


if __name__ == "__main__":
    # for generating the py header
    #makeheader(gen_py_header, "py")
    # for generating the rst header
    makeheader(gen_algorithm_header, "rst")

