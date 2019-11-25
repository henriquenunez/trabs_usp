#ifndef _SHELL_SORT_PREDEF_H
#define _SHELL_SORT_PREDEF_H

#include "utils.h"
#include <math.h>

int* gen_step_vector(int length, int* steps)
{
	// 2^k -1 is the value on the vector of index i
	int k;
	int *newvec;

	k = log(length+1)/log(2);

	newvec = (int*) malloc(k * sizeof(int));

	for (int i = 1 ; i <= k ; i++)
	{
		newvec[i-1] = pow(2, i) - 1;
	}

	printf("step vector is:\n");
	printVec(newvec, k);
	*steps = k;

	return newvec;
}

/*generate last value, since it'll be divided by two*/
int gen_first_step(int length)
{
	// 2^k -1 is the value on the vector of index i
	int k;
	int *newvec;

	k = log(length+1)/log(2);
	
	return pow(2,k)-1;
}
void shell_sort_predef(int *v, int n, int top_steps)
{
	int j;
	int aux = (int)(top_steps / 2.0);


	while(aux > 0)
	{
		//printf("aux is: %d\n", aux);
		for (j = aux ; j < n ; ++j)
		{
			int k = v[j];
			int b = j;
			
			while( (b >= aux) && (v[b-aux] > k))
			{
				v[b] = v[b-aux]; b -= aux;
			}
			v[b] = k;
			//printVec(v, n);
		}
		//printVec(v, n);
		aux = (int)(aux / 2.0);
	}
}

#endif

