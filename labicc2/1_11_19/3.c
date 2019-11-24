//BUCKETSORT BASED ON COUNTSORT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 50
#define _span(a,b) b - a + 1

#define _rand_interval(a,b) rand() % (_span(a,b)) + a


/*Span A->B*/
int* countsort(int* in_vec, int size, int a, int b)
{
	int* count_vec = (int*) calloc (_span(a,b), sizeof(int));

	for (int i = 0 ; i < size ; i++)
		count_vec[in_vec[i]]++;

	return count_vec;
}

int* genvec(int size, int a, int b)
{
	int* new_vec = (int*) malloc (size * sizeof(int));
	for (int i = 0 ; i < size ; i++)
		new_vec[i] = _rand_interval(a,b);

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
	printf("\n", counter);
}

int main()
{

	int *init_vec, *sorted_vec, size, a, b;
	scanf("%d", &size);
	scanf("%d", &a);
	scanf("%d", &b);
	init_vec = genvec(size, a, b);
	printvec(init_vec, size);
	sorted_vec = countsort(init_vec, size, a, b);	
	printvec(sorted_vec, _span(a,b));

	return 0;
}


