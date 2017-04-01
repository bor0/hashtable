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

ht *ht_create(int len) {
	int i;
	ht *table;

	if (len <= 0) {
		return NULL;
	}

	table = (ht *)malloc(sizeof(ht));

	table->len = len;
	table->elements = 0;
	table->array = (ll **)malloc(len * sizeof(ll *));

	for (i = 0; i < len; i++) {
		table->array[i] = NULL;
	}

	return table;
}

void ht_print(ht *table) {
	int i;
	ll *list;
	ll_iterator iterator;

	printf("[ ");

	for (i = 0; i < table->len; i++) {
		printf("\n {");
		list = table->array[i];

		for (iterator = ll_iterator_start(list); !ll_iterator_end(&iterator); ll_iterator_next(&iterator)) {
			list = ll_iterator_get(&iterator);
			printf("\n  '%s': '%s',", ll_get_key(list), ll_get_value(list));
		}

		printf("\n },");
	}

	printf("\n]\n");
}

static int ht_hash(char *str, int len) {
        int h = 1234;
	int a = 4567;
	int i;

        for (i = strlen(str) - 1; i >= 0; i--) {
		h = ((h*a) + str[i]) % len;
        }

        return h;
}

void ht_set(ht *table, char *key, char *value) {
	int index = ht_hash(key, table->len);
	ll *list = ll_find(table->array[index], key);

	if (list != NULL) {
		ll_set_value(list, value);
		return;
	}

	table->elements++;
	ll_add(&table->array[index], key, value);
}


char *ht_get(ht *table, char *key) {
	int index = ht_hash(key, table->len);
	ll *list;

	if (table->array[index] == NULL) {
		return NULL;
	}

	list = ll_find(table->array[index], key);

	return ll_get_value(list);
}

void ht_unset(ht *table, char *key) {
	int index = ht_hash(key, table->len);

	if (table->array[index] == NULL) {
		return;
	}

	table->elements--;
	ll_remove(&table->array[index], key);
}

void ht_free(ht **table) {
	int i;

	if (*table == NULL) {
		return;
	}

	for (i = 0; i < (*table)->len; i++) {
		if ((*table)->array[i] != NULL) {
			ll_free((*table)->array[i]);
		}
	}

	free(*table);

	*table = NULL;
}

float ht_loadfactor(ht *table) {
	return table == NULL || table->len == 0 ? 0 : (float) table->elements / table->len;
}

void ht_rehash(ht **table, int len) {
	ht *new_table;
	int i;

	if (len <= 0) {
		return;
	}

	new_table = ht_create(len);

	for (i = 0; i < (*table)->len; i++) {
		ll_iterator iterator;
		ll *list, *tmp;

		list = (*table)->array[i];

		if (list == NULL) {
			continue;
		}

		for (iterator = ll_iterator_start(list); !ll_iterator_end(&iterator); ll_iterator_next(&iterator)) {
			tmp = ll_iterator_get(&iterator);
			ht_set(new_table, ll_get_key(tmp), ll_get_value(tmp));
		}
	}

	ht_free(table);
	*table = new_table;
}
