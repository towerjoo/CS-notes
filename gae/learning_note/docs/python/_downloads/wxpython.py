# coding:utf-8
#/usr/bin/env python

import os
import wx
ID_ABOUT=101
ID_EXIT=110
ID_OPEN=111
class MainWindow(wx.Frame):
    def __init__(self,parent,id,title):
        wx.Frame.__init__(self,parent,wx.ID_ANY, title, size = (200,100))
        self.control = wx.TextCtrl(self, 1, style=wx.TE_MULTILINE)
        self.CreateStatusBar() # A StatusBar in the bottom of the window
# Setting up the menu.
        filemenu= wx.Menu()
        filemenu.Append(ID_OPEN, "&Open", "打开文件")
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
        wx.EVT_MENU(self, ID_OPEN, self.OnOpen)   # attach the menu-event ID_EXIT to the
# method self.OnExit
        self.Show(True)

    def OnOpen(self, e):
        self.dirname = ""
        dlg = wx.FileDialog(self,"选择一个文件", self.dirname, "", "*.py", wx.OPEN)
        if dlg.ShowModal() == wx.ID_OK:
            self.filename = dlg.GetFilename()
            self.dirname = dlg.GetDirectory()
            f = open(os.path.join(self.dirname, self.filename), 'r')
            self.control.SetValue(f.read())
            f.close()
        dlg.Destroy()

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

