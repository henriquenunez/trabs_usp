//COUNTSORT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 50

int* countsort(int* in_vec, int size)
{
	int* count_vec = (int*) calloc (MAX, sizeof(int));

	for (int i = 0 ; i < size ; i++)
		count_vec[in_vec[i]]++;

	return count_vec;
}

int* genvec(int size, int max)
{
	int* new_vec = (int*) malloc (size * sizeof(int));
	for (int i = 0 ; i < size ; i++)
		new_vec[i] = rand() % max;

	return new_vec;
}

void printvec(int* vec, int size)
{
	int counter = 0;
	for (int i = 0 ; i < size ; i++)
	{
		printf("%d ", vec[i]);
		counter += vec[i];
	}
	printf("\ncount %d elements\n", counter);
}

int main()
{
	int *init_vec, *sorted_vec, size;
	scanf("%d", &size);
	init_vec = genvec(size, MAX);
	printvec(init_vec, size);
	sorted_vec = countsort(init_vec, size);	
	printvec(sorted_vec, MAX);

	return 0;
}


