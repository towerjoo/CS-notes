
def gen_rst_header(name):
    from datetime import datetime
    name = ".".join(name.split(".")[:-1])
    cont = ""
    cont += ".. Author: Tower Joo<zhutao.iscas@gmail.com>\n"
    cont += ".. Time: %s\n\n" % datetime.now().strftime("%Y-%m-%d %H:%M")
    cont += "="*40 + "\n"
    cont += "%s\n" % name
    cont += "="*40 + "\n"

    cont += ":Author: %s \n" % "朱涛"


