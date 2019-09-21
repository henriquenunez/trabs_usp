#include <stdlib.h>
#include <stdio.h>
#include "mergevec.h"

struct _finishParams
{
    int from;
    int to;
    int start;
};

void finishInsertion(finishParams finishParams, int vecSrc[], int vecDest[]);

int* mergeVecs(int vecA[], int vecB[], int sizeA, int sizeB)
{

    #define NUM_ELE sizeA + sizeB
    
    int* newVec = (int*) calloc (NUM_ELE, NUM_ELE*sizeof(int));
    int countA = 0;

    finishParams params;

    for (int i = 0 ; i < NUM_ELE ; i++){

        if (countA >= sizeA)
        {
            printf("A!\n");
            params.from = i;
            params.to = NUM_ELE - 1;
            params.start = (int)(i/2)+(i%2);
            finishInsertion(params, vecB, newVec);
            return newVec;
        }
        if (NUM_ELE - countA < sizeB)
        {
            printf("B!\n");
            params.from = i;
            params.to = NUM_ELE - 1;
            params.start = (int)(i/2);
            finishInsertion(params, vecA, newVec);
            return newVec;
        }

        if (i % 2)
        {
            newVec[i] = vecA[(int)(i/2)];
            ++countA;
        }
        else
        {
            newVec[i] = vecB[(int)(i/2)+(i%2)];
        }

    }

    #undef NUM_ELE
    return newVec;
}

void finishInsertion(finishParams finishParams, int vecSrc[], int vecDest[])
{

    for (int i = finishParams.from; i <= finishParams.to ; i++)
    {
        vecDest[i] = vecSrc[finishParams.start + (i - finishParams.from)];
    }
   
}