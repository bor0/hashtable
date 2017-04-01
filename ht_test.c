#include <stdio.h>
#include "ht.h"

int main() {
	ht *test = ht_create(5);

	ht_set(test, "asdf", "1");
	ht_set(test, "bsdf", "2");
	ht_set(test, "csdf", "3");
	ht_set(test, "dsdf", "4");
	ht_set(test, "esdf", "5");
	ht_set(test, "fsdf", "6");

	ht_print(test);

	ht_unset(test, "asdf");
	ht_unset(test, "bsdf");

	ht_print(test);

	printf("load factor: %f\n", ht_loadfactor(test));

	ht_free(&test);

	return 0;
}
