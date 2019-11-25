#include <stdlib.h>

#include "defines.h"
#include "bin_tree.h"

struct node 
{
	void* content;

	NODE* L_child;
	NODE* R_child;

};


struct tree
{
	NODE* root;
	int depth;
};

NODE* tree_node_create(void*);

/*FUNCTIONS*/

TREE* tree_create(NODE* root_node)
{
	TREE* new_tree = (TREE*) malloc (sizeof(TREE));
	new_tree->depth = 0;
	new_tree->root = root_node;

	return new_tree;
}

int node_insert_left(NODE* root, NODE* leaf)
{
	if (root->L_child != NULL) return -2; //already has child
	root->L_child = leaf;

	return OK;
}

int node_insert_right(NODE* root, NODE* leaf)
{
	if (root->R_child != NULL) return -2; //already has child
	root->R_child = leaf;

	return OK;
}

int tree_get_depth(TREE* this_tree)
{

	return this_tree->depth;
}

NODE* tree_node_create(void* content)
{
	NODE* new_node = (NODE*) malloc (sizeof(NODE));
	new_node->content = content;
	new_node->L_child = NULL;
	new_node->R_child = NULL;

	return new_node;
}

void* node_return_content(NODE* this_node)
{
	return this_node->content;
}

NODE* tree_get_root(TREE* this_tree)
{
	return this_tree->root;
}

NODE* node_get_left(NODE* this_node)
{
	return this_node->L_child;
}

NODE* node_get_right(NODE* this_node)
{
	return this_node->R_child;
}

void tree_node_free(NODE* this_node)
{
	free(this_node->content);
	free(this_node);
}

/*IMPLEMENTATION DETAILS*/
