all: test

test: tree.a
	gcc tree.a test.c -o test

tree.a: tree.o
	ar rs tree.a stack.o tnw.o tree.o

tree.o:
	gcc -c stack.c tnw.c tree.c

clean:
	rm -rf *.o tree.a test
