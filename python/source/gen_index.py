# coding:utf-8
class Index(object):
    """Generate the index for sphinx document.
    """

    def __init__(self, file, output = ""):
        self.file = file
        self.content = self.process()
        if output == "":
            items = file.split(".")
            self.output  = "%s_backup.%s" % (".".join(items[:-1]), items[-1])

    def process(self):
        """process the file to get the content and close
        """
        try:
            fh = open(self.file)
            content = fh.read()
            fh.close()
        except IOError:
            content = ""
        return content
    
    def write2file(self, file, cont):
        """write to the index-including new file
        """
        try:
            fh = open(file, "w")
            fh.write(cont)
            fh.close()
        except IOError:
            print "IOError: %s" % file

    def gen_index(self):
        """Generate the index for the sphinx document.

        Here you can change the method *algorithm*.
        """
        self.write2file(self.output, self.content)
        self.proc_relate()
        self.write2file(self.file, self.content)

    def pre_proc(self):
        """pre-porcess the content to make all \r\n to \n
        """
        import re
        self.content = re.sub("\r\n", "\n", self.content)

    def post_proc(self):
        """post-process the content to make all \n to \r\n
        """
        import re
        self.content = re.sub("\n", "\r\n", self.content)

    def algorithm(self):
        """This algorithm is:

        1. find the title, subtitle, section, subsection, which includes alphanumber only
        2. add the ".. index::\n index_name" to it by substitute
        3. write to the output file
        """
        import re
        self.pre_proc()
        pattern = r"(\n(\w[\w ]+)\n[_=\^]+\n)"
        #pattern = r"[a-zA-Z0-9-_ ]+\r\n"
        rx = re.compile(pattern)
        self.content = rx.sub(r"\n.. index::\n    \2\n\1", self.content)
        self.post_proc()

    def proc_relate(self):
        """ process the title with "关于，相关"
        """
        import re
        self.pre_proc()
        #process "关于"
        #pattern = ur"(\n关于([^\n]+)\n[_=\^]+\n)"
        pattern = r"(\n关于([^\n]*)\n[_=\^]+\n)"
        #pattern = r"[a-zA-Z0-9-_ ]+\r\n"
        rx = re.compile(pattern)
        self.content = rx.sub(r"\n.. index::\n    \2\n\1", self.content)
        #process "相关"
        pattern = r"(\n([^\n]+)相关\n[_=\^]+\n)"
        rx = re.compile(pattern)
        self.content = rx.sub(r"\n.. index::\n    \2\n\1", self.content)
        self.post_proc()


def show_help():
    import sys
    argv = sys.argv
    def usage():
        print "\n"
        print "Usage: python gen_index.py filename"
        print "author: Tower Joo <zhutao.iscas@gmail.com>"
        print "version: 0.1"
        print "filename: the name of the sphinx file"
        print "This script will generate a new file same as the *filename* and backup the old *filename* as *filename_back*"
        print "\n"

    if len(argv) != 2:
        usage()
        return None
    else:
        return argv[1]

if __name__ == "__main__":
    file = show_help()
    if file:
        a = Index(file)
        a.gen_index()
