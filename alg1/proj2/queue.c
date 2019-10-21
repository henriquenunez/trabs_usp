#include <stdlib.h>

#include "nodes.h"
#include "queue.h"
#include "defines.h"


typedef struct _node
{
	void* content;
	struct _node* nxt;	

} NODE;


struct _queue
{
	NODE* first;
	NODE* last;
	NODE* iter;
	int amount;
};


QUEUE* queue_create()
{
	QUEUE* new = (QUEUE*) malloc (sizeof(QUEUE));
	new->iter = NULL;
	new->first = NULL;
	new->last = NULL;
	new->amount = 0;
	return new;
}

/*Creates element at the end of the queue, with the given content*/
int queue_append(QUEUE* this_queue, void* content)
{
	NODE* new_node = node_create();
	
	if (this_queue->last == NULL)
	{
		this_queue->last = new_node;
	}

	if (this_queue->first == NULL)
	{
		this_queue->first = new_node;
	}


	//node_set(this_queue->last, this_queue->last->content, new_node);
	node_set(new_node, content, NULL);
	
	this_queue->last = new_node;
	this_queue->amount++;
	
	return 0;
}

/*Returns content of the first element*/
void* queue_call(QUEUE* this_queue)
{
	NODE* temp;
	void* content;

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
	if (this_queue->amount == 0) return NULL;
	if (this_queue->iter == NULL) this_queue->iter = this_queue->first;
	if (this_queue->iter == this_queue->last) this_queue->iter = NULL;
	void* cont = this_queue->iter->content;
	this_queue->iter = this_queue->iter->nxt;
	
	return cont;
}

/*Frees every element of the list, the frees the list itself*/
int queue_purge(QUEUE* this_queue)
{
	while(node_free(queue_call(this_queue)) != NULL_PTR_ERR);
	free(this_queue);

	return OK;
}