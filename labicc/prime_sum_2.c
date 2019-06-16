#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

const int target = 2000000;

void sieve(bool* cont){
	for(int i = 2 ; i <= target ; i++){
//		printf("%d:" , i);
//		printf("%d\n" , cont[i]);	
		if(cont[i]){
			for (int j = 2*i ; j < target ; j +=i){
//				printf("%d is now 0.\n" , j);
				cont[j]=0;
			}
		}
	}
}

int main(){

	long long int sum = 0;
	
	bool container[target+1];
	memset(container , 1 , (target+1));
	sieve(container);

	for (int i = 2 ; i < target ; i++){
		if (container[i]){
//			printf("yay:%d\n" , i);
			sum+=i;
		}
	}

	printf("%lld\n" , sum);

}
