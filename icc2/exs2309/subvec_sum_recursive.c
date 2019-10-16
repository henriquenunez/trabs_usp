#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOW_NUM -0x3f3f3f

/*
#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define RAND_MAX 200
*/

int max(int a, int b)
{
	if (a > b) return a;
	else return b;
}

int subvec_sum(int* base_pointer, int* last_pointer, void (*printfunc)(int*,  int*))
{
	int sum;
	
	//printfunc(base_pointer, last_pointer);

	if (base_pointer == last_pointer) 
	{
		sum = base_pointer[0];
		//printf("sum is: %d\n", sum);
		return sum;
	}

	sum = max(	base_pointer[0],
				max(
					base_pointer[0] + subvec_sum(base_pointer+1, last_pointer, printfunc),
					subvec_sum(base_pointer + 1, last_pointer, printfunc)
					));
	
	//printf("sum is: %d\n", sum);

	return sum;
}

int* genRand(int n)
{
	int* newVec = (int*) malloc (sizeof(int)*n);
	do
	{	
		if (rand()%2)
			newVec[n-1] = rand() % 100;
		else 
			newVec[n-1] = -1 * (rand() % 100);
	}while(n--);
	return newVec;
}

void printVec(int vec[], int* end)
{
	for (int i = 0; vec + i <= end; ++i)
	{
		printf("%d ", vec[i]);
	}
	printf("\n");
}

int main()
{
	srand(time(0));

	int* vec, n;
	scanf("%d", &n);

	vec = genRand(n);
	printVec(vec, vec + n - 1);

	printf("subvec_sum: %d\n", subvec_sum(vec, vec+(n-1), printVec));

}