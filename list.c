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

bool cr_arraylist_add (CRArrayList *list, void *data)
{
	void **ptr;
	if (!list)
		return false;
	if ((list->size*2) > list->storage_size) {
		if (ptr = realloc (list->data, sizeof(void *) * list->storage_size * 2)) {
			list->data = ptr;
			list->storage_size = list->storage_size * 2;
		}
	}
	if (list->size == list->storage_size)
		return false;
	list->data[list->size] = data;
	list->size++;
	return true;
}

void *cr_arraylist_take (CRArrayList *list)
{
	void *ret;
	if (!list || !list->size)
		return NULL;
	list->size--;
	if (list->size <= (list->storage_size / 4)) {
		list->data = realloc (list->data, sizeof(void *) * list->storage_size / 2);
		list->storage_size = list->storage_size / 2;
	}
	ret = list->data[list->size];
	list->data[list->size] = NULL;
	return ret;
}

void *cr_arraylist_take_idx (CRArrayList *list, ut32 idx)
{
	void *ret;
	if (!list || list->size <= idx)
		return NULL;
	if ((list->size - 1) == idx)
		return cr_arraylist_take (list);
	ret = list->data[idx];
	if ((list->size - 1) <= (list->storage_size / 4)) {
		list->data = realloc (list->data, sizeof(void *) * list->storage_size / 2);
		list->storage_size = list->storage_size / 2;
	}
	memmove (list->data + idx, list->data + idx + 1, (list->size - idx) * sizeof (void *));
	list->size--;
	return ret;
}
