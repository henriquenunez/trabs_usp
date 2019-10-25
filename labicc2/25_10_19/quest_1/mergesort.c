#include "mergesort.h"
#include <stdlib.h>
#include <stdio.h>

void divide_and_conquer(int* vec, int begin, int end);
void sort(int* vec, int begin, int midpoint, int end);

int mergeSort(int* vec, int size)
{
	divide_and_conquer(vec, 0, size-1);
}

/*begin -> inclusive
  end   -> inclusive*/
void divide_and_conquer(int* vec, int begin, int end)
{	
	if (begin >= end) return; /*our base case*/

	/* It's okay to use this divison, because the right part
	midpoints will always be +1 this midpoint
	*/

	#define MIDPOINT ((end + begin)/2)

	divide_and_conquer(vec, begin, MIDPOINT);
	divide_and_conquer(vec, MIDPOINT+1, end);

	sort (vec, begin, MIDPOINT, end);

	#undef MIDPOINT
}

void sort(int* vec, int begin, int midpoint, int end)
{
	int* newVec = (int*) malloc ((end - begin+1) * sizeof(int));
	//printf("size %d\n", (end - begin));
	//int newVec[200];

	int walk1  =  begin;
	int walk2  =  midpoint+1;
	int walkVec = 0;

	while(walk1 <= midpoint && walk2 <= end)
	{
		if(vec[walk1] < vec[walk2])
		{
			newVec[walkVec] = vec[walk1];
			++walk1;
		}
		else
		{
			newVec[walkVec] = vec[walk2];
			++walk2;
		}
		++walkVec;
	}

	while (walk1 <= midpoint)
	{
		newVec[walkVec] = vec[walk1];
		++walk1;
		++walkVec;
	}
	
	while(walk2 <= end)
	{
		newVec[walkVec] = vec[walk2];
		++walk2;
		++walkVec;
	}

	for (int i = begin; i < (begin + walkVec); i++)
	{
		vec[i] = newVec[i-begin];
	}

	free(newVec);
}
