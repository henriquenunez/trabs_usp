//numeros perfeitos
#include <stdio.h>


int main(){

    int a;
    //unsigned int index = 0;
    int b_1;
    int b_2;

#pragma omp parallel for private(a , b_1 , b_2)
    for ( a = 1 ; a<100000 ; a++ ){ //número perfeito máximo que queremos alcancar
        b_2 = 0; //soma dos divisores
        b_1 = a;    //buffer para rodas as iteracoes
        
        while(--b_1){        //verifica os numeros que sao possíveis divisores
            if (a % b_1 == 0){
        //        printf("deubom\n");
                b_2 += b_1;
            }
        }
        
        //printf("deumuitobom\n");
        if (b_2 == a)
            printf("%d\n" , a);
    }
    return 42;
}
