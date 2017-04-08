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

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "ht.h"

ht_options options = { 0, NULL };

void test_ht_has() {
	ht *ht = ht_create(10, options);

	ht_set(ht, "asdf", "1");

	/* Should return true if the key exists */
	assert(ht_has(ht, "asdf"));

	/* Should return false if the key doesn't exist */
	assert(!ht_has(ht, "bsdf"));

	ht_free(&ht);
}

void test_ht_set() {
	ht *ht = ht_create(10, options);

	ht_set(ht, "asdf", "1");
	/* Should go into the third bucket */
	assert(!strcmp(ll_get_key(ht->array[2]), "asdf"));
	assert(!strcmp(ll_get_value(ht->array[2]), "1"));

	ht_set(ht, "asdf", "2");
	/* Setting the same key should just overwrite the same value */
	assert(!strcmp(ll_get_key(ht->array[2]), "asdf"));
	assert(!strcmp(ll_get_value(ht->array[2]), "2"));

	ht_set(ht, "bsdf", "1");
	/* Setting another key should not overwrite the previous inserted value */
	assert(!strcmp(ll_get_key(ht->array[2]), "asdf"));
	assert(!strcmp(ll_get_value(ht->array[2]), "2"));

	/* The new key should go into the fourth bucket */
	assert(!strcmp(ll_get_key(ht->array[3]), "bsdf"));
	assert(!strcmp(ll_get_value(ht->array[3]), "1"));

	ht_free(&ht);
}

void test_ht_get() {
	ht *ht = ht_create(10, options);

	ht_set(ht, "asdf", "1");
	/* Should be equal to '1' for the 'asdf' key */
	assert(!strcmp(ht_get(ht, "asdf"), "1"));

	/* Should return NULL on a key that doesn't exist */
	assert(ht_get(ht, "bsdf") == NULL);

	ht_free(&ht);
}

void test_ht_unset() {
	ht *ht = ht_create(10, options);
	int retval;

	ht_set(ht, "asdf", "1"); /* Third bucket */
	ht_set(ht, "bsdf", "2");

	retval = ht_unset(ht, "asdf");

	/* unset should return true on successful removal, "asdf" should be removed from the third bucket */
	assert(retval && ht->array[2] == NULL);

	retval = ht_unset(ht, "asdf");

	/* unset should return false when nothing is removed */
	assert(!retval);

	/* "bsdf" should remain in the fourth bucket */
	assert(!strcmp(ll_get_key(ht->array[3]), "bsdf"));
	assert(!strcmp(ll_get_value(ht->array[3]), "2"));

	ht_free(&ht);
}

void test_ht_loadfactor() {
	ht *ht = ht_create(10, options);

	ht_set(ht, "asdf", "1"); /* Third bucket */
	ht_set(ht, "bsdf", "2");

	/* We have 2 elements in 10 buckets, so the load factor is 2/10 == 0.2 */
	assert(ht_loadfactor(ht) == 0.2f);

	ht_set(ht, "asdf", "10"); /* Third bucket */

	/* Load factor should not be affected when updating values for the same key */
	assert(ht_loadfactor(ht) == 0.2f);

	ht_unset(ht, "asdf");

	/* Load factor should be affected when removing existing keys (1/10) */
	assert(ht_loadfactor(ht) == 0.1f);

	ht_unset(ht, "asdf");

	/* Load factor should not be affected when removing non-existing keys (1/10) */
	assert(ht_loadfactor(ht) == 0.1f);

	ht_free(&ht);
}

void test_ht_rehash() {
	ht *ht = ht_create(3, options);

	ht_set(ht, "x1", "1"); /* Third bucket */
	ht_set(ht, "y2", "2"); /* Second bucket */
	ht_set(ht, "z3", "3"); /* First bucket */

	/* Load factor should be equal to 1 (3/3) */
	assert(ht_loadfactor(ht) == 1.0f);

	ht_set(ht, "a4", "3"); /* First bucket */
	ht_set(ht, "b5", "3"); /* Third bucket */
	ht_set(ht, "c6", "3"); /* Second bucket */

	/* Load factor should be equal to 2 (6/3) */
	assert(ht_loadfactor(ht) == 2.0f);

	ht_rehash(ht, 6);

	/* Load factor should be equal to 1 after rehash (6/6) */
	assert(ht_loadfactor(ht) == 1.0f);

	ht_rehash(ht, 12);

	/* Load factor should be equal to 0.5 after rehash (6/12) */
	assert(ht_loadfactor(ht) == 0.5f);

	ht_rehash(ht, 2);

	/* Load factor should be equal to 3 after rehash (6/2) */
	assert(ht_loadfactor(ht) == 3.0f);

	ht_free(&ht);
}

int main() {
	test_ht_has();
	test_ht_set();
	test_ht_get();
	test_ht_unset();
	test_ht_loadfactor();
	test_ht_rehash();

	printf("ht: All tests pass.\n");

	return 0;
}
