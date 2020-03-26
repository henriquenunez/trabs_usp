#include <stdio.h>
#include "colecao.h"

int main()
{
	Colecao* abb = cria_colecao(LISTA_ORDENADO);
	printf(".\n");
	adiciona(abb, 10);
	printf(".\n");
	adiciona(abb, 20);
	printf(".\n");
	adiciona(abb, 9) ;
	printf(".\n");
	adiciona(abb, 7) ;
	printf(".\n");
	adiciona(abb, 8) ;
	printf(".\n");
	adiciona(abb, 30);
	printf(".\n");
	adiciona(abb, 30);
	printf(".\n");
	adiciona(abb, 25);
	printf(".\n");
	adiciona(abb, 25);
	printf(".\n");
	adiciona(abb, 30);
	printf(".\n");
	adiciona(abb, 40);
	printf(".\n");
	adiciona(abb, 50);
	printf(".\n");
	adiciona(abb, 60);
	printf(".\n");
	adiciona(abb, 70);
	printf(".\n");

	printf("sera se ? %d\n", existe(abb,10));
	printf("sera se ? %d\n", existe(abb,9));
	printf("sera se ? %d\n", existe(abb,25));
	destroi(abb);
}
