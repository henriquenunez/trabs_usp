#include <stdio.h>
#include <stdlib.h>
#include "mergevec.h"

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
        printf("%d\n", vec[i]);
    printf("\n");
}

int getRead()
{
    int var;
    scanf("%d", &var);
    return var;
}

int main()
{
    int* a;
    int sizea;
    int* b;
    int sizeb;


    scanf("%d", &sizea);
    scanf("%d", &sizeb);

    a = genRand(sizea);
    b = genRand(sizeb);

    printVec(a, sizea);
    printVec(b, sizeb);
    
    int* newVec = mergeVecs(a, b, sizea, sizeb);
    printVec(newVec, sizea+sizeb);

    return 0;
}