#include "ll.h"

typedef struct ht {
	ll **array;
	int len;
} ht;

ht *ht_create(int len);
void ht_print(ht *table);
char *ht_get(ht *table, char *key);
void ht_set(ht *table, char *key, char *val);
void ht_unset(ht *table, char *key);
void ht_free(ht **table);
