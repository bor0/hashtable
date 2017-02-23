#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ht.h"

ht *ht_create(int len) {
	int i;
	ht *table = (ht *)malloc(sizeof(ht));

	table->len = len;
	table->array = (ll **)malloc(len * sizeof(ll *));

	for (i = 0; i < len; i++) {
		table->array[i] = NULL;
	}

	return table;
}

void ht_print(ht *table) {
	int i;
	ll *tmp;

	printf("[ ");

	for (i = 0; i < table->len; i++) {
		printf("\n {");
		tmp = table->array[i];

		while (tmp != NULL) {
			printf("\n  '%s': '%s',", tmp->key, tmp->val);
			tmp = tmp->next;
		}

		printf("\n },");
	}

	printf("\n]\n");
}

int ht_hash(char *str, int len) {
        int h = 1234;
	int a = 4567;
	int i;

        for (i = strlen(str) - 1; i >= 0; i--) {
		h = ((h*a) + str[i]) % len;
        }

        return h;
}

char *ht_get(ht *table, char *key) {
	int index = ht_hash(key, table->len);
	char **value;

	if (table->array[index] == NULL) {
		return NULL;
	}

	value = ll_find(table->array[index], key);

	return value != NULL ? *value : NULL;
}

void ht_set(ht *table, char *key, char *val) {
	int index = ht_hash(key, table->len);
	char **value = ll_find(table->array[index], key);

	if (value != NULL) {
		free(*value);
		*value = strdup(val);
		return;
	}

	ll_add(&table->array[index], key, val);
}

void ht_unset(ht *table, char *key) {
	int index = ht_hash(key, table->len);

	if (table->array[index] == NULL) {
		return;
	}

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
