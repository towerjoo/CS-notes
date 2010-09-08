import os
import sys

curdir = os.path.abspath(os.path.dirname(__file__))


notes = ["programming", "python"]

for note in notes:

    #target = "%s/../%s/" % (curdir, "learning_note", note)
    #source = "%s/../%s/" % (curdir, note, "source")

    target = "../learning_note/docs/%s" % note
    source = "../../%s/source" % note

    cmd = "sphinx-build -a -b html %s %s" % (source, target)
    os.system(cmd)

