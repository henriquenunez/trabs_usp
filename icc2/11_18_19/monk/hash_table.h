#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

typedef struct _hash_table H_TABLE;

H_TABLE* table_create(int, void (*)(void*));
int table_insert(H_TABLE*, int, void*);
void* table_retrieve(H_TABLE*, int);
void table_purge(H_TABLE*);

#endif

