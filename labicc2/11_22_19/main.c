#include <stdlib.h>
#include <stdio.h>

#include "shell_sort.h"
#include "utils.h"

int myvec[] = {1,1,2,7,5,3,0,0}, mylen = 8;

int main()
{
	long long int n;
	int seeeedrand;
	int* vec;
	scanf("%d", &seeeedrand);
	scanf("%lld", &n);
	vec = (int*) malloc(sizeof(int)* n);
	printVec(vec, n);

	shell_sort(myvec, mylen);
	
	printVec(vec, n);
	return 0;
}
