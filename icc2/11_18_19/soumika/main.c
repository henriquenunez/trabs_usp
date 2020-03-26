#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int check_even(int a);
int* strtoint(char* input_string);
int* soumika (int* vector, int size);
void print_vec(int vec[], int size);

int main()
{
	//char* input = NULL;
	char input[100];
	unsigned long int len = 0;
	int* int_vec;
	int* count_vec;

	//getline(&input, &len, stdin);
	//printf("%lu:%s", len, input);
	scanf("%s", input);
	len = strlen(input);
	//printf("\n");
	int_vec = strtoint(input);
	//print_vec(int_vec, len);
	//printf("\n");
	count_vec = soumika(int_vec, len);
	print_vec(count_vec, len);

	//free(input);
	free(int_vec);
	free(count_vec);
}

int* soumika (int* vector, int size)
{
	int *ret_vec = (int*) calloc (1, (size+1) * sizeof(int));
//	ret_vec[size] = 0;

	for (int i = size-1 ; i >= 0 ; i--)
	{
		ret_vec[i] = ret_vec[i+1] + check_even(vector[i]);
	}
	return ret_vec;
}

int* strtoint(char* input_string)
{
	//works only with numbers

	int* ret_vec = (int*)
		malloc (sizeof(int) * strlen(input_string));

	for (int i = 0 ; i < strlen(input_string) ; i++)
		ret_vec[i] = input_string[i] - 0x30;

	return ret_vec;
}

int check_even(int a)
{
	if (a & 1) return 0; //not even
	else return 1; //even
}

void print_vec(int vec[], int size)
{
	for (int i = 0 ; i < size ; i++)
		printf("%d ",vec[i]);
	printf("\n");
}

