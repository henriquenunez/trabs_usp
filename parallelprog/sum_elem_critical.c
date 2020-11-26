#include "omp.h"
#include "stdio.h"

int main(){
    int vec[8] = {3 , 6 , 5 , 2 , 4 , 6 , 3 , 2};
    int sum = 0 , i;

#pragma omp parallel for private(i) //rodar o for paralelo
    for(i = 0 ; i < 8 ; i++)
        #pragma omp critical
            sum += vec[i]; //realiza a soma de maneira sequencial

printf("%d" , sum);

return 0;
}