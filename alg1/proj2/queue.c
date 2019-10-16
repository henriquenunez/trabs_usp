#include <stdlib.h>
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
}


QUEUE* queue_create()
{
	QUEUE* new = (QUEUE*) malloc (sizeof(QUEUE));

	return new;
}


int queue_append(QUEUE* this_queue, void* content)
{
	NODE* new_node = node_create()
	node_set(this_queue->last, this_queue->last->content, new_node);
	node_set(new_node, content, NULL);
	this_queue->last = new_node;

	return 0;
}

int queue_call()
{
	
}