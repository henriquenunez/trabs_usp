#include <stdlib.h>
#include <stdool.h>
#include "mergevec.h"

void recursiveMerge(int count, int vecA[], int vecB[], int newVec[] ,bool op);

mergeVecs()
{
    int* newVec = (int*) calloc (NUM_ELE, NUM_ELE*sizeof(int));

    recursiveMerge(0, vecA, vecB, newVec, 0);

    return newVec;
}

recursiveMerge()
{
    if (op)
    {
        newVec[i] = vecA[(int)(i/2)];
        recursiveMerge(count+1, 0)
    }
    else
    {
        newVec[i] = vecA[(int)(i/2)];
        recursiveMerge(count+1, 1)
    }
}