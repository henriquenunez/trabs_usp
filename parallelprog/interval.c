#include <stdio.h>
#include <omp.h>
#define n_fim 10000000000

int main(){

	long long soma = 0;
	long long  a;
	//scanf("%d" , &n_fim);
#pragma omp parallel for private(a) schedule(dynamic , 1000000) reduction(+:soma)
	for (a = 0 ; a < n_fim ; a++){
		soma += a;
	}

	return 0;
}
