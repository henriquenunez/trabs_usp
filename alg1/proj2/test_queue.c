#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

int main()
{
	char* s1 = (char*) malloc(10);
	char* s2 = (char*) malloc(10);
	char* s3 = (char*) malloc(10);
	char* var;

	strcpy(s1,"ne");
	strcpy(s2,"isso");
	strcpy(s3,"que");


	QUEUE* my_queue = queue_create();

	queue_append(my_queue, s1);
	queue_append(my_queue, s2);
	queue_append(my_queue, s3);

	for( var = queue_call(my_queue); var != NULL; var = queue_call(my_queue))
	{
		printf("%s\n", var);
		//var = queue_call(my_queue);
	}

	return 0;
}
