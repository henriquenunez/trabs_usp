#ifndef _SHELL_SORT_H
#define _SHELL_SORT_H

#include "utils.h"
#include <math.h>

void shell_sort(int *v, int n)
{
	int j;
	int aux = (int)(n / 2.0);


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

