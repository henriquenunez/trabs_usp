#include <math.h>
#include <stdio.h>
#include <stdbool.h>
//
//program for finding the largest prime factor of a number
//
const long long int target = 600851475143;

bool check_prime(long long int num){
//	printf("re-testing: %lld\n" , num);
	for (int j = 2 ; j*j < num ; j++){
//		printf("re-re-testing: %d\n" , j);
		if(num%j == 0){
			return false;
		}
	}
	return true;
}

void find_div(){
	for(long long int i = 2 ; i < target ; i++){
		if (target % i == 0){
//			printf("testing: %lld\n" , i);
			if(check_prime(target/i)){
				printf("%lld\n" , target/i);
				return;
			}
		}
	}

}

int main(){
//	if(check_prime(23)) printf("is das so?\n");

	find_div();
	return 0;
}
