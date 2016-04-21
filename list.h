#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define	ut32	unsigned int

typedef struct cr_array_list_t {
	void *(*free)(void *);
	void **data;
	ut32 size;
	ut32 storage_size;
} CRArrayList;

CRArrayList *cr_arraylist_new ();
void cr_arraylist_free (CRArrayList *list);
bool cr_arraylist_add (CRArrayList *list, void *data);
void *cr_arraylist_take (CRArrayList *list);
void *cr_arraylist_take_idx (CRArrayList *list, ut32 idx);
