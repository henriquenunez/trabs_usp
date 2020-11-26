#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 700000

int main(int argc,char **argv) {
    int i, j;
    int quant_num_perfeitos=0; //Armazenada a quantidade de números perfeitos encontrados
    int num_perfeitos[100]; //Vetor para armazenar os números perfeitos
    int soma;

#pragma omp parallel for schedule(dynamic) private(i , j , soma) /*todas essas variaveis devem ser privadas*/
    for (i = 1; i < MAX; i++){
        soma = 0;
    
        for (j = 1; j < i; j++){
            if(i%j == 0){
                soma += j;
            }
    }
        if (soma == i){
            #pragma omp critical //essa e a regiao critica do programa, pois varias threads tentarao acessar uma variavel que deve imprescindivelmente ser global
            {
            num_perfeitos[quant_num_perfeitos]=i; 
            quant_num_perfeitos++;
            }
        }
    }
    
    printf("Quantidade de nrs perfeitos = %d \n", quant_num_perfeitos);
    for(i=0;i<quant_num_perfeitos;i++){
        printf("%d ",num_perfeitos[i]);
    }
    printf("\n");
    return 0;
}
