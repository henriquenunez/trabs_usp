#include <stdlib.h>
#include <stdio.h>

int calls = 0;

#include <bubble_sort.h>
#include <merge_sort.h>
#include <quick_sort.h>

int genRand(int* vec, int n, int my_seeds)
{
	srand(my_seeds);
	for (int i = 0; i < n; i++)
	{
		vec[i] = rand()%1000;
	}
}

int printVec(int* vec, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", vec[i]);
	printf("\n");
}

int main()
{
	long long int n;
	int seeeedrand;
	int* vec;
	scanf("%d", &seeeedrand);
	scanf("%lld", &n);
	vec = (int*) malloc(sizeof(int)* n);
	genRand(vec, n, seeeedrand);
	printVec(vec, n);

	//quick_sort(vec, 0, n-1);
	
	bubble_sort(vec, n);

	//merge_sort(vec, n);
	printVec(vec, n);
	free(vec);
	printf("recursive calls number: %d\n", calls);
	return 0;
}