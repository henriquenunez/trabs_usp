#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "bin_tree.h"

void addchar(char* base, char new)
{
	base[strlen(base + 1)] = new;
}

void removechar(char* base, char old)
{
	char* loc; //pointer to last location of old
	loc = strrchr(base, old);
	if (loc != NULL) *loc = 0;
}

void recursive_print(NODE* root, char* format)
{
	if (root == NULL) return;
	if (node_return_content(root) == NULL) return;
	printf("%s> %s\n", format, node_return_content(root));

	addchar(format, '=');
	recursive_print(node_get_left(root), format);
	recursive_print(node_get_right(root), format);
	removechar(format, '=');
}

int main()
{
	TREE* a_tree;

	NODE* temp_node;

	char* levels = (char*) calloc (40, sizeof(char));

	char* a = "amor";
	char* b = "baixinho";
	char* c = "coracao";
	char* d = "doidinho";
	char* e = "esmelindo";
	char* f = "fala tu";
	char* g = "gato";
	char* h = "hiram";
	char* i = "istmo";

	temp_node = tree_node_create(a);

	a_tree = tree_create(temp_node);
	
	node_insert_left(temp_node, tree_node_create(b));
	node_insert_right(temp_node, tree_node_create(c));

	printf("root: %s\n", (char*)node_return_content(temp_node));
	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));

	temp_node = node_get_left(temp_node);

	node_insert_left(temp_node, tree_node_create(d));
	node_insert_right(temp_node, tree_node_create(e));

	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));

	temp_node = node_get_right(temp_node);

	node_insert_left(temp_node, tree_node_create(f));
	node_insert_right(temp_node, tree_node_create(g));

	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));

	temp_node = node_get_left(temp_node);

	node_insert_left(temp_node, tree_node_create(h));
	node_insert_right(temp_node, tree_node_create(i));

	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));


	recursive_print(tree_get_root(a_tree), levels);
}
/*
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "bin_tree.h"

void addchar(char* base, char new)
{
	base[strlen(base + 1)] = new;
}

void removechar(char* base, char old)
{
	char* loc; //pointer to last location of old
	loc = strrchr(base, old);
	if (loc != NULL) *loc = 0;
}

void recursive_print(NODE* root, char* format)
{
	if (root == NULL) return;
	if (node_return_content(root) == NULL) return;
	printf("%s> %s\n", format, node_return_content(root));

	addchar(format, '=');
	recursive_print(node_get_left(root), format);
	recursive_print(node_get_right(root), format);
	removechar(format, '=');
}

int main()
{
	TREE* a_tree;

	NODE* temp_node;

	char* levels = (char*) calloc (40, sizeof(char));

	char* a = "amor";
	char* b = "baixinho";
	char* c = "coracao";
	char* d = "doidinho";
	char* e = "esmelindo";
	char* f = "fala tu";
	char* g = "gato";
	char* h = "hiram";
	char* i = "istmo";

	temp_node = tree_node_create(a);

	a_tree = tree_create(temp_node);
	
	node_insert_left(temp_node, tree_node_create(b));
	node_insert_right(temp_node, tree_node_create(c));

	printf("root: %s\n", (char*)node_return_content(temp_node));
	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));

	temp_node = node_get_left(temp_node);

	node_insert_left(temp_node, tree_node_create(d));
	node_insert_right(temp_node, tree_node_create(e));

	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));

	temp_node = node_get_right(temp_node);

	node_insert_left(temp_node, tree_node_create(f));
	node_insert_right(temp_node, tree_node_create(g));

	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));

	temp_node = node_get_left(temp_node);

	node_insert_left(temp_node, tree_node_create(h));
	node_insert_right(temp_node, tree_node_create(i));

	printf("left: %s\n", (char*)node_return_content(
			node_get_left(temp_node)));
	printf("right: %s\n", (char*)node_return_content(
			node_get_right(temp_node)));


	recursive_print(tree_get_root(a_tree), levels);
}

*/


