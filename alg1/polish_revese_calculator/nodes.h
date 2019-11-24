#ifndef NODES_H
#define NODES_H

typedef struct _node NODE;

NODE* node_create();
int node_free(NODE*);

int node_set(NODE*, void*, NODE*);
void* node_retrieve(NODE*, char);

#endif
