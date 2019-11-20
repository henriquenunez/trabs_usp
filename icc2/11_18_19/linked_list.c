#include <stdlib.h>
#include "linked_list.h"

/*DEFINES*/

#define SUCCESS 0;
#define NON_EXCISTE -1;
#define FAILED -2;
#define EXISTS -3;

typedef struct _node
{
	void* content;
	int key;
	struct _node *next;
}NODE;

struct _list
{
	NODE* first;
	NODE* last;
	void (*free_func)(void*);
};

/*PROTOTYPES*/

NODE* node_create();
NODE* node_free(NODE*, void (*free_func)(void*));
int node_set(NODE*, int, void*);

/*FUNCTIONS*/

LIST* list_create(void(*free_func)(void*))
{
	LIST* new_list = (LIST*) calloc (1, sizeof(LIST));
	new_list->free_func = free_func;
	return new_list;
}

int list_append(LIST* this_list, int key, void* content)
{
	if (this_list == NULL || content == NULL || key <= 0) return FAILED;

	NODE* this_node = node_create();
	node_set(this_node, key, content);

	if (this_list->first == NULL)
	{
		this_list->first = this_node;
		this_list->last = this_node;
	}
	else
	{
		this_list->last->next;
	}

	return SUCCESS;
}

int list_exists(LIST* this_list, int key)
{
	NODE* temp = this_list->first;

	while (temp!= NULL)
	{
		if (temp->key == key)
			return EXISTS;
		temp = temp->next;
	}

	return NON_EXCISTE;
}

void* list_retrieve(LIST* this_list, int key)
{
	NODE* temp = this_list->first;

	while (temp!= NULL)
	{
		if (temp->key == key)
			return temp->content;
		temp = temp->next;
	}

	return NULL;
}

int list_purge(LIST* this_list)
{
	NODE* temp = this_list->first;
	while(this_list->first!=NULL)
	{
		temp = node_free(temp, this_list->free_func);
	}
	free(this_list);
}

/*IMPLEMENTATION DETAILS*/

NODE* node_create()
{
	NODE* new_node = (NODE*) calloc (1, sizeof(NODE));
	return new_node;
}

int node_set(NODE* this_node, int key, void* content)
{
	if (key <= 0 || content == NULL) return FAILED;

	this_node->content = content;
	this_node->key = key;

	return SUCCESS;
}

NODE* node_free(NODE* this_node , void (*free_func)(void*))
{
	NODE* ret_node = this_node->next;
	free_func(this_node->content);
	free(this_node);
	return ret_node;
}
