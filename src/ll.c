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
