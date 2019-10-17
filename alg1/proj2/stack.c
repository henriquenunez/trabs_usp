#include <stdlib.h>

#include "nodes.h"
#include "defines.h"
#include "stack.h"


struct _stack 
{
	NODE* stack_top;
};


STACK* stack_create()
{
	STACK* new = (STACK*) malloc(sizeof(STACK));
	new->stack_top = NULL;
	return new;
}


int stack_push(STACK* this_stack, void* cont)
{
	NODE* new_node = node_create();
	
	if (this_stack->stack_top != NULL)
		node_set(new_node, cont, this_stack->stack_top);
	
	this_stack->stack_top = new_node;

	return 0;
}


void* stack_pop(STACK* this_stack)
{
	if (this_stack == NULL || this_stack->stack_top == NULL)
		return NULL;
	
	void* temp = this_stack->stack_top;
	void* content = node_retrieve(temp, 0);
	this_stack->stack_top = (NODE*)node_retrieve(temp, 1);
	node_free(temp);

	return content;
}


int stack_purge(STACK* this_stack)
{
	if (this_stack == NULL) return NULL_PTR_ERR;

	while(stack_pop(this_stack) != NULL);
	free(this_stack);

	return OK;
}