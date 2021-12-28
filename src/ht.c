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
#include <stdlib.h>
#include <string.h>
#include "ht.h"

/*
 * The hashing private function
 */
static unsigned int ht_hash(char *str, unsigned int buckets) {
	int h = 1234;
	int a = 4567;
	int i;

	/* iterate through each character and calculate its hash */
	for (i = strlen(str) - 1; i >= 0; i--) {
		h = ((h*a) + str[i]) % buckets;
	}

	return h;
}

/*
 * Initialization of the hashtable
 */
ht *ht_create(unsigned int buckets, ht_options options) {
	unsigned int i;
	ht *table;

	if (buckets == 0) {
		buckets = 16;
	}

	/* create a new hashtable and initialize number of buckets and elements */
	table = (ht *)malloc(sizeof(ht));
	table->elements = 0;
	table->options = options;
	table->buckets = buckets;
	table->rehashing = 0;

	/* default to hash function */
	if (table->options.hashfn == NULL) {
		table->options.hashfn = ht_hash;
	}

	/* initialize buckets number of empty linked lists */
	table->array = (ll **)malloc(table->buckets * sizeof(ll *));

	for (i = 0; i < table->buckets; i++) {
		table->array[i] = NULL;
	}

	return table;
}

/*
 * Print the hashtable in a JSON format
 */
void ht_print(ht *table) {
	unsigned int i;
	ll *list;
	ll_iterator iterator;

	printf("[ ");

	/* iterate through all of the buckets */
	for (i = 0; i < table->buckets; i++) {
		printf("\n {");

		/* the current bucket is actually a linked list */
		list = table->array[i];

		/* use list iterator for each bucket and print it */
		for (iterator = ll_iterator_start(list); !ll_iterator_end(&iterator); ll_iterator_next(&iterator)) {
			list = ll_iterator_get(&iterator);
			printf("\n  '%s': '%s',", ll_get_key(list), ll_get_value(list));
		}

		printf("\n },");
	}

	printf("\n]\n");
}

/*
 * Check if a hashtable contains a key
 */
int ht_has(ht *table, char *key) {
	unsigned int index = table->options.hashfn(key, table->buckets) % table->buckets;
	ll *list = ll_find(table->array[index], key);

	return list != NULL;
}

/*
 * Insert/overwrite an element in the hashtable
 */
void ht_set(ht *table, char *key, char *value) {
	unsigned int index = table->options.hashfn(key, table->buckets) % table->buckets;
	ll *list = ll_find(table->array[index], key);

	if (list != NULL) {
		/* the current key exists in the hashtable, so just overwrite its value */
		ll_set_value(list, value);

		return;
	}

	/* increase the number of elements because the current key doesn't exist in the hashtable */
	table->elements++;

	/* add the key and the value to the linked list */
	ll_add(&table->array[index], key, value);

	/* check max loadfactor threshold */
	if (table->options.max_loadfactor != 0 && ht_loadfactor(table) >= table->options.max_loadfactor) {
		ht_rehash(table, table->buckets * 2);
	}
}

/*
 * Get an element from the hashtable
 */
char *ht_get(ht *table, char *key) {
	unsigned int index = table->options.hashfn(key, table->buckets) % table->buckets;
	ll *list = ll_find(table->array[index], key);

	/* in case list NULL (i.e. value was not found or list is not initialized), ll_get_value will return NULL */
	return ll_get_value(list);
}

/*
 * Remove an element from the hashtable
 */
int ht_unset(ht *table, char *key) {
	unsigned int index = table->options.hashfn(key, table->buckets) % table->buckets;

	if (table->array[index] == NULL) {
		/* the list is not initialized at that index, so nothing to remove */
		return 0;
	}

	if (ll_remove(&table->array[index], key)) {
		/* if the key was found in the list and was removed, decrease the number of elements */
		table->elements--;

		return 1;
	}

	return 0;
}

/*
 * Free the hashtable from memory
 */
void ht_free(ht **table) {
	unsigned int i;

	if (*table == NULL) {
		return;
	}

	/* iterate through each bucket and free it */
	for (i = 0; i < (*table)->buckets; i++) {
		if ((*table)->array[i] != NULL) {
			ll_free((*table)->array[i]);
		}
	}

	/* free bucket array */
	free((*table)->array);

	/* we need to keep the original allocation if rehashing */
	if (!(*table)->rehashing) {
		free(*table);
		*table = NULL;
	}
}

/*
 * Calculate the load factor of the hashtable
 */
float ht_loadfactor(ht *table) {
	return table == NULL || table->buckets == 0 ? 0 : (float) table->elements / table->buckets;
}

/*
 * Rehash the hashtable to a different number of buckets
 */
void ht_rehash(ht *table, unsigned int buckets) {
	ht *new_table;
	unsigned int i;

	/* create a new hashtable with the new number of buckets */
	new_table = ht_create(buckets, table->options);

	table->rehashing = 1;

	/* iterate through each bucket of the old table */
	for (i = 0; i < table->buckets; i++) {
		ll_iterator iterator;
		ll *list, *tmp;

		list = table->array[i];

		for (iterator = ll_iterator_start(list); !ll_iterator_end(&iterator); ll_iterator_next(&iterator)) {
			/* get the current element of the iterating bucket */
			tmp = ll_iterator_get(&iterator);

			/* set the key and the value from the old hashtable to the new one */
			ht_set(new_table, ll_get_key(tmp), ll_get_value(tmp));
		}
	}

	/* free the old table (but not the main allocation) */
	ht_free(&table);
	memcpy(table, new_table, sizeof (ht));

	/* free main allocation of new table */
	free(new_table);
}
