infile = open("program.jvm", "r")
f = infile.read()
memory = []

for c in f:
	memory.append("%02x" % ord(c))
	
print memory
infile.close()
