#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>

using namespace std;

#define MAX_TEX 260000
#define MAX_PAD 1000

char texto[MAX_TEX+1], padrao[MAX_PAD+1];
long int b[MAX_PAD+10];

void kmpPreProcess(long int padraoTam)
{
	long int i = 0;
	long int j = -1;
	b[0] = -1;
	while(i < padraoTam)
	{
		while(j>=0 && padrao[i] != padrao[j])
			j = b[j];
		i++;
		j++;
		b[i] = j;
	}
}

void kmpSearch(long int padraoTam, long int textoTam)
{
	long int i = 0, j = 0;
	while(i < textoTam)
	{
		while(j>=0 && texto[i] != padrao[j])
			j = b[j];
		i++;
		j++;
		if(j == padraoTam){
			printf("O padrao foi encontrado na posicao %ld\n", i-j);
			j = b[j];
		}
	}
}

int main(){
	scanf("%s", texto);
	scanf("%s", padrao);
	
	long int textoTam = strlen(texto);
	long int padraoTam = strlen(padrao);
	
	kmpPreProcess(padraoTam);
	kmpSearch(padraoTam, textoTam);
	
	return 0;
}
