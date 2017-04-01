all: lib tests examples

lib:
	mkdir -p bin
	gcc -Iinclude src/ht.c -c -o bin/ht.o
	gcc -Iinclude src/ll.c -c -o bin/ll.o
	ar rcs bin/libht.a bin/*.o

tests: lib
	gcc tests/ht_test.c -Iinclude -Lbin -lht -o bin/ht_test
	gcc tests/ll_test.c -Iinclude -Lbin -lht -o bin/ll_test

runtests: tests
	bin/ht_test
	bin/ll_test

examples: lib
	gcc examples/example1.c -Iinclude -Lbin -lht -o bin/example1

runexamples: examples
	bin/example1

clean:
	rm -rf bin
