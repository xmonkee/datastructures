all: lib test

test:
	gcc -o bin/test src/test.c -Llib -ltree -Iinclude

lib: objs
	ar cr lib/libtree.a stack.o tnw.o tree.o
	rm -f *.o

objs:
	gcc -c src/stack.c src/tnw.c src/tree.c -Iinclude

clean:
	rm -rf lib/* bin/* *.o
