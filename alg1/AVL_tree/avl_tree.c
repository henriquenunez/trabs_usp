#include <stdlib.h>

#include "defines.h"
#include "bin_tree.h"

struct node 
{
	void* content;
	NODE* L_child;
	NODE* R_child;
	int key;
	int unbal_factor;
	int height;
};


struct tree
{
	NODE* root;
	int depth;
};

NODE* tree_node_create(void*);

/*FUNCTIONS*/

AVL_TREE* avl_tree_create(NODE* root_node)
{
	TREE* new_tree = (TREE*) malloc (sizeof(TREE));
	new_tree->depth = 0;
	new_tree->root = root_node;

	return new_tree;
}

int avl_tree_insert_content(TREE* this_tree, void* content, int key)
{
	__avl_tree_insert_content(&(this_tree->root), content, key);
}

/*TREE IMPLEMENTATION*/

/*TODO
REMOVE
avl balance
avl set height
avl max min
*/

int __avl_tree_insert_content(NODE** this_root, void* content, int key)
{
	if ( (*this_root) == NULL)
	{
		 (*this_root) = __tree_node_create(content, key);
		return SUCCESS;
	}

	if ( (*this_root)->key == key)
	{
		return KEY_EXISTS;
	}
	
	else if ( (*this_root)->key > key) 
	{
		__avl_tree_insert_content(&((*this_root)->L_child), content, key);
	}
	
	else if ( (*this_root)->key < key) 
	{
		__avl_tree_insert_content(&((*this_root)->R_child), content, key);
	}
}

__avl_tree_balance(NODE** this_root)
{
	//check for unbalancing factors on both children
}

/*NODE IMPLEMENTATION*/

NODE* __tree_node_create(void* content, int key)
{
	NODE* new_node = (NODE*) calloc (sizeof(NODE));
	//Unbalacing factor is equal to 0, as well as height
	new_node->content = content;
	new_node->key = key;
	return new_node;
}

