#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "mergevec.h"

/*
*Bitmasks for selection and 
*for storing whether Vector A or B
*has finished
*/

#define VEC_SEL            1  // 2^0, bit 0
#define VEC_A_FINISHED     2  // 2^1, bit 1
#define VEC_B_FINISHED     4  // 2^2, bit 2

void recursiveMerge(int count,
					int countA, 
					int posA,
					int vecA[], 
					int vecB[], 
					int newVec[], 
					unsigned char op, 
					int max);

int* mergeVecs(int vecA[], int vecB[], int sizeA, int sizeB)
{
    #define NUM_ELE sizeA + sizeB
    int* newVec = (int*) calloc (NUM_ELE, NUM_ELE * sizeof(int));

    recursiveMerge(0, sizeA, 0, vecA, vecB, newVec, 0, NUM_ELE);

    return newVec;
}

void recursiveMerge(int count,
					int sizeA,
					int posA, 
					int vecA[], 
					int vecB[], 
					int newVec[], 
					unsigned char op, 
					int max)
{
    if (count >= max) return; //in case the maximum size has been reached

    if ( !(op & VEC_A_FINISHED) && ((int)count/2) >= sizeA)
    {
    	op ^= VEC_A_FINISHED; //if size A has been reached, toggles the bit
    }
    
    if ( !(op & VEC_B_FINISHED) & ((int)count/2) >= max-sizeA)
    {
    	op ^= VEC_B_FINISHED; //if size B has been reached, toggles the bit
    }

    //   vector B finished***********sees if the selection or finish vector bits are on
    if ( (op & VEC_B_FINISHED) ? 0 : op & (VEC_SEL | VEC_A_FINISHED) )
    {
    	newVec[count] = vecB[count-posA];
    	if (op & VEC_A_FINISHED) 
    	{
        	recursiveMerge(count+1, sizeA, posA, vecA, vecB, newVec, op ^ VEC_SEL, max);
        }
        else 
        {
        	recursiveMerge(count+1, sizeA, posA, vecA, vecB, newVec, op ^ VEC_SEL, max);
        }
        
        //recursiveMerge(count+1, sizeA, posA+1, vecA, vecB, newVec, op ^ VEC_SEL, max);
    }
    else
    {
        newVec[count] = vecA[posA];
    	if (op & VEC_B_FINISHED)
    	{
    		recursiveMerge(count+1, sizeA, posA+1, vecA, vecB, newVec, op ^ VEC_SEL, max);
    	}
        else
        {
        	recursiveMerge(count+1, sizeA, posA+1, vecA, vecB, newVec, op ^ VEC_SEL, max);
        }
        //recursiveMerge(count+1, sizeA, vecA, vecB, newVec, op ^ VEC_SEL, max);
    }
}