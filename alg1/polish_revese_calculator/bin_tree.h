#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

typedef struct tree TREE;
typedef struct node NODE;


TREE* tree_create();

int node_insert_left(NODE*, NODE*);
int node_insert_right(NODE*, NODE*);

int tree_get_depth(TREE*);

NODE* tree_get_root(TREE*);
NODE* node_get_left(NODE*);
NODE* node_get_right(NODE*);
NODE* tree_node_create(void*);

void tree_node_free(NODE*);
void* node_return_content(NODE*);

#endif

