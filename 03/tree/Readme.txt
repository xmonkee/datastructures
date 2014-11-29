Self Balancing Red-Black Binary Search Tree

compilation: gcc *.c -o dict

files:
   interactive.c - User Interface
   dict.c - interface between interactive moduel and tree datastructure
   tree.c - Tree implementation

Logging: The logfile is by default "tree.log". This can be changed in tree.h
Loggin is enabled by default, *but calculating tree heigh is O(n) operation* and can slow down dictionary performance. It can be turned off in tree.h
