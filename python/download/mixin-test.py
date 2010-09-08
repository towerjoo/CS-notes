# coding:utf-8
#!/usr/bin/env python

class A:
    pass

class B:

    def p(self, value):
        print value

class C(A):
    pass

if __name__ == "__main__":
    a = C()
    #a.p()   # will get error
    C.__bases__ += (B,) # dynamically change the inheriting tree
    a.p("hello")
