#ifndef _UTILS_H_
#define _UTILS_H_

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

#endif

