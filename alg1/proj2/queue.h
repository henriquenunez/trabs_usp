#ifndef QUEUE_H
#define QUEUE_H

typedef struct _queue QUEUE;

QUEUE* queue_create();
int queue_append(QUEUE*, void*);
void* queue_call(QUEUE*);
int queue_purge(QUEUE*);

#endif