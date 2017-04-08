/*
 * This file is part of Hashtable.
 * Hashtable is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Hashtable is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Hashtable.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "ht.h"

int hash_test(char *str, int buckets) {
	/* random, right? */
	return 4;
}

int main() {
	ht *test = ht_create(5, hash_test);

	ht_set(test, "asdf", "1");
	ht_set(test, "bsdf", "2");
	ht_set(test, "csdf", "3");
	ht_set(test, "dsdf", "4");
	ht_set(test, "esdf", "5");
	ht_set(test, "fsdf", "6");

	ht_print(test);

	ht_free(&test);

	return 0;
}
