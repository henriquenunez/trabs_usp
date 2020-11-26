#include "omp.h"
#include "stdio.h"
#include "stdlib.h"
#define oi 1000000

int main(){
    int vec[oi];
    long long sum = 0 , i;

for(int a = 0 ; a < oi ; a++)
    vec[a] = (rand() % 22831);

#pragma omp parallel for private(i) //reduction(+:sum)
    for(i = 0 ; i < oi ; i++)
        #pragma omp atomic
            sum += vec[i];
printf("%lld" , sum);

}