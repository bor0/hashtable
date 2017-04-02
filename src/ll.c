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

/*
 * Adding elements to the linked list
 */
void ll_add(ll **list, char *key, char *value) {
	ll *tmp = *list;

	/* create a new list and put the current key and value on top */
	*list = (ll *)malloc(sizeof(ll));
	(*list)->key = strdup(key);
	(*list)->value = strdup(value);

	/* push the other elements to the next of the newly created list */
	(*list)->next = tmp;

	return;
}

/*
 * Removing elements from the linked list
 */
int ll_remove(ll **list, char *key) {
	ll *tmp, *prev = NULL, *next;

	if (list == NULL) {
		return 0;
	}

	tmp = *list;

	/* iterate through the whole list */
	while (tmp != NULL) {

		if (!strcmp(tmp->key, key)) {
			/* free the key and the value */
			free(tmp->key);
			free(tmp->value);

			/* remember the next pointer before freeing the actual list element */
			next = tmp->next;

			free(tmp);

			if (prev != NULL) {
				/* if previous element was initialized (i.e. this is not the first element), set its next value */
				prev->next = next;
			} else {
				/* we removed the first element, so set the start of the list to point to the next one */
				*list = next;
			}

			return 1;
		}

		/* remember the previous element and advance the list */
		prev = tmp;
		tmp = tmp->next;
	}

	return 0;
}

/*
 * Find an element in the linked list by key using the iterators
 */
ll *ll_find(ll *list, char *key) {
	ll_iterator iterator;
	ll *tmp;

	/* iterate through the whole list in attempt to find the key */
	for (iterator = ll_iterator_start(list); !ll_iterator_end(&iterator); ll_iterator_next(&iterator)) {
		tmp = ll_iterator_get(&iterator);

		/* we found the key, so return the list pointer to it */
		if (!strcmp(ll_get_key(tmp), key)) {
			return tmp;
		}
	}

	return NULL;
}

/*
 * Free the linked list from memory
 */
void ll_free(ll *list) {
	ll *tmp;

	/* iterate through the whole list and free all of it */
	while (list != NULL) {
		tmp = list->next;
		free(list->key);
		free(list->value);
		free(list);
		list = tmp;
	}

	return;
}

/*
 * Getter for key
 */
char *ll_get_key(ll *list) {
	return list == NULL ? NULL : list->key;
}

/*
 * Getter for value
 */
char *ll_get_value(ll *list) {
	return list == NULL ? NULL : list->value;
}

/*
 * Setter for key
 */
void ll_set_key(ll *list, char *key) {
	if (list == NULL) {
		return;
	}

	/* if the list is initialized, free the old key and duplicate the new one */
	free(list->key);
	list->key = strdup(key);
}

/*
 * Setter for value
 */
void ll_set_value(ll *list, char *value) {
	if (list == NULL) {
		return;
	}

	/* if the list is initialized, free the old value and duplicate the new one */
	free(list->value);
	list->value = strdup(value);
}

/*
 * Initialization of iterator
 */
ll_iterator ll_iterator_start(ll *list) {
	ll_iterator iterator;

	/* the start of the iterator makes the head and the current pointing to the list */
	iterator.head = iterator.current = list;
	return iterator;
}

/*
 * Getter for current value of the iterator
 */
ll *ll_iterator_get(ll_iterator *iterator) {
	/* get the actual list value from the current iterator */
	return iterator->current;
}

/*
 * Predicate for whether the iterator is completed
 */
int ll_iterator_end(ll_iterator *iterator) {
	return iterator->current == NULL;
}

/*
 * Advancing the iterator to the next element
 */
void ll_iterator_next(ll_iterator *iterator) {
	/* if we're done iterating, just return */
	if (ll_iterator_end(iterator)) {
		return;
	}

	iterator->current = iterator->current->next;
}
