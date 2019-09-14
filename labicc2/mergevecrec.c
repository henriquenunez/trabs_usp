#include <stdlib.h>
#include <stdbool.h>
#include "mergevec.h"

#define VEC_SEL            1  // 2^0, bit 0
#define VEC_A_FINISHED     2  // 2^1, bit 1
#define VEC_B_FINISHED     4  // 2^2, bit 2

void recursiveMerge(int count, int vecA[], int vecB[], int newVec[], unsigned char op, int max);

int* mergeVecs(int vecA[], int vecB[], int sizeA, int sizeB)
{
    #define NUM_ELE sizeA + sizeB
    int* newVec = (int*) calloc (NUM_ELE, NUM_ELE * sizeof(int));

    recursiveMerge(0, vecA, vecB, newVec, 0, NUM_ELE);

    return newVec;
}

void recursiveMerge(int count, int vecA[], int vecB[], int newVec[], unsigned char op, int max)
{
    if (count >= max) return;
    if ( ( ( (op) & VEC_SEL ) | VEC_A_FINISHED) & ~VEC_B_FINISHED)
    {
        newVec[count] = vecB[(int)(count/2)];
        recursiveMerge(count+1, vecA, vecB, newVec, op ^ VEC_SEL, max);
    }
    else
    {
        newVec[count] = vecA[(int)(count/2)];
        recursiveMerge(count+1, vecA, vecB, newVec, op ^ VEC_SEL, max);
    }
}