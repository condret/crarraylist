#include "list.h"

CRArrayList cr_arraylist_new ()
{
	CRArrayList *ret = calloc (1, sizeof(CRArrayList));
	if (!ret)
		return NULL;
	ret->data = malloc (sizeof(void *)*2);
	if (!ret->data) {
		free (ret);
		return NULL;
	}
	ret->storage_size = 2;
	return ret;
}

void cr_arraylist_free (CRArrayList *list)
{
	int i;
	if (!list)
		return;
	if (list->free)
		for (i = 0; i < list->size; i++)
			free (list->data[i]);
	free (list->data);
	free (list);
}

void cr_arraylist_add (CRArrayList *list, void *data)
{
	void **ptr;
	if (!list)
		return;
	if ((list->size*2) > list->storage_size)
		if (ptr = realloc (list->data, list->storage_size * 2)) {
			list->data = ptr;
			list->storage_size = list->storage_size * 2;
		}
	if (list->size == list->storage_size)
		return;
	list->data[list->size] = data;
	list->size++;
}

void *cr_arraylist_take (CRArrayList *list)
{
	if (!list || !list->size)
		return NULL;
	list->size--;
	if (list->size <= (list->storage_size / 4)) {
		list->data = realloc (list->data, list->storage_size / 2);
		list->storage_size = list->storage_size / 2;
	}
	return list->data[list->size];
}
