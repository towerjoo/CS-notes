

i = 0
for line in open("zhutao.txt"):
    i += 1
    print "#" + str(i) + line[:-1]
