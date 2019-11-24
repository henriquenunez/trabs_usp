#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "stack.h"
#include "bin_tree.h"
#include "defines.h"
#include "calculator.h"

STACK* split_input(char*);

NODE* make_tree(STACK*, NODE*);
int is_operation(char*);
int is_number(char*);

float recursive_operations(NODE*, int*);
void recursive_print(NODE*, char*);
void removechar(char*, char);

float make_things_work(char* yeah)
{
	char* buffer = (char*) calloc (40, sizeof(char)); //char for printing
	strcpy(buffer, "=");
	int *code = (int*) malloc (sizeof(int));

	NODE* a_node;
	STACK* the_stack;

	the_stack = split_input(yeah);
	a_node = make_tree(the_stack, NULL);
	//a_tree = tree_create(a_node);
	//recursive_print(a_node, buffer);
	//printf("%.2f\n", recursive_operations(a_node, code));
	return recursive_operations(a_node, code);
}

/*IMPLEMENTATION DETAILS*/

NODE* make_tree(STACK* operands_stack, NODE* this_root)
{
	char* this_operand;
	NODE* temp_node;

	if (this_root == NULL)
	{
		this_operand = stack_pop(operands_stack);
		//printf("GOT:%s\n", this_operand);
		temp_node = tree_node_create(this_operand); 
		make_tree(operands_stack, temp_node);
		return temp_node;
	}

	/*Evaluation for right child*/

	this_operand = stack_pop(operands_stack);
	//printf("GOT(R):%s\n", this_operand);
	temp_node = tree_node_create(this_operand); 
	node_insert_right(this_root, temp_node);

	if (is_operation(this_operand))
	{
		//printf("Right is operation!\n");
		make_tree(operands_stack, temp_node);
	}
	else
	{
		//printf("Right is number!\n");
	}

	/*Evaluation for left child*/
	
	this_operand = stack_pop(operands_stack);
	//printf("GOT(L):%s\n", this_operand);
	temp_node = tree_node_create(this_operand); 
	node_insert_left(this_root, temp_node);


	if (is_operation(this_operand))
	{
		//printf("Left is operation!\n");
		make_tree(operands_stack, temp_node);
	}
	else
	{
		//printf("Left is number!\n");
	}

	return this_root;
}


STACK* split_input(char* input)
{
	char buffer[40];
	char* position_now;
	char* temp_op;

	STACK* operands_stack = stack_create();

	position_now = strtok(input, " \n");

	while ( position_now != NULL)
	{
		strcpy(buffer, position_now);
		//printf("%s\n", buffer);

		temp_op = (char*) malloc ( (strlen(buffer) + 1) * sizeof(char) );
		strcpy(temp_op, buffer);
		removechar(temp_op, '\n');

		stack_push(operands_stack, temp_op);
		position_now = strtok(NULL, " ");
	}

	return operands_stack;
}

int is_operation(char* this_string)
{
	if (strlen(this_string) != 1) return 0;
	else if (this_string[0] == '/') return DIVISION;
	else if (this_string[0] == '*') return MULTIPLI;  
	else if (this_string[0] == '+') return ADDITION;
	else if (this_string[0] == '-') return SUBTRACT;
	
	return 0;
}

void addchar(char* base, char new)
{
	base[strlen(base)] = new;
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

	printf("%s>>>%s\n", format, (char*)node_return_content(root));
	
	addchar(format, 'l');
	recursive_print(node_get_left(root), format);
	removechar(format, 'l');
	addchar(format, 'r');
	recursive_print(node_get_right(root), format);
	removechar(format, 'r');
}

float recursive_operations(NODE* root, int* err_code)
{
	if (root == NULL) return 0;
	if (node_return_content(root) == NULL) return 0;

	//printf(">>>%s\n", node_return_content(root));

	switch(is_operation(node_return_content(root)))
	{
		case DIVISION:
			return recursive_operations(node_get_left(root), err_code) / 
				recursive_operations(node_get_right(root), err_code);
		case MULTIPLI:
			return recursive_operations(node_get_left(root), err_code) * 
				recursive_operations(node_get_right(root), err_code);
		case ADDITION:
			return recursive_operations(node_get_left(root), err_code) + 
				recursive_operations(node_get_right(root), err_code);
		case SUBTRACT:
			return recursive_operations(node_get_left(root), err_code) - 
				recursive_operations(node_get_right(root), err_code);
		default:
			//printf("%f", atof(node_return_content(root)));
			return atof(node_return_content(root));
	}
}

