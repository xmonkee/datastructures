#!/usr/bin/env python


#Author: Mayank Mandava (mayankmandava@gmail.com)
#Graph file generator
#Usage: python gengraph.py N outfile
#N is number of vertices
#File format:
#   source-vertex  target-vertex  weight



import random
import sys

def gen_graph(N):
   out = ""
   for u in range(N):
      degrees = random.randint(0,min(100, max(min(10,N),N/10)))
      for j in range(degrees):
         v = random.randint(0,N-1)
         if v != u:
            wt = random.randint(0,1000)
            out += " %s %s %s\n" % (u, v, wt)
   return out


def main():
   with open(sys.argv[2], "w") as f:
      out = gen_graph(int(sys.argv[1]))
      f.write(out)

if __name__=='__main__':
   main()
