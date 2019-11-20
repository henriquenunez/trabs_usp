#ifndef _LIST_H
#define _LIST_H

typedef struct _list LIST;

LIST* list_create();
int list_append(LIST*, int, void*);
int list_exists(LIST*, int);
void* list_retrieve(LIST*, int);
int list_purge(LIST*);

#endif

