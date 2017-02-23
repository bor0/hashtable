typedef struct ll {
	char *key;
	char *val;
	struct ll *next;
} ll;

void ll_add(ll **list, char *key, char *val);
void ll_remove(ll **list, char *key);
char **ll_find(ll *list, char *key);
void ll_free(ll *list);
