CC=gcc
CFLAGS=-ansi -pedantic -Wall -Iinclude

all: lib tests examples

lib:
	mkdir -p bin
	$(CC) $(CFLAGS) src/ht.c -c -o bin/ht.o
	$(CC) $(CFLAGS) src/ll.c -c -o bin/ll.o
	ar rcs bin/libht.a bin/*.o

tests: lib
	$(CC) $(CFLAGS) tests/ht_test.c -Lbin -lht -o bin/ht_test
	$(CC) $(CFLAGS) tests/ll_test.c -Lbin -lht -o bin/ll_test

runtests: tests
	bin/ht_test
	bin/ll_test

examples: lib
	$(CC) $(CFLAGS) examples/example1.c -Lbin -lht -o bin/example1

runexamples: examples
	bin/example1

clean:
	rm -rf bin
