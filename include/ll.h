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

typedef struct ll {
	// key of hashtable element
	char *key;

	// value of hashtable element
	char *val;

	// next element in linkedlist
	struct ll *next;
} ll;

typedef struct ll_iterator {
	// start of list
	ll *head;

	// current pointer
	ll *current;
} ll_iterator;

void ll_add(ll **list, char *key, char *val);
void ll_remove(ll **list, char *key);
char **ll_find(ll *list, char *key);
void ll_free(ll *list);
char *ll_get_key(ll *list);
char *ll_get_val(ll *list);

ll_iterator ll_iterator_start(ll *list);
ll *ll_iterator_get(ll_iterator *iterator);
int ll_iterator_end(ll_iterator *iterator);
void ll_iterator_next(ll_iterator *iterator);
