#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef 

TABLE* create_table();
void insert(TABLE*, key, void*);
void* get(TABLE*, key);
void remove(TABLE*, key);
void print_table(TABLE*);


#endif

