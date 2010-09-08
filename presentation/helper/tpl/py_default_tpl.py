# coding: utf-8

code_template =  \
'''class %(classname)s(object):
    """
    The description of the class

    >>> test = %(classname)s()
    >>> test.fun()
    >>> 
    """

    def __init__(self):
        pass

    def method1(self):
        """
        description of method1
        """
        pass

    def method2(self):
        """
        description of method2
        """
        pass

if __name__ == "__main__":
    import doctest
    doctest.testmod(verbose=True)
'''

header_template = \
'''#coding: utf-8
#! /usr/bin/env python

#############################################################
## filename: %(filename)s
## Author: %(author)s <%(email)s>
## version: $Id
## created date: %(created_date)s
## introduction: The short description comes here.
## description: The long description comes here.
#############################################################
'''



TEMPLATE = {
    "author" : "Tower Joo",
    "email" : "zhutao.iscas@gmail.com",
    "statement" : "The source code are based on BSD License",
    "language" : "python",
    "code" : code_template,
    "header" : header_template,
}


