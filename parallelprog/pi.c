/* Authors: Tim Mattson and Larry Meadows, Intel Engineers*/

#include "stdio.h"
#include "stdlib.h"
#include "omp.h"

static long num_steps = 1000000000;

double step;

int main () {
    int i; double x, pi, sum = 0.0;
    step = 1.0/(double) num_steps;

#pragma omp parallel for private(i , x) schedule(static) reduction(+:sum)
    for (i=0 ; i < num_steps ; i++){
        x = (i + 0.5) * step; // Largura do retângulo
        sum = sum + 4.0/(1.0 + x*x); // Sum += Área do retângulo
    }

    pi = step * sum;

    printf("Valor de Pi: %.100f\n", pi);
}
