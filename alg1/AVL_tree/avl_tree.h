#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

typedef struct tree TREE;
typedef struct node NODE;

TREE* tree_create();

int avl_tree_get_depth(TREE*);
int avl_tree_insert_content(TREE*, void*, int);
void* avl_tree_return_content(TREE*, int);

#endif

