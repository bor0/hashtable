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

#include <stdlib.h>
#include <string.h>
#include "ll.h"

void ll_add(ll **list, char *key, char *val) {
	ll *tmp = *list;
	*list = (ll *)malloc(sizeof(ll));
	(*list)->next = tmp;
	(*list)->key = strdup(key);
	(*list)->val = strdup(val);

	return;
}

void ll_remove(ll **list, char *key) {
	ll *tmp, *prev = NULL, *next;

	if (list == NULL) {
		return;
	}

	tmp = *list;

	while (tmp) {
		if (!strcmp(tmp->key, key)) {
			free(tmp->key);
			free(tmp->val);

			next = tmp->next;

			free(tmp);

			if (prev != NULL) {
				prev->next = next;
			} else {
				*list = next;
			}

			return;
		}

		prev = tmp;
		tmp = tmp->next;
	}

	return;
}

char **ll_find(ll *list, char *key) {
	while (list) {
		if (!strcmp(list->key, key)) {
			return &list->val;
		}

		list = list->next;
	}

	return NULL;
}

void ll_free(ll *list) {
	ll *tmp;

	while (list) {
		tmp = list->next;
		free(list->key);
		free(list->val);
		free(list);
		list = tmp;
	}

	return;
}

ll_iterator ll_iterator_start(ll *list) {
	ll_iterator iterator;

	iterator.head = iterator.current = list;
	return iterator;
}

ll *ll_iterator_get(ll_iterator *iterator) {
	return iterator->current;
}

int ll_iterator_end(ll_iterator *iterator) {
	return iterator->current->next == NULL;
}

void ll_iterator_next(ll_iterator *iterator) {
	if (ll_iterator_end(iterator)) {
		return;
	}

	iterator->current = iterator->current->next;
}
