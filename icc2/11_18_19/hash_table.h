#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

typedef struct _hash_table H_TABLE;

H_TABLE* table_create();
int table_insert(H_TABLE*, int, void*);
H_TABLE* table_remove(H_TABLE*, int, (int));

#undef

