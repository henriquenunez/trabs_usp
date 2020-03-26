#ifndef _HASH_H_
#define _HASH_H_

#define MAX_ENTRIES 10000

typedef int err_t;

HASH_TABLE* table_create();
err_t table_insert(HASH_TABLE*, int, void*);
void* table_find(HASH_TABLE*, int);

#endif

