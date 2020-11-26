#include <stdio.h>
#include <omp.h>
#include <math.h>
#define interacoes 500000

int main() {

	int arr1[interacoes];
	int arr2[interacoes];
	int arr3[interacoes];
#pragma omp parallel for schedule(static)

	for (int i = 0 ; i <= interacoes ; i++){
//		printf("%d" , i);
		arr1[i] = i%2;
		arr2[i] = i%11; 
		arr3[i] = (arr1[i] + arr2[i]);
	}

	return 0;
}
