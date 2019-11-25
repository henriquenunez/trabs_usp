#include <stdlib.h>
#include "colecao.h"

#include "defines.h"

struct _no {
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura;
} ;

struct _c {
    int estrutura_id;
    No* inicio; 

    void* estrutura;
    int (*adiciona)(void*, int, No*);
    int   (*existe)(No*, int);
    void  (*destroi)(void*);
};

typedef struct _abb ABB;
typedef struct _avl AVL;

/*PROTOTIPOS DE FUNÇÕES*/

void no_libera(No* esse_no);
int a_pos_ordem(No* no_raiz, void (*exec)(No*));

/*ABB*/

ABB* abb_criar();
int abb_insere(void*, int, No*);
void abb_libera(void*);

/*BUSCA EM ARVORE*/

int arvore_busca(No*, int);

/*FUNÇÕES EXPOSTAS*/

Colecao* cria_colecao(int estrutura_id) 
{
    Colecao* nova_colecao = (Colecao*) malloc (sizeof(Colecao));

    switch(estrutura_id)
    {
	case LISTA_ORDENADO:
	    return NULL;
	    break;
	case LISTA_ULTIMO:
	    return NULL;
	    break;
	case LISTA_PRIMEIRO:
	    return NULL;
	    break;
	case ARVORE_BINARIA:
	    nova_colecao->estrutura_id = ARVORE_BINARIA;

	    nova_colecao->estrutura = abb_criar();
	    nova_colecao->adiciona = abb_insere;
	    nova_colecao->existe = arvore_busca;
	    nova_colecao->destroi = abb_libera;

	    break;
	case ARVORE_AVL:
	    break;
	default:
	    return NULL;
    }

    return nova_colecao;
}

No* cria_no(int valor)
{
    No* novo_no = (No*) calloc (1, sizeof(No));
    novo_no->valor = valor;

    return novo_no;
}

void adiciona(Colecao* c, int valor)
{
    No* novo_no = cria_no(valor);

    if (c->adiciona(c->estrutura, valor, novo_no) != SUCESSO) 
	free(novo_no);
}

int existe(Colecao* c, int valor)
{
    return c->existe(c->inicio, valor);
}

void destroi(Colecao* c)
{
    // Implementar
}


/*IMPLEMENTAÇÃO DE LISTA*/


/*IMPLEMENTAÇÃO DE ÁRVORE DE BUSCA BINÁRIA*/

struct _abb
{
	No* raiz;
};

ABB* abb_criar()
{
	ABB* nova_arvore = (ABB*) calloc (1, sizeof(ABB));
	return nova_arvore;
}

int __abb_insere(No** no_raiz, int valor, No* esse_no)
{
	if (esse_no == NULL) return ERRO;
	if ((*no_raiz) == NULL)
	{
		(*no_raiz) = esse_no;
		return SUCESSO;
	}
	if ((*no_raiz)->valor == valor) return EXISTE;

	//se o valor atual é maior que o valor que inserimos, insere à esquerda dele
	if ((*no_raiz)->valor > valor)
		return __abb_insere(&(*no_raiz)->esq, valor, esse_no);
	//caso contrário, insere à direita
	else
		return __abb_insere(&(*no_raiz)->dir, valor, esse_no);
}

int abb_insere(void* essa_arvore, int valor, No* esse_no)
{
	return __abb_insere(&((ABB*)essa_arvore)->raiz, valor, esse_no);
}

void abb_libera(void* essa_arvore)
{
	a_pos_ordem(((ABB*)essa_arvore)->raiz, no_libera);
}

/*IMPLEMENTAÇÃO DE ÁRVORE AVL*/

struct _avl
{
	No* raiz;
};

int avl_libera(AVL* essa_arvore)
{
	a_pos_ordem(essa_arvore->raiz, no_libera);
}

/*BUSCA EM ARVORE*/

int arvore_busca(No* esse_no, int valor)
{
	if (esse_no == NULL) return INEXISTE;
	
	if (esse_no->valor == valor) return valor;

	if (esse_no->valor < valor) return arvore_busca(esse_no->dir, valor);
	else return arvore_busca(esse_no->esq, valor);
}

/*CAMINHAMENTO PÓS ORDEM*/

int a_pos_ordem(No* no_raiz, void (*exec)(No*))
{
	if(no_raiz->esq != NULL)
	{
		a_pos_ordem(no_raiz->esq, exec);
	}

	if(no_raiz->dir != NULL)
	{
		a_pos_ordem(no_raiz->dir, exec);
	}

	exec(no_raiz);
}

/*DESALOCA NÓ*/

void no_libera(No* esse_no)
{
	free(esse_no);
}
