/*BINARY SEARCH AND INTERPOLATION SEARCH*/

#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

#define mid(a,b) ((a + b)/2)

#define MAX 50
#define _span(a,b) b - a + 1
#define _interpol(val,min,max,size) (int)((float)((val-min)/(float)(max-min))*(float)(size - 1))
#define _rand_interval(a,b) rand() % (_span(a,b)) + a

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

//binary search from A to B
int* binary_search(int* vec, int a, int b, int val, int* iter_num)
{
	(*iter_num)++;
	printf("mid is %d:%d\n", mid(a,b), vec[mid(a,b)]);
	if (vec[mid(a,b)] == val)
		return vec+mid(a,b);
	if (a == b) return NULL;
	else if (vec[mid(a,b)] < val) return binary_search(vec, mid(a,b) + 1, b, val, iter_num);
	else return binary_search(vec, a, mid(a,b) - 1, val, iter_num);
}

//interpolation search
int* interpolation_search(int* vec, int a, int midpoint, int b, int min, int max, int val, int* iter_num)
{
	(*iter_num)++;
	printf("mid is %d:%d\n", midpoint, vec[midpoint]);
	if (vec[midpoint] == val) return vec+midpoint;
	if (midpoint == a || midpoint == b) return NULL;
	if (vec[midpoint] < val) return interpolation_search(vec, midpoint+1, _interpol(val, vec[a], vec[b], _span(a,b)), b, min, max, val, iter_num);
	else return interpolation_search(vec, a, _interpol(val, vec[a], vec[b], _span(a,b)), midpoint-1, min, max, val, iter_num);
}

int main()
{
	int *init_vec, size, min, max, *found_pos, val_we_want, iterations;
	printf("Insert size:\n");
	scanf("%d", &size);
	printf("Insert min value:\n");
	scanf("%d", &min);
	printf("Insert max value:\n");
	scanf("%d", &max);
	printf("Insert wanted val:\n");
	scanf("%d", &val_we_want);
	init_vec = genvec(size, min, max);
	printvec(init_vec, size);
	mergeSort(init_vec, size);	
	printvec(init_vec, size);
	//Vector sorted

	//Binary search
	iterations = 0;
	found_pos = binary_search(init_vec, 0, size-1, val_we_want, &iterations);
	printf("B found at: %p, iterations: %d\n", found_pos, iterations);

	//Interpolation search
	iterations = 0;
	found_pos = interpolation_search(init_vec, 0, mid(0, size-1), size-1, min, max, val_we_want, &iterations);
	printf("I found at: %p, iterations: %d\n", found_pos, iterations);

	free(init_vec);

	return 0;
}

