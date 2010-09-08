#! /usr/bin/env python
# coding: utf-8
"""
本脚本用于自动创建特定源文件的骨架

目前支持的脚本的文件包括:

* python
* html
* blog

脚本会自动从模板文件中读取内容,然后生成相应的骨架
"""

import zipfile
import os
import optparse
import sys


class NotFoundException(Exception):
    """
    如果skeleton没有找到
    """
    def __init__(self, filename):
        self.msg = "Skeleton file %s not found in the same directory and also not found in skeleton.zip in the same directory." % filename

    def __str__(self):
        return repr(self.msg)


class Skeleton:
    """
    基类
    """
    def __init__(self, type, skeleton=""):
        self.type = type
        if skeleton == "":
            skeleton = type + ".skl"
        self.skeleton = skeleton

    def get_skeleton_content(self, skeleton=""):
        """
        获得skeleton文件
        查找顺序:
        1. 同目录skeleton文件
        2. 同目录skeleton.zip中
        如果没找到则出错
        """
        if skeleton == "":
            skeleton = self.skeleton
        skeleton_zip = "skeleton.zip"
        curdir = os.path.abspath(os.path.dirname(__file__))
        try:
            file = os.path.join(curdir, skeleton)
            if os.path.isfile(file):
                return open(file, "r").read()
            if zipfile.is_zipfile(skeleton_zip):
                zipf = zipfile.ZipFile(skeleton_zip, "r")
                if skeleton in zipf.namelist():
                    return zipf.read(skeleton)
                elif os.path.join("skeleton", skeleton) in zipf.namelist():
                    return zipf.read(os.path.join("skeleton", skeleton))
            raise(NotFoundException(skeleton))
        except NotFoundException, e:
            print e.msg
            sys.exit(0)

    def gen_config_tpl(self):
        """
        生成config文件模板
        """
        #config = self.get_skeleton_content("config.skl")
        author = raw_input("Enter the your name as the author(e.g Tower Joo<zhutao.iscas@gmail.com>, as the default):\n")
        if author == "":
            author = "Tower Joo<zhutao.iscas@gmail.com>" 

        output = "config.py"
        if os.path.isfile(output):
            print "%s has already existed! You can't generate the config.py file." % output
            sys.exit(0)
        else:
            config = """# coding: utf-8
data = {
    "author" : "%s",
}
            """ % author
            open(output, "w").write(config)

    def read_config(self):
        """
        读取config文件
        """
        conf = "config.py"
        if os.path.isfile(conf):
            import config
            return config.data
        else:
            print "%s not found! Generate it automaticlally." % conf
            self.gen_config_tpl()
            import config
            return config.data
            #sys.exit(0)

    def gen_classname_from_filename(self, filename):
        cls = filename.split(".")[0]
        classname = cls[0].upper() + cls[1:]
        return classname

    def gen_output(self, output):
        """
        通过获得的skeleton来产生输出文件
        """
        if len(output.split(".")) == 1:
            print "Your output should have a postfix."
            sys.exit(0)
        if self.type == "unknown":
            print "the postfix of the output is unknown."
            sys.exit(0)

        skeleton = self.get_skeleton_content()
        conf = self.read_config()
        if os.path.isfile(output):
            print "%s has already existed! You can't generate the output file." % output
            sys.exit(0)
        else:
            from datetime import datetime
            data = {
                "filename" : output,
                "classname" : self.gen_classname_from_filename(output),
                "date" : datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
                "description" : "",
            }
            conf.update(data)
            open(output, "w").write(skeleton % conf)

if __name__=="__main__":
    parser = optparse.OptionParser("usage: %prog [options] output")
    parser.add_option("-S", "--skeleton", dest="skeleton",
                      default="", type="string",
                      help="specify the skeleton to generate from. will use <format>.skl for <format> if not provided.")
    parser.add_option("-T", "--type", dest="type", default="",
                      type="string", help="the type of the file to generate, like html,python,php. Will get from the postfix of output if not provided.")

    (options, args) = parser.parse_args()
    if len(args) != 1:
        print "Invalid call!\n" 
        parser.print_help()
        sys.exit(0)

    format = {
        "py" : "python",
        "php" : "php",
        "html" : "html",
        "htm" : "html",
        "js" : "javascript",
        "css" : "css",
        "rst" : "rst",
    }
    type = options.type
    if type == "":
        type = format.get(args[0].split(".")[-1], "unknown")
    skeleton = options.skeleton
    a = Skeleton(type, skeleton)
    a.gen_output(args[0])

