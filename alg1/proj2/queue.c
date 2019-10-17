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
};


QUEUE* queue_create()
{
	QUEUE* new = (QUEUE*) malloc (sizeof(QUEUE));

	return new;
}

/*Creates element at the end of the queue, with the given content*/
int queue_append(QUEUE* this_queue, void* content)
{
	NODE* new_node = node_create();
	node_set(this_queue->last, this_queue->last->content, new_node);
	node_set(new_node, content, NULL);
	this_queue->last = new_node;

	return 0;
}

/*Returns content of the first element*/
void* queue_call(QUEUE* this_queue)
{
	NODE* temp;
	void* content;

	temp = this_queue->first;
	content = node_retrieve(temp, 0);
	this_queue->first = (NODE*)node_retrieve(temp, 1);
	free(temp);

	return content;
}

/*Frees every element of the list, the frees the list itself*/
int queue_purge(QUEUE* this_queue)
{
	while(node_free(queue_call(this_queue)) != NULL_PTR_ERR);
	free(this_queue);

	return OK;
}