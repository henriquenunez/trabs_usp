#include <stdlib.h>

#include "hash_table.h"
#include "linked_list.h"

#define hash_function(key,mod) key%mod

struct _hash_table
{
	LIST** lists;
	int size;
};

/*FUNCTIONS*/

H_TABLE* table_create(int size, void (*free_func)(void*))
{
	H_TABLE* new_table = (H_TABLE*) malloc(sizeof(H_TABLE));
	new_table->size = size;
	
	new_table->lists = (LIST**) malloc(size * sizeof(LIST*));
	for (int i = 0 ; i < size ; i++)
	{
		new_table->lists[i] = list_create(free_func);
	}

	return new_table;
}

int table_insert(H_TABLE* this_table, int key, void* content)
{
	return list_append(this_table->lists[hash_function(key, this_table->size)],
				key, 
				content);
}

void* table_retrieve(H_TABLE* this_table, int key)
{
	return list_retrieve(this_table->lists[hash_function(key, this_table->size)],
				key);
}

void table_purge(H_TABLE* this_table)
{
	for (int i = 0 ; i < this_table->size ; i++)
	{
		list_purge(this_table->lists[i]);
	}
	free(this_table->lists);
	free(this_table);
}
