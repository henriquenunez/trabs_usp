#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>

float peri(int h , int w){
    return (2 * h + 2 * w);
}

float area(int h , int w){
    return h * w;
}

float diag(int h , int w){
    return sqrt(h*h + w * w);
}

void gera_geral(){

}

int main(){

int n_rec , sementinha;

scanf("%d%d" , &n_rec , &sementinha);

srand(sementinha);
float val_rec[n_rec][2];
float res_peri[n_rec];
float res_area[n_rec];
float res_diag[n_rec];


printf("chegay\n");

#pragma omp parallel for
    for(int a = 0 ; a < n_rec ; a++)
    {
        val_rec[a][0] = (rand() % 1000) / 10; //base
        val_rec[a][1] = (rand() % 1000) / 10; //altura
    }

    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                for (int a = 0 ; a < n_rec ; a++)
                {
                res_peri[a] = peri(val_rec[a][0] , val_rec[a][1]);
                printf("peri %d %f\n" , a , res_peri[a]);
                }
            }
            
            #pragma omp section
            {
                for (int a = 0 ; a < n_rec ; a++){    
                res_area[a] = area(val_rec[a][0] , val_rec[a][1]);
                printf("area %d %f\n", a , res_area[a]);
                }
            }
            
            #pragma omp section
            {
                for (int a = 0 ; a < n_rec ; a++)
                {
                res_diag[a] = diag(val_rec[a][0] , val_rec[a][1]);
                printf("diag %d %f\n", a , res_diag[a]);
                }
            }
        }
    }

return 0;
}