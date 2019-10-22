#include <stdlib.h>
#include <stdio.h>

#include "nodes.h"
#include "defines.h"
#include "stack.h"


struct _stack 
{
	NODE* stack_top;
	NODE* stack_bottom;
	NODE* iter;
	short_number_t flag_iter;
	short_number_t amount;
};


STACK* stack_create()
{
	STACK* new = (STACK*) malloc(sizeof(STACK));
	new->stack_top = NULL;
	new->stack_bottom = NULL;
	new->iter = NULL;
	new->amount = 0;
	new->flag_iter = 1;

	return new;
}


int stack_push(STACK* this_stack, void* cont)
{
	NODE* new_node = node_create();
	
	if (this_stack->stack_top != NULL)
		node_set(new_node, cont, this_stack->stack_top);
	else
	{
		node_set(new_node, cont, NULL);
		this_stack->stack_bottom = new_node;
	}
	
	this_stack->stack_top = new_node;
	this_stack->amount++;

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
	this_stack->amount--;

	return content;
}


/*Iters through stack based on last position*/
void* stack_iter(STACK* this_stack)
{
	//printf("S iter is %p\n", this_stack->iter);
	if (this_stack->amount == 0) return NULL;
	if (this_stack->flag_iter == 0)
	{
		this_stack->flag_iter = 1;
		return NULL;
	}
	if (this_stack->iter == NULL) 
		this_stack->iter = this_stack->stack_top;
	
	void* cont = node_retrieve(this_stack->iter, 0);
	
	if (this_stack->iter == this_stack->stack_bottom)
	{
		this_stack->flag_iter = 0;
		this_stack->iter = NULL;
	}
	else 
		this_stack->iter = (NODE*)
			node_retrieve(this_stack->iter, 1);
	
	return cont;
}

int stack_purge(STACK* this_stack)
{
	if (this_stack == NULL) return NULL_PTR_ERR;

	while(stack_pop(this_stack) != NULL);
	free(this_stack);

	return OK;
}
