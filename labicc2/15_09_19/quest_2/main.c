//main.c

#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int* genRand(int size)
{
    int* vec = (int*) malloc (size * sizeof(int));
    for (int i = 0 ; i < size ; i++)
        vec[i] = rand()%6969;
    return vec;
}

void printVec(int* vec, int len)
{
    for (int i = 0 ; i < len ; i++)
        printf("%d ", vec[i]);
    printf("\n");
}

int main()
{
    int* a;
    int sizea;

    scanf("%d", &sizea);

    a = genRand(sizea);

    printVec(a, sizea);
    
    mergeSort(a, sizea-1);

    printVec(a, sizea);

    return 0;
}