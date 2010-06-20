import re

#converts midi note to frequency
def note2freq(note):
    return 220.0 * 2 ** ((note-57)/12.0)

#converts freq to count needed to attain such a tone
def freq2cnt(freq):
    return (1.0/freq)/(64.0/20000000.0) - 1

#combines the 2 prev functions
def note2cnt(note):
    return freq2cnt(note2freq(note))
    
f = open("spark_out.txt", 'r')
text = f.read()
r0 = re.split('\n', text)

for line in r0:
    r1 = re.search('play\((\d+), (\d+)\)', line, re.DOTALL)
    if(r1 != None):
    	if(int(r1.group(1)) > 0):
        	print "play(" + str(int(note2cnt(int(r1.group(1))))) + ", " + str(int(note2freq(int(r1.group(1)))*(int(r1.group(2))*0.00296/2))) + ");"
        else:
        	print "play(0, " + str(int(440*(int(r1.group(2))*0.00296/2))) + ");"
#r1 = re.search('play(.*)', text, re.DOTALL).group
