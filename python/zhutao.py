"""
this is the module doc
"""
class comp:
    def __init__(self, i, j):
        self.i = i
        self.j = j

    def __repr__(self):
        return "%d + %d*j" % (self.i, self.j)
    def __str__(self):
        return "%d + %d*j" % (self.i, self.j)
    def __add__(self, other):
        return comp(self.i+other.i, self.j+other.j)
    def __getitem__(self, index):
        if index==0:
            return self.i
        elif index==1:
            return self.j
        else:
            raise "IndexError"

u = comp(1,1)
k = comp(1,2)
z = u+k
print z
print z[1]
print u<k
