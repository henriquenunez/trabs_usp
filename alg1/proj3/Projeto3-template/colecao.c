#include <stdlib.h>
#include "colecao.h"

#include "avl.h"
#include "list.h"

struct _no {
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura;
} ;

struct _c {
    No* inicio;
    int estrutura_id;

    void* ptr_to_data_struct;
    (void*) retrieve(int);
    (err_t) insert(void* int);
    (void) delete();
};

Colecao* cria_colecao(int estrutura_id) 
{
    // Implementar
    return NULL;
}

No* cria_no(int valor)
{
    // Implementar
    return NULL;
}

void adiciona(Colecao* c, int valor)
{
    // Implementar
}

int existe(Colecao* c, int valor)
{
    // Implementar
    return 1;
}

void destroi(Colecao* c)
{
    // Implementar
}


/*IMPLEMENTAÇÃO DE LISTA*/


/*IMPLEMENTAÇÃO DE ÁRVORE DE BUSCA BINÁRIA*/


