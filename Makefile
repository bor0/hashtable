all:
	gcc -Iinclude ht_test.c src/*.c -o ht_test

run:
	./ht_test

clean:
	rm ht_test
