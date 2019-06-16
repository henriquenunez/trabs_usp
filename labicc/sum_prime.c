#include <stdio.h>

const int target = 1000;

int main(){
	long long int sum = 0;

	for (int i = 3 ; i < target ; i+=3){
//		printf("%d %d" ,sum , i);
		sum+=i;
	}
	
	for (int i = 5 ; i < target ; i+=5){
//		printf("%d %d" ,sum , i);
		if(i%3 == 0) continue;
		sum+=i;
	}

	printf("%lld\n" , sum);
}
