#coding: utf-8
#! /usr/bin/env python

#############################################################
## filename: gen_tpl.py
## Author: Tower Joo <zhutao.iscas@gmail.com>
## version: $Id
## created date: 2009-09-23 22:11
## introduction: as a command line tool
## description: 
#############################################################

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

import tpl_helper
import sys
import os
from optparse import OptionParser

def handle_cmd():
    
    parser = OptionParser()
    parser.add_option("-t", "--type", dest="type", 
                      help="Specify the file type your want to generate, rst/s5/sphinx/py/php/c")
    parser.add_option("-o", "--output",
                        dest="filename", help="The filename you want to generate")
    parser.add_option("-u", "--update", action="store_true",
                         help="The dict file you want to update")

    (options, args) = parser.parse_args()


    if options.filename is None:
        print "You should provide the file name"
        parser.print_help()
        sys.exit(0)
    if options.filename is None:
        print "You should provide the type"
        parser.print_help()
        sys.exit(0)
    filename = options.filename
    type = options.type

    if tpl_helper.ext_mapping.get(type) == ".rst":
        helper = tpl_helper.RstHelper(filename, type=type)
    else:
        helper = tpl_helper.ProgramHelper(filename, type=type)

    helper.apply_tpl()




if __name__ == "__main__":
    handle_cmd()


