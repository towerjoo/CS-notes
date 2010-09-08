=========================
python GUI编程学习
=========================

各种常用GUI库的Hello World 学习
================================
.. note::

    常用的python GUI库包括：Tkinter, wxPython, PyGTK, PyQT4等，下文会就各种库完成一个hellworld例程，最后会进行一个对比，并给出自己的选择。

Tkinter
------------

`Tkinter <http://www.pythonware.com/library/tkinter/introduction/whats-tkinter.htm>`_ 是基于TK GUI Toolkit的一个python库，它是python *标准* 的GUI库。


HelloWorld例程( 下载 :download:`源码 <../download/tkinter.py>` )

::

    from Tkinter import *

    class App:

        def __init__(self, master):

            frame = Frame(master)
            frame.pack()

            self.button = Button(frame, text="退出", fg="red", command=frame.quit)
            self.button.pack(side=LEFT)

            self.hi_there = Button(frame, text="Hello", command=self.say_hi)
            self.hi_there.pack(side=LEFT)

        def say_hi(self):
            print "hi there, everyone!"

    root = Tk()
    
    app = App(root)

    root.mainloop()


我的评价：

    #. 优点

        * 所谓的python *standard* gui library
        * 开发还是比较简单的
        * Idle就是使用tkinter开发的

    #. 缺点

        * 默认界面比较丑
        * TK的发展并不好

wxpython
------------

`wxPython <http://www.wxpython.org/>`_ 是基于wxWidgets C++ class library的python GUI库。

一个helloworld的例程：( 下载 :download:`源码 <../download/wxpython.py>` )


::

    import os
    import wx
    ID_ABOUT=101
    ID_EXIT=110
    class MainWindow(wx.Frame):
        def __init__(self,parent,id,title):
            wx.Frame.__init__(self,parent,wx.ID_ANY, title, size = (200,100))
            self.control = wx.TextCtrl(self, 1, style=wx.TE_MULTILINE)
            self.CreateStatusBar() # A StatusBar in the bottom of the window
            # Setting up the menu.
            filemenu= wx.Menu()
            filemenu.Append(ID_ABOUT, "&About"," Information about this program")
            filemenu.AppendSeparator()
            filemenu.Append(ID_EXIT,"E&xit"," Terminate the program")
            # Creating the menubar.
            menuBar = wx.MenuBar()
            menuBar.Append(filemenu,"&File") # Adding the "filemenu" to the MenuBar
            self.SetMenuBar(menuBar)  # Adding the MenuBar to the Frame content.
            wx.EVT_MENU(self, ID_ABOUT, self.OnAbout) # attach the menu-event ID_ABOUT to the
            # method self.OnAbout
            wx.EVT_MENU(self, ID_EXIT, self.OnExit)   # attach the menu-event ID_EXIT to the
            # method self.OnExit
            self.Show(True)

        def OnAbout(self,e):
            d= wx.MessageDialog( self, " A sample editor \n"
                    " in wxPython","About Sample Editor", wx.OK)
            # Create a message dialog box
            d.ShowModal() # Shows it
            d.Destroy() # finally destroy it when finished.

        def OnExit(self,e):
            self.Close(True)  # Close the frame.

    app = wx.PySimpleApp()
    frame = MainWindow(None, -1, "Sample editor")
    app.MainLoop()


评价：

    #. 优点
        
        * 有更多的feauture
        * 响应速度（指启动后）
        * 本地化的界面
        * 有成熟的作品(如ulipad等）

    #. 缺点

        * 启动速度比较慢（wxPython的库比较大，相比于TK)
        * 相比于TK可能不是太stable


pygtk
------------

`pygtk <http://www.pygtk.org/>`_ 是一个基于GTK+库的Python GUI库。

helloworld例程：( 下载 :download:`源码 <../download/pygtk-test.py>` )


::
    
    import pygtk
    pygtk.require('2.0')
    import gtk

    class HelloWorld2:

        # Our new improved callback.  The data passed to this method
        # is printed to stdout.
        def callback(self, widget, data):
            print "Hello again - %s was pressed" % data

        # another callback
        def delete_event(self, widget, event, data=None):
            gtk.main_quit()
            return False

        def __init__(self):
            # Create a new window
            self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)

            # This is a new call, which just sets the title of our
            # new window to "Hello Buttons!"
            self.window.set_title("Hello Buttons!")

            # Here we just set a handler for delete_event that immediately
            # exits GTK.
            self.window.connect("delete_event", self.delete_event)

            # Sets the border width of the window.
            self.window.set_border_width(10)

            # We create a box to pack widgets into.  This is described in detail
            # in the "packing" section. The box is not really visible, it
            # is just used as a tool to arrange widgets.
            self.box1 = gtk.HBox(False, 0)

            # Put the box into the main window.
            self.window.add(self.box1)

            # Creates a new button with the label "Button 1".
            self.button1 = gtk.Button("Button 1")

            # Now when the button is clicked, we call the "callback" method
            # with a pointer to "button 1" as its argument
            self.button1.connect("clicked", self.callback, "button 1")

            # Instead of add(), we pack this button into the invisible
            # box, which has been packed into the window.
            self.box1.pack_start(self.button1, True, True, 0)

            # Always remember this step, this tells GTK that our preparation for
            # this button is complete, and it can now be displayed.
            self.button1.show()

            # Do these same steps again to create a second button
            self.button2 = gtk.Button("Button 2")

            # Call the same callback method with a different argument,
            # passing a pointer to "button 2" instead.
            self.button2.connect("clicked", self.callback, "button 2")

            self.box1.pack_start(self.button2, True, True, 0)

            # The order in which we show the buttons is not really important, but I
            # recommend showing the window last, so it all pops up at once.
            self.button2.show()
            self.box1.show()
            self.window.show()

    def main():
        gtk.main()

    if __name__ == "__main__":
        hello = HelloWorld2()
        main()


pyqt4
-------------

`pyqt4 <http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/pyqt4ref.html>`_ 是一个基于 QT4 的Python GUI库。

Hello world例程：( 下载 :download:`源码 <../download/pyqt4.py>` )


::
    
    import sys
    from PyQt4 import QtCore, QtGui

    app = QtGui.QApplication(sys.argv)

    widget = QtGui.QWidget()
    widget.resize(250, 250)
    widget.setWindowTitle("Test")
    widget.show()

    sys.exit(app.exec_())


比较
---------
    
    #. `tkinter vs. wxpython <http://wiki.wxpython.org/Choosing%20wxPython%20over%20Tkinter>`_

    #. `Rossum's comment about tkinter and wxpython <http://lists.wxwidgets.org/pipermail/wxpython-users/2000-February/000399.html>`_

结论
---------

单就我的个人使用而言，我觉得wxPython足以满足我的需要，因为：

    #. 有本地的界面支持（这点做的比较好，UI比较好看）
    #. 开源的协议
    #. 功能比较强大
    #. 响应速度快（启动可能比较慢）
    #. 已经有成功的作品（如ulipad)

.. literalinclude:: ../download/hello.py
    :linenos:
    :language:python

.. [[[cog 
..  def run_script(input_file, script_name, interpreter='python'):
..    """Run a script in the context of the input_file's directory, 
..      return the text output formatted to be included as an rst
..       literal text block.
..       """
..      from paver.runtime import sh
..      from paver.path import path
..      rundir = path(input_file).dirname()
..      output_text = sh('cd %(rundir)s; %(interpreter)s %(script_name)s 2>&1' % vars(),
..               capture=True)
..      response = '\n::\n\n\t$ %(interpreter)s %(script_name)s\n\t' % vars()
..      response += '\n\t'.join(output_text.splitlines())
..      while not response.endswith('\n\n'):
..          response += '\n'
..          return responsedef run_script(input_file, script_name, interpreter='python'):
..  print "hello"
.. ]]]
.. [[[end]]]
