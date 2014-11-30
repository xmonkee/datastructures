#!/usr/bin/env python


#Author: Mayank Mandava (mayankmandava@gmail.com)
#Graph file generator
#Usage: python gengraph.py N outfile
#N is number of vertices
#File format:
#   First line is a single number indicating total number of indices
#   Following lines:
#   u v1 w1 v2 w2....
#   ==> Vertex number (u) followed by pairs of it's neighbors and edge wt



import random
import sys

def gen_graph(N):
   out = "%s\n"%N #first line is number of vertices
   for u in range(N):
      out += "%s" % u
      degrees = random.randint(0,N)
      for j in range(degrees):
         v = random.randint(0,N-1)
         if v != u:
            wt = random.randint(0,1000)
            out += " %s %s" % (v, wt)
      out += "\n"
   return out


def main():
   with open(sys.argv[2], "w") as f:
      out = gen_graph(int(sys.argv[1]))
      f.write(out)

if __name__=='__main__':
   main()
