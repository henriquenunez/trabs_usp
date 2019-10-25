//main.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mergesort.h"

int* genRand(int size)
{
    int* vec = (int*) malloc (size * sizeof(int));
    for (int i = 0 ; i < size ; i++)
        vec[i] = rand()%15;
    return vec;
}

void printVec(int* vec, int len)
{
    for (int i = 0 ; i < len ; i++)
        printf("%d ", vec[i]);
    printf("\n");
}

int findQuantOnVec(int* vec, int size, int x)
{
    int i = 0, j = size-1;

    while(i < j)
    {
    	if (vec[i] + vec[j] == x) return 1;
	else if (vec[i] + vec[j] > x) j--;
	else i++;
    }
    return 0;
}


int main()
{
    int* a; /*our vector*/
    int sizea; /*its size*/
    int x; /*amount to be found my sum*/

    srand(time(NULL));

    scanf("%d %d", &x, &sizea);
    a = genRand(sizea);
    printVec(a, sizea);
    
    mergeSort(a, sizea);
    printVec(a, sizea);

    printf("%s %d on vector\n", findQuantOnVec(a, sizea, x) ? "Can find" : "Can't find", x);

    return 0;
}
