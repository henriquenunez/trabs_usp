/*Bucket sort execise*/

/*Since the greatest element is 1000, we use 10 bits for comparison*/
#include <stdlib.h>
#include <stdio.h>
#include "mergesort.h"

#define MAX 1000
#define BIT_NUM 10 //number of buckets

#define OK 1;
#define OUT_OF_RANGE -1;

typedef struct vector
{
	int* arr;
	int size;
}vector_t;

int count_ones(int);
int put_into_buckets(int*);

int main()
{
	char *input = NULL;
	unsigned long int len = 0
	int *numbers;
	vector_t *buckets, input;
	buckets = (vector_t*) calloc (BIT_NUM , sizeof(vector_t));
	getline(&input, &len, stdin);
	
	put_into_buckets(buckets, )

	/*Freeing the things*/
	free(input.arr);
	for (int i = 0 ; i < BIT_NUM ; i++)
	{
		free(buckets[i].arr);
	}
	free(buckets);
	return 0;
}

int put_into_buckets(vector_t* buckets, vector_t value_array)
{
	for (int i = 0 ; i < value_array.size ; i++)
	{
		add_to_bucket(&buckets[count_ones(value_array.arr[i]) - 1],
				value_array.arr[i]);
	}
	return OK;
}

int count_ones(int input)
{
	int counter = 0;
	int temp = input;

	if (input > MAX) return OUT_OF_RANGE;
	else
	{
		for(i = 0 ; i < BIT_NUM ;  i++)
		{
			if (temp ^ 1) counter++;
			temp = temp >> 1;
		}
	}
	return counter;
}

int add_to_bucket(vector_t* bucket, int val)
{
	bucket->arr = realloc (bucket->arr, bucket->size++);
	bucket->arr[size-1] = val;

	return OK;
}

void print_buckets(vector_t* buckets)
{


}

vector_t split_input(int **num_vector, char *input)
{
	int i = 0;
	(*num_vector) = (int*) malloc (count_words(input) * sizeof(int));
	while(temp = strtok(input) != NULL)
	{
		num_vector[i] = atoi(temp);
		i++;
	}
}

int count_words(char* input)
{
	int count = 0;
	for (int i = 0 ; i < strlen(input) ; i++)
	{
		if (input[i] == ' ') count++;
	}
	return count + 1;
}

