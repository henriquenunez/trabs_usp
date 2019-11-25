#include <stdio.h>
#include <stdlib.h>

void printVec(int vec[], int lowerBound, int upperBound)
{
	for (int i = lowerBound ; i <= upperBound ; i++)
		printf("%d ", vec[i]);
	printf("\n");
}


void insertionSort(int vec[], int lowerBound, int upperBound) 
{ 
    int i, key, j; 
    for (i = lowerBound + 1; i < upperBound + 1; i++) { 
        key = vec[i]; 
        j = i - 1; 

        while (j >= lowerBound && vec[j] > key) { 
            vec[j + 1] = vec[j]; 
            j = j - 1; 
        } 
        vec[j + 1] = key; 
    }
} 

void merge(int vec[], int lowerBound, int upperBound, int k)
{
	int mid = (lowerBound + upperBound) / 2;
	//printf("bounds: %d %d\n", lowerBound, upperBound);
	if (upperBound + 1 - lowerBound > k)
	{
		merge(vec, lowerBound, mid, k);
		merge(vec, mid+1, upperBound, k);
	}
	insertionSort(vec, lowerBound, upperBound);
    	printVec(vec, lowerBound, upperBound); 
}

int main()
{
	int *vec, size, k;

	scanf("%d", &size);
	vec = (int*) malloc(sizeof(int) * size);

	for (int i = 0 ; i < size ; i++)
		scanf("%d", &vec[i]);
	//printVec(vec, size);

	scanf("%d", &k);
	merge(vec, 0, size-1, k);
	free(vec);
}

