<<<<<<< HEAD
all: test clean
=======
all: lib test
>>>>>>> c18111cc8ff1294f18094c44df367cd3d8dc1053

test:
	gcc -o bin/test src/test.c -Llib -ltree -Iinclude

lib: objs
	ar cr lib/libtree.a stack.o tnw.o tree.o
	rm -f *.o

objs:
	gcc -c src/stack.c src/tnw.c src/tree.c -Iinclude

clean:
<<<<<<< HEAD
	rm -rf *.o tree.a
=======
	rm -rf lib/* bin/* *.o
>>>>>>> c18111cc8ff1294f18094c44df367cd3d8dc1053
