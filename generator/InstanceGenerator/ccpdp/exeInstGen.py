import string
import os
import sys
import numpy


for i in  range(5):
  print "i = %d" % (i+1)

the_count = [1, 2, 3, 4, 5]
for number in the_count: 
  print "This is count %d" % number


os.system("mkdir -p inst/")
for a in range(4,9):
  numberAgents = 2**a
  for d in range(1,6):
    for w in numpy.arange(0.0, 0.5, 0.1):
      print "generating instances with " + str(numberAgents)+"agents " + " type q " + str(d)+"x"+str(d) + " W = "+str(w)
      for id in range(1,11):
        os.system("./a.out inst/ " + str(numberAgents) + " " + str(id) + " q " + str(d)  + " " + str(w))
        #print "./CCPDP inst/ " + str(numberAgents) + " " + str(id) + " q " + str(d)  + " " + str(w) 
        
    
  
