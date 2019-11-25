#include <stdlib.h>
#include "hash.h"

#define TABLE_SIZE 50

struct table 
{
	void* contents[TABLE_SIZE];
};


int hash_this(int key);

/*FUNCTIONS*/

TABLE* create_table()
{
	TABLE* new_table = (TABLE*) malloc (sizeof(TABLE));
	return new_table;
}

void insert(TABLE* this_table, int key, void* content)
{
	this_table->contents[hash_this(key)] = content;

}

void* get(TABLE* this_table, int key)
{
	return this_table->contents[hash_this(key)];
}

void remove(TABLE* this_table, int key)
{
	this_table->contents[hash_this(key)] = NULL;
}

void print_table(TABLE* this_table)
{
	for (int i = 0 ; i < TABLE_SIZE ; i++)
	{
		//if (this_table->contents[i] != NULL);
		printf("%d => %p", this_table->contents[i]);
	}
} 

/*IMPLEMENTATION DETAILS*/

int hash_this(int key)
{
	return key % TABLE_SIZE;
}

