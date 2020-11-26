#include <stdio.h>
#include <omp.h>
#define n_fim 10000000000
#define thread_num numero_da_thread
#define end 11
#define init 0

int main(){

	
	//long long soma = 0;
	//long long  a;
	//scanf("%d" , &n_fim);
//#pragma omp parallel for private(a) schedule(dynamic , 1000000) reduction(+:soma)
	int interval , resto , maximo_de_threads;
	//scanf("%d%d" , init , end);//numero inicial e final do intervalo
	maximo_de_threads = omp_get_max_threads();
	resto = (end - init) % maximo_de_threads;
	//printf("resto %d\n" , resto);
	interval = (end - init) / maximo_de_threads;
	//printf("interval %d\n" , interval)
	int madu = 0; //a melhor variavel que voce vai ver
	int soma[maximo_de_threads];

#pragma omp parallel num_threads(maximo_de_threads)
{
	int numero_da_thread = omp_get_thread_num();
	int fim , ini;

	ini = interval * thread_num;
	soma[thread_num] = 0;

	if(thread_num == (maximo_de_threads - 1)){
		fim = interval * (thread_num + 1) + resto;
	}else{
		fim = interval * (thread_num + 1);
	}

		for(int i = ini ; i < fim; i++ ){
			soma[thread_num] += i;
		}
}

for (int b = 0; b < maximo_de_threads ; b++)
	madu += soma[b]; printf("%d\n" , madu);
return 0;
}