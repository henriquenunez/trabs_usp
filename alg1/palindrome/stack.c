#include <stdlib.h>
#include "stack.h"
#include <stdio.h>

typedef struct _node NODE;
 
struct _node
{
	char content;
	NODE* next;
};

struct _stack
{
	NODE* stack_top;
	NODE* stack_bottom;
	int content;
};

NODE* new_node(char content)
{
	NODE* new = (NODE*) malloc (sizeof(NODE));
	new->content = content;
	new->next = NULL;
	return new;
}

STACK* stack_create()
{
	STACK* new = (STACK*) malloc (sizeof(STACK));
	new->stack_top = NULL;
	new->stack_bottom = NULL;
	return new;
}

void stack_push(STACK* this_stack, char content)
{
	NODE* temp = new_node(content);
	if (this_stack->stack_bottom == NULL)
		this_stack->stack_bottom = temp;
	temp->next = this_stack->stack_top;
	this_stack->stack_top = temp;
}

char stack_pop(STACK* this_stack)
{
	if (this_stack->stack_top == NULL) return 0;
	NODE* temp = this_stack->stack_top;
	if (this_stack->stack_top == this_stack->stack_bottom) 
	{
		this_stack->stack_top == NULL;
		this_stack->stack_bottom == NULL;
	} 
	char content = temp->content;
	this_stack->stack_top = temp->next;
	//printf("sending: %c\n", content);
	free(temp);
	return content;
}

void stack_free(STACK* this_stack)
{
	while (stack_pop(this_stack) != 0);
	free (this_stack);
}

