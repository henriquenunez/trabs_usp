#include <stdio.h>

#define ll long long

ll int gcd(ll int a , ll int b){
	if(b==0) return a;
	return gcd(b , a%b);
}

ll int hcf(ll int a , ll int b){
	return (a*b)/gcd(a,b);
}
int main(){
	ll int buff=1 , target=20;
	for (int i = 1 ; i <= target ; i++){
		buff = hcf(i , buff);
	}
	printf("%lld" , buff);
}
