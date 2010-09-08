# coding:utf-8
#! /usr/bin/env python

"""
this script has the following functionalities:

* generate template for rst/s5/sphinx
* support external template
* handle the links to append them to the bottom of the generated files
* add the links automatically from looking up the existed dict of the links
* can expand the dict from scaning the generated files

Usage:

python rst_helper.py -t <type> <filename>


if filename has no extension, the ".rst" will be appended automatically
currently we support the following type:

* rst (default, if you don't specify the type)
* s5
* sphinx
* py
* any other c-like languages, which supports /* */ and // comments

if the same name file already exists, you'll be asked to decide whether overwrite or choose another name

"""

import os
import re
import sys


ext_mapping = {
    "rst" : ".rst",
    "s5" : ".rst",
    "sphinx" : ".rst",
    "py" : ".py",
}
ROOT_PATH = os.path.abspath(os.path.dirname(__file__))

class RstBase(object):
    """
    the base class to be inherited.

    """

    def __init__(self, filename, type="rst", linkdict="linkdict.txt", tpl=""):
        self.type = type
        if os.path.splitext(filename)[-1] == "":
            self.filename = filename + ext_mapping.get(type, "." + type)
        self.linkdict = linkdict
        self.tpl = tpl

    def get_links(self):
        """
        get the existed links from looking up the linkdict
        """
        links = {}
        try:
            for line in open(self.linkdict, "r"):
                entry = line[:-1].split("=>")
                links[entry[0].strip()] = entry[1].strip()
            return links
        except IOError:
            print "No link dict file named %s" % self.linkdict
            sys.exit(0)

    def is_already_exists(self):
        """
        judge whether the filename provided already exists in the current dir
        """
        if os.path.exists(os.path.join(ROOT_PATH, self.filename)):
            return False
        else:
            return True

    def append_links(self):
        """
        append the links which appears in the generated file to the bottom
        """
        try:
            fh = open(self.filename, "r")
            content = fh.read()
            fh.close()
            rx = re.compile(r"`([^`]+)`_")
            links = rx.findall(content)
            links = list(set(links))
            append_text = "\n" * 5
            available_links = self.get_links()
            for key in links:
                append_text += ".. _%s: %s\n" % (key, available_links.get(key, ""))
            content += append_text
            fh = open(self.filename, "w")
            fh.write(content)
            fh.close()
        except IOError:
            print "No generated file found. "
            sys.exit(0)

    def expand_dict(self):
        """
        expand the current dict if the new entry found in the generated file
        """
        try:
            fh = open(self.filename, "r")
            content = fh.read()
            fh.close()
            rx = re.compile(r".. _([^:]+):[ ]*([\S]+)")
            links = rx.findall(content)
            links = list(set(links))
            available_links = self.get_links()
            import copy
            old_linkd = copy.deepcopy(available_links)

            newlinks = {}
            for entry in links:
                newlinks[entry[0]] = entry[1]
            available_links.update(newlinks)
            if available_links == old_linkd:
                pass
            else:
                try:
                    fh = open(self.linkdict, "w")
                    cont = ""
                    for k, v in available_links.iteritems():
                        cont += "%s => %s\n" % (k, v)
                    fh.write(cont)
                    fh.close()
                except IOError:
                    print "No link dict file named %s" % self.linkdict
                    sys.exit(0)

        except IOError:
            print "No generated file found. "
            sys.exit(0)

    def get_tpl_module(self):
        """
        get the template module
        """
        curdir = os.path.abspath(os.path.dirname(__file__))
        tpl_dir = os.path.join(curdir, "tpl")
        if tpl_dir:
            sys.path.insert(0, tpl_dir)

        if self.tpl == "":
            if self.type == "rst":
                self.tpl = "rst_default_tpl.py" 
            else:
                self.tpl = "%s_default_tpl.py" % ("py" if self.type == "py" else "clike")
        base = os.path.splitext(self.tpl)[0]
        cur_tpl = __import__(base)

        if tpl_dir:
            del sys.path[0]

        cur_tpl = cur_tpl.TEMPLATE
        return cur_tpl

    def write_to_file(self, cont):
        """
        write the generated content to the target file
        """
        fh = open(self.filename, "w")
        fh.write(cont)
        fh.close()

    def apply_tpl(self):
        """
        apply the template to generate the file
        """
        pass

class Utility(object):
    """
    some helper methods
    """

    def add_suffix_if_needed(name, suffix):
        if name.split(".")[-1] == suffix:
            return name
        else:
            return name + ".%s" % suffix




class RstHelper(RstBase):
    """
    Rst helper class

    """

    def apply_tpl(self):
        """
        apply the template to generate the file
        """
        cur_tpl = self.get_tpl_module() 
        from datetime import datetime
        name = ".".join(self.filename.split(".")[:-1])
        cont = ""
        cont += ".. Author: %s<%s>\n" % (cur_tpl.get("author", ""), cur_tpl.get("email", ""))
        cont += ".. Time: %s\n\n" % datetime.now().strftime("%Y-%m-%d %H:%M")
        cont += "="*40 + "\n"
        cont += "%s\n" % name
        cont += "="*40 + "\n"
        cont += "\n\n"

        cont += "%s\n\n" % cur_tpl.get("statement", "")

        for h in cur_tpl.get("h1", []):
            cont += "\n"
            cont += "%s\n" % h
            cont += "=" * 50
            cont += "\n" * 5
            if h == "Abstract" or h == "摘要":
                cont += ".. contents::\n"
            cont += "\n" * 5
        self.write_to_file(cont)

class ProgramHelper(RstBase):
    """
    generate the proper programming language template
    python - a seperate template
    c-like: except python
    
    >>> name = "gen_tpl"
    >>> rst = ProgramHelper(name, type="py")
    >>> rst.apply_tpl()
    """
    def apply_tpl(self):

        cur_tpl = self.get_tpl_module()
        from datetime import datetime
        cont = ""
        cont += cur_tpl.get("header", "") % {"filename" : self.filename, "author" : cur_tpl.get("author", ""), 
                                                "email" : cur_tpl.get("email", ""),
                                                "created_date" : datetime.now().strftime("%Y-%m-%d %H:%M")}

        cont += "\n" * 2
        name = ".".join(self.filename.split(".")[:-1])
        classname = name[0].upper() + name[1:] 
        if self.type != "c":
            cont += cur_tpl.get("code", "%(classname)ss") % {"classname":classname}
        self.write_to_file(cont)


if __name__ == "__main__":
    import doctest
    doctest.testmod()
