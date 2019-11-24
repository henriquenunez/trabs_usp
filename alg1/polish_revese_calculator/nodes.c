#include <stdlib.h>

#include "nodes.h"
#include "defines.h"


struct _node
{
	void* content;
	struct _node* nxt;	

};


NODE* node_create()
{
	NODE* new = (NODE*) malloc (sizeof(NODE));
	new->nxt = NULL;

	return new;
}


int node_set(NODE* this_node, void* cont, NODE* next)
{
	this_node->content = cont;
	this_node->nxt = next;

	return OK;
}


void* node_retrieve(NODE* this_node, char op)
{
	if (op == 0)
		return this_node->content;
	else
		return this_node->nxt;
}


int node_free(NODE* this_node)
{
	free(this_node);	

	return OK;
}
