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

#include "ll.h"

typedef struct ht {
	/* linked list */
	ll **array;

	/* number of current elements */
	int elements;

	/* length of buckets */
	int buckets;
} ht;

ht *ht_create(int buckets);
void ht_print(ht *table);
void ht_set(ht *table, char *key, char *val);
char *ht_get(ht *table, char *key);
void ht_unset(ht *table, char *key);
void ht_free(ht **table);
float ht_loadfactor(ht *table);
void ht_rehash(ht **table, int buckets);
