all: lib tests

lib:
	mkdir -p bin
	gcc -Iinclude src/ht.c -c -o bin/ht.o
	gcc -Iinclude src/ll.c -c -o bin/ll.o
	ar rcs bin/libht.a bin/*.o

tests: bin/libht.a
	mkdir -p bin
	gcc tests/ht_test.c -Iinclude -Lbin -lht -o bin/ht_test

run:
	bin/ht_test

clean:
	rm -rf bin
