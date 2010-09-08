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

if the same name file already exists, you'll be asked to decide whether overwrite or choose another name

"""

import os
import re
import sys

class RstBase(object):
    """
    the base class to be inherited.

    >>> name = "zhutao.rst"
    >>> rst = RstBase(name)
    >>> rst.append_links()
    >>> rst.expand_dict()
    """

    def __init__(self, filename, type="rst", linkdict="linkdict.txt", tpl="default.txt"):
        self.type = type
        self.filename = filename
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

        def apply_tpl(self):
            """
            apply the template to generate the file
            """
            pass




class RstHelper(RstBase):
    pass


if __name__ == "__main__":
    import doctest
    doctest.testmod()
