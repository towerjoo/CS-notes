import os
import shutil

def rmsvn(path, target):
    """
    remove the .svn directories recursively

    >>> curdir = os.path.abspath(os.path.dirname(__file__))
    >>> path = os.path.join(curdir, "testfolder")
    >>> target = ".svn"
    >>> rmsvn(path, target)
    """

    filename = path.split(os.path.sep)[-1]
    if os.path.isdir(path):
        if filename == target:
            shutil.rmtree(path)
        else:
            for file in os.listdir(path):
                rmsvn(os.path.join(path, file), target)



if __name__ == "__main__":
    import doctest
    doctest.testmod()



