nclude <stdio.h>
#include <stdlib.h>

int fatorial_duplo(int N){
    if (N >= 1){
        if(N % 2) return N * fatorial_duplo(N-1); //
        else return fatorial_duplo(N-1);
    }
    else return 1;
}

int main(int argv, char **argc){
    int N;
    scanf("%d", &N);
    printf("%d\n ", fatorial_duplo(N));
}
