#coding: utf-8
import wx
class TextFrame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, -1, '中科院研究生院网络登录',
        size=(400, 200))
        panel = wx.Panel(self, -1)
        basicLabel = wx.StaticText(panel, -1, "你的账号:")
        self.basicText = wx.TextCtrl(panel, -1, "", size=(175, -1))
        self.basicText.SetInsertionPoint(0)
        pwdLabel = wx.StaticText(panel, -1, "你的密码:")
        self.pwdText = wx.TextCtrl(panel, -1, "", size=(175, -1),
        style=wx.TE_PASSWORD)
        sizer = wx.FlexGridSizer(cols=2, hgap=6, vgap=6)

        self.button = wx.Button(panel, -1, "确定", pos=(30,150))
        self.Bind(wx.EVT_BUTTON, self.OnClick, self.button)
        self.button.SetDefault()

        self.exit= wx.Button(panel, -1, "关闭", pos=(130,150))
        self.Bind(wx.EVT_BUTTON, self.OnExit, self.exit)

        #create a list box
        field = ["mails.gucas.ac.cn", "gucas.ac.cn"]
        wx.StaticText(panel, -1, "请选择域:", pos=(10, 70))
        self.choice = wx.Choice(panel, -1, pos=(80,70), choices=field)
        self.choice.SetSelection(0)
        
        types = ["连线国际", "连线国内", "连线城域", "离线"]
        wx.StaticText(panel, -1, "请选择操作:", pos=(10, 110))
        self.type= wx.Choice(panel, -1, pos=(80,110), choices=types)
        self.type.SetSelection(0)

        sizer.AddMany([basicLabel, self.basicText, pwdLabel, self.pwdText])
        panel.SetSizer(sizer)
    def OnClick(self,event):
        field = self.choice.GetStringSelection()
        if field == "mails.gucas.ac.cn":
            field = 1
        else:
            field = 2
        uid = self.basicText.GetValue()
        psw = self.pwdText.GetValue()
        type = self.type.GetStringSelection()
        self.login(uid, psw,field, type)

    def login(self, uid, psw, field, type):
        import urllib2
        import urllib
        url = "https://auth.gucas.ac.cn/php/user_login.php"
        name = "loginuser"
        domain = "domainid"
        pasw = "password"
        refer = "refer"
        refer_value = "https://auth.gucas.ac.cn/php/onlinestatus.php?logout_offnet=1"
        t="logintype"
        
        data = [(name, uid), (pasw,psw), (domain, field), (t, type.encode('utf-8'))]
        uh = urllib2.urlopen(url, urllib.urlencode(data))
        print uh.read()


    def OnExit(self,event):
        self.Close(True)
if __name__ == '__main__':
    app = wx.PySimpleApp()
    frame = TextFrame()
    frame.Show()
    app.MainLoop()
