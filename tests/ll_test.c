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
#include "ll.h"

void test_ll_add() {
	ll *list = NULL;

	ll_add(&list, "asdf", "1");
	assert(!strcmp(list->key, "asdf") && !strcmp(list->value, "1") && list->next == NULL);

	ll_free(list);
}

void test_ll_add_2() {
	ll *list = NULL;

	ll_add(&list, "asdf", "1");
	ll_add(&list, "bsdf", "2");

	assert(!strcmp(list->key, "bsdf") && !strcmp(list->value, "2"));
	assert(!strcmp(list->next->key, "asdf") && !strcmp(list->next->value, "1"));
	assert(list->next->next == NULL);

	ll_free(list);
}

void test_ll_remove() {
	ll *list = NULL;

	ll_add(&list, "asdf", "1");
	ll_add(&list, "bsdf", "2");

	ll_remove(&list, "asdf");

	assert(!strcmp(list->key, "bsdf") && !strcmp(list->value, "2"));
	assert(list->next == NULL);

	ll_remove(&list, "bsdf");

	assert(list == NULL);

	ll_free(list);
}

void test_ll_find() {
	ll *list = NULL, *tmp;

	ll_add(&list, "asdf", "1");
	ll_add(&list, "bsdf", "2");

	tmp = ll_find(list, "asdf");
	assert(!strcmp(tmp->key, "asdf") && !strcmp(tmp->value, "1"));

	tmp = ll_find(list, "bsdf");
	assert(!strcmp(tmp->key, "bsdf") && !strcmp(tmp->value, "2"));

	tmp = ll_find(list, "test");
	assert(tmp == NULL);

	ll_free(list);
}

void test_ll_getters_setters() {
	ll *list = NULL, *tmp;

	ll_add(&list, "asdf", "1");
	ll_add(&list, "bsdf", "2");

	tmp = ll_find(list, "asdf");
	ll_set_key(tmp, "ASDF");
	ll_set_value(tmp, "10");

	tmp = ll_find(list, "bsdf");
	ll_set_key(tmp, "BSDF");
	ll_set_value(tmp, "20");

	assert(!strcmp(list->key, "BSDF") && !strcmp(list->value, "20"));
	assert(!strcmp(list->next->key, "ASDF") && !strcmp(list->next->value, "10"));

	ll_free(list);
}

void test_ll_iterator() {
	ll *list = NULL, *tmp;
	ll_iterator iterator;
	int i;
	const char *test_data_keys[] = {
		"bsdf",
		"asdf"
	};
	const char *test_data_values[] = {
		"2",
		"1"
	};

	ll_add(&list, "asdf", "1");
	ll_add(&list, "bsdf", "2");

	for (iterator = ll_iterator_start(list), i = 0; !ll_iterator_end(&iterator); ll_iterator_next(&iterator), i++) {
		tmp = ll_iterator_get(&iterator);

		assert(!strcmp(ll_get_key(tmp), test_data_keys[i]));
		assert(!strcmp(ll_get_value(tmp), test_data_values[i]));
	}


	ll_free(list);
}

int main() {
	test_ll_add();
	test_ll_add_2();
	test_ll_remove();
	test_ll_find();
	test_ll_getters_setters();
	test_ll_iterator();

	printf("ll: All tests pass.\n");

	return 0;
}
