# coding: utf-8

code_template =  \
'''class %(classname)s:
    /*
     * description:
     *
     */
    // to do here

'''

header_template = \
'''
/*
 * filename: %(filename)s
 * Author: %(author)s <%(email)s>
 * version: $Id
 * created date: %(created_date)s
 * introduction: The short description comes here.
 * description: The long description comes here.
*/
'''



TEMPLATE = {
    "author" : "Tower Joo",
    "email" : "zhutao.iscas@gmail.com",
    "statement" : "The source code are based on BSD License",
    "language" : "python",
    "code" : code_template,
    "header" : header_template,
}


