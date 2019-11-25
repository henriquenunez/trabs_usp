#include "hash_table.h"
#include "linked_list.h"

#define hash(key,mod) key%mod

struct _hash_table
{
	LIST** lists;
	int size;
};

/*FUNCTIONS*/

TABLE* table_create(int size)
{
	TABLE* new_table = (TABLE*) malloc(sizeof(TABLE));
	new_table->size = size;
	
	new_table->lists = (LIST**) malloc(size * sizeof(LIST*));
	for (int i = 0 ; i < size ; i++)
	{
		new_table->lists[i] = list_create();
	}

	return new_table;
}

int table_insert(TABLE* this_table, void* content, int key)
{
	return list_append(this_table->lists[hash_function(key)]
				content, 
				key);
}

void* table_retrieve(TABLE* this_table, void* content, int key)
{
	return list_retrieve(this_table->lists[hash_function(key)]
				key);
}

void table_purge(TABLE* this_table)
{
	for (int i = 0 ; i < this_table->size ; i++)
	{
		list_purge(new_table->lists[i]);
	}
	free(new_table->lists);
	free(new_table);
}

/*IMPLEMENTATION DETAILS*/
/*
int hash_function(int key, int mod)
{
	return key % mod;
}
*/


