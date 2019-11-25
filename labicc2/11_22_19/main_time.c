#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "shell_sort.h"
#include "shell_sort_predef.h"
#include "utils.h"

clock_t time_init, time_end;

int main()
{
	long long int n;
	int seeeedrand;
	int* vec;
	int* step_vec;
	
	scanf("%d", &seeeedrand);
	scanf("%lld", &n);
	vec = (int*) malloc(sizeof(int)* n);
	genRand(vec, n, seeeedrand);
	//printVec(vec, n);

	int first_step = gen_first_step(n);

	time_init = clock();
	shell_sort_predef(vec, n, first_step);
	time_end = clock();

	printf("time is(predef): %lf\n", (double)(time_end-time_init)/(double)CLOCKS_PER_SEC);

	time_init = clock();
	shell_sort(vec, n);
	time_end = clock();

	printf("time is(not_predef): %lf\n", (double)(time_end-time_init)/(double)CLOCKS_PER_SEC);

	//printVec(vec, n);
	free(vec);
	
	return 0;
}
