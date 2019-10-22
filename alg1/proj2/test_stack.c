#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int main()
{
	char* s1 = (char*) malloc(10);
	char* s2 = (char*) malloc(10);
	char* s3 = (char*) malloc(10);
	char* s4 = (char*) malloc(10);
	char* var;

	strcpy(s1,"ne");
	strcpy(s2,"isso");
	strcpy(s3,"que");
	strcpy(s4,"doce");

	STACK* my_stack = stack_create();
	
	printf("%p\n", stack_iter(my_stack));

	stack_push(my_stack, s1);
	stack_push(my_stack, s2);
	stack_push(my_stack, s3);
	stack_push(my_stack, s4);

	for( var = stack_iter(my_stack); var != NULL; var = stack_iter(my_stack))
	{
		printf("%s\n", var);
	}
/*
	for( var = stack_pop(my_stack); var != NULL; var = stack_pop(my_stack))
	{
		printf("%s\n", var);
	}
*/
	return 0;
}
