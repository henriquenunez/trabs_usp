#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"

#include <math.h>

int main()
{
	char* buffer = NULL; //input buffer
	unsigned long int l = 0; //length
	float result;

	//printf("got %ld characters\n", getline(&buffer, &l, stdin) );
	getline(&buffer, &l, stdin);
	result = make_things_work(buffer);	
	
	if (!isinf(result))
		printf("O resultado da operação é %.2f.\n", result);
	else
		printf("Não foi possível realizar a operação.\n");

	free(buffer);
	return 0;
}
