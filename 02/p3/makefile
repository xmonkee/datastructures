all: test clean

test: libtree.a
	gcc -o bin/test -Ltree -llib -Iinclude src/test.c
	rm -f *.o

libtree.a: objs
	ar cr lib/libtree.a stack.o tnw.o tree.o

objs:
	gcc -c src/stack.c src/tnw.c src/tree.c -Iinclude

clean:
	rm lib/* bin/* *.o
