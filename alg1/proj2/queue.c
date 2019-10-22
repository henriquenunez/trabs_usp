#include <stdlib.h>
#include <stdio.h>

#include "nodes.h"
#include "queue.h"
#include "defines.h"

/*
typedef struct _node
{
	void* content;
	struct _node* nxt;	

} NODE;
*/

struct _queue
{
	NODE* first;
	NODE* last;
	NODE* iter;
	short_number_t flag_iter;
	short_number_t amount;
};


QUEUE* queue_create()
{
	QUEUE* new = (QUEUE*) malloc (sizeof(QUEUE));
	new->iter = NULL;
	new->first = NULL;
	new->last = NULL;
	new->flag_iter = 1;
	new->amount = 0;
	return new;
}

/*Creates element at the end of the queue, with the given content*/
int queue_append(QUEUE* this_queue, void* content)
{
	NODE* new_node = node_create();
	
	node_set(new_node, content, NULL);
	
	printf("appended: %p %p\n", new_node, content);
	
	if (this_queue->last == NULL && this_queue->first == NULL)
	{
		this_queue->first = new_node;
		this_queue->last = new_node;
		this_queue->amount++;
		
		return OK;
	}

	node_set(this_queue->last, node_retrieve(this_queue->last, 0), new_node);

	this_queue->last = new_node;
	this_queue->amount++;
	
	return 0;
}

/*Returns content of the first element*/
void* queue_call(QUEUE* this_queue)
{
	NODE* temp;
	void* content;

	printf("first: %p last: %p\n", this_queue->first , this_queue->last);
	if (this_queue->last == NULL) return NULL;
	if (this_queue->first == this_queue->last)
	{
		this_queue->last = NULL;
	}

	temp = this_queue->first;
	content = node_retrieve(temp, 0);
	this_queue->first = (NODE*)node_retrieve(temp, 1);
	free(temp);
	this_queue->amount--;

	return content;
}

/*Iters through queue based on last position*/
void* queue_iter(QUEUE* this_queue)
{
	//printf("Q iter on %p\n", this_queue->iter);
	if (this_queue->amount == 0) return NULL;
	if (this_queue->flag_iter == 0)
	{
		this_queue->flag_iter = 1;
		return NULL;
	}
	if (this_queue->iter == NULL) 
		this_queue->iter = this_queue->first;
	
	void* cont = node_retrieve(this_queue->iter, 0);
	
	if (this_queue->iter == this_queue->last)
	{
		this_queue->flag_iter = 0;
		this_queue->iter = NULL;
	}
	else
		this_queue->iter = (NODE*)
			node_retrieve(this_queue->iter, 1);
	
	return cont;
}

/*Frees every element of the list, the frees the list itself*/
int queue_purge(QUEUE* this_queue)
{
	while(node_free(queue_call(this_queue)) != NULL_PTR_ERR);
	free(this_queue);

	return OK;
}
