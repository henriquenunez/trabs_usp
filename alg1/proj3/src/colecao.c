#include <stdlib.h>
#include "colecao.h"

#include "defines.h"

struct _no {
    int valor;
    struct _no* esq;
    struct _no* dir;
    int altura;
};

struct _c {
    int estrutura_id;
    No* inicio; 

    void* estrutura;
    No* (*adiciona)(void*, int, No*, int*);
    int   (*existe)(No*, int);
    void  (*destroi)(void*);
};

typedef struct _lista LISTA;
typedef struct _abb ABB;
typedef struct _avl AVL;

/*PROTOTIPOS DE FUNÇÕES*/

/*COMUM*/

void no_libera(No* esse_no);

/*LISTAS*/

LISTA* lista_criar();
No* lista_insere_inicio(void*, int, No*, int*);
No* lista_insere_final(void*, int, No*, int*);
No* lista_insere_ordenado(void*, int, No*, int*);
int lista_busca(No*, int);
void lista_libera(void*);

/*ARVORES*/

void a_pos_ordem(No* no_raiz, void (*exec)(No*));
int arvore_busca(No*, int);

/*ABB*/

ABB* abb_criar();
No* abb_insere(void*, int, No*, int*);
void abb_libera(void*);

/*AVL*/

AVL* avl_criar();
No* avl_insere(void*, int, No*, int*);
void avl_libera(void*);

/*FUNÇÕES EXPOSTAS*/

Colecao* cria_colecao(int estrutura_id) 
{
    Colecao* nova_colecao = (Colecao*) malloc (sizeof(Colecao));

    switch(estrutura_id)
    {
	case LISTA_ORDENADO:
	    nova_colecao->estrutura_id = LISTA_ORDENADO;

	    nova_colecao->estrutura = lista_criar();
	    nova_colecao->adiciona = lista_insere_ordenado;
	    nova_colecao->existe = lista_busca;
	    nova_colecao->destroi = lista_libera;

	    break;
	case LISTA_ULTIMO:
	    nova_colecao->estrutura_id = LISTA_ULTIMO;

	    nova_colecao->estrutura = lista_criar();
	    nova_colecao->adiciona = lista_insere_final;
	    nova_colecao->existe = lista_busca;
	    nova_colecao->destroi = lista_libera;
	    
	    break;
	case LISTA_PRIMEIRO:
	    nova_colecao->estrutura_id = LISTA_PRIMEIRO;

	    nova_colecao->estrutura = lista_criar();
	    nova_colecao->adiciona = lista_insere_inicio;
	    nova_colecao->existe = lista_busca;
	    nova_colecao->destroi = lista_libera;

	    break;
	case ARVORE_BINARIA:
	    nova_colecao->estrutura_id = ARVORE_BINARIA;

	    nova_colecao->estrutura = abb_criar();
	    nova_colecao->adiciona = abb_insere;
	    nova_colecao->existe = arvore_busca;
	    nova_colecao->destroi = abb_libera;

	    break;
	case ARVORE_AVL:
	    nova_colecao->estrutura_id = ARVORE_AVL;

	    nova_colecao->estrutura = avl_criar();
	    nova_colecao->adiciona = avl_insere;
	    nova_colecao->existe = arvore_busca;
	    nova_colecao->destroi = avl_libera;
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
    int err;

    /*Reatribui o nó de início para buscas*/
    c->inicio = c->adiciona(c->estrutura, valor, novo_no, &err);

    if (err == EXISTE) 
	{
	//printf("ja tem!!\n");
	free(novo_no);
	}
}

int existe(Colecao* c, int valor)
{
	return c->existe(c->inicio, valor) == INEXISTE ? 0 : 1;
}

void destroi(Colecao* c)
{
    c->destroi(c->estrutura);
    free(c);
}

/*IMPLEMENTAÇÃO DE LISTA*/

struct _lista
{
	No* inicio;
};

LISTA* lista_criar()
{
	LISTA* nova_lista = 
		(LISTA*) calloc(1, sizeof(LISTA));
	return nova_lista;
}

No* __lista_insere_inicio(LISTA* essa_lista, No* no_inserido)
{
	if (essa_lista->inicio == NULL)
	{
		essa_lista->inicio = no_inserido;
	}
	else
	{
		no_inserido->dir = essa_lista->inicio;
		essa_lista->inicio = no_inserido->dir->esq = no_inserido;
	}
	return essa_lista->inicio;	
}

No* lista_insere_inicio(void* essa_lista, int valor, No* no_inserido, int* err)
{
	if (essa_lista == NULL) return NULL;
	return __lista_insere_inicio((LISTA*) essa_lista, no_inserido);
}

No* __lista_insere_final(LISTA* essa_lista, No* no_inserido)
{
	No* temp;

	if (essa_lista->inicio == NULL)
	{
		essa_lista->inicio = no_inserido;
	}
	else
	{
		temp = essa_lista->inicio;

		while (temp->dir != NULL)
			temp = temp->dir;
	
		no_inserido->esq = temp;
		no_inserido->esq->dir = no_inserido;
	}
	
	return essa_lista->inicio;
}

No* lista_insere_final(void* essa_lista, int valor, No* no_inserido, int* err)
{
	if (essa_lista == NULL) return NULL;
	return __lista_insere_final((LISTA*) essa_lista, no_inserido);
}

No* __lista_insere_ordenado(LISTA* essa_lista, int valor, No* no_inserido, int* err)
{
	No* temp;

	if (essa_lista->inicio == NULL)
	{
		essa_lista->inicio = no_inserido;
	}
	else if (essa_lista->inicio->valor > valor)
	{
		no_inserido->dir = essa_lista->inicio;
		essa_lista->inicio = no_inserido->dir->esq = no_inserido;
	}
	else
	{
		temp = essa_lista->inicio;

		while (temp->dir != NULL && temp->dir->valor <= valor)
			temp = temp->dir;

		no_inserido->esq = temp;
		no_inserido->dir = temp->dir;
		no_inserido->esq->dir = no_inserido;
		
		if (no_inserido->dir != NULL)
			no_inserido->dir->esq = no_inserido;

	}

	return essa_lista->inicio;
}

No* lista_insere_ordenado(void* essa_lista, int valor, No* no_inserido, int* err)
{
	if (essa_lista == NULL) return NULL;
	return __lista_insere_ordenado((LISTA*) essa_lista, valor, no_inserido, err);
}

int lista_busca(No* inicio, int valor)
{
	No* temp = inicio;

	while(temp!=NULL)
	{
		if (temp->valor == valor) return valor;
		temp = temp->dir;
	}
	return INEXISTE;
}

void __lista_libera(LISTA* essa_lista)
{
	No* temp = essa_lista->inicio;
	No* temp_prox;

	while(temp!=NULL)
	{
		temp_prox = temp->dir;
		no_libera(temp);
		temp = temp_prox;
	}
}

void lista_libera(void* essa_lista)
{
	__lista_libera((LISTA*)essa_lista);
	free(essa_lista);
}

/*IMPLEMENTAÇÃO DE ÁRVORE DE BUSCA BINÁRIA*/

#define altura(no) ((no != NULL) ? no->altura : 0)

/*Descritor da árvore*/
struct _abb
{
	No* raiz;
};

/*Cria árvore*/
ABB* abb_criar()
{
	ABB* nova_arvore = (ABB*) calloc (1, sizeof(ABB));
	return nova_arvore;
}

/*Atualiza a altura do nó*/
void __abb_atualiza_altura(No* no_inserido)
{
	no_inserido->altura = 1 + max(altura(no_inserido->esq), 
				  altura(no_inserido->dir));
}

/*Insere um nó*/
int __abb_insere(No** no_raiz, int valor, No* no_inserido)
{
	int cr;

	if (no_inserido == NULL) return ERRO;
	if ((*no_raiz) == NULL)
	{
		(*no_raiz) = no_inserido;
		return SUCESSO;
	}
	if ((*no_raiz)->valor == valor) return EXISTE;

	//se o valor atual é maior que o valor que inserimos, insere à esquerda dele
	if ((*no_raiz)->valor > valor)
		cr = __abb_insere(&(*no_raiz)->esq, valor, no_inserido);
	//caso contrário, insere à direita
	else
		cr = __abb_insere(&(*no_raiz)->dir, valor, no_inserido);

	__abb_atualiza_altura(*no_raiz);
	return cr;
}

/*Expõe a inserção do nó*/
No* abb_insere(void* essa_arvore, int valor, No* no_inserido, int* err)
{
	*err = __abb_insere(&((ABB*)essa_arvore)->raiz, valor, no_inserido);
	return ((ABB*)essa_arvore)->raiz;
}

/*Libera a árvore*/
void __abb_libera(No* no_raiz)
{
	//a_pos_ordem(no_raiz, imprime_valor);
	a_pos_ordem(no_raiz, no_libera);
}

/*Expõe a liberação da árvore*/
void abb_libera(void* essa_arvore)
{
	__abb_libera( ((ABB*)essa_arvore)->raiz );
	free(essa_arvore);
}

/*IMPLEMENTAÇÃO DE ÁRVORE AVL*/

struct _avl
{
	No* raiz;
};

AVL* avl_criar()
{
	AVL* nova_arvore = (AVL*) calloc (1, sizeof(AVL));
	return nova_arvore;
}

/*Atualiza altura*/
void __avl_atualiza_altura(No* esse_no)
{
	//printf("%p:%p\n",esse_no->esq,esse_no->dir);
	//printf("%d:%d\n",altura(esse_no->esq),altura(esse_no->dir));
	esse_no->altura = 1 + max(altura(esse_no->esq), 
				  altura(esse_no->dir));
	//printf("altura do nó:%d\n", esse_no->altura);
}

int __avl_fator_balanceamento(No* esse_no)
{
	if (esse_no == NULL) return 0;
	return altura(esse_no->esq) - altura(esse_no->dir);
}

void __avl_balanceia(No** no_raiz)
{
	No* temp;
	if (__avl_fator_balanceamento(*no_raiz) == 2) /*Nó desbalanceado p/ esquerda*/
	{
		if (__avl_fator_balanceamento((*no_raiz)->esq) == 1)
		/*Inserção feita num extremo, RD*/
		{
			//printf("RD\n");
			temp = (*no_raiz);
			(*no_raiz) = (*no_raiz)->esq;
			temp->esq = (*no_raiz)->dir;
			(*no_raiz)->dir = temp;
		}
		else if (__avl_fator_balanceamento((*no_raiz)->esq) == -1) 
		/*Inserção feita em uma sub-árvore direita do nó, RED*/
		{
			/*Rotacao esquerda no nó da esquerda*/
			//printf("RED\n");
			temp = (*no_raiz)->esq;
			(*no_raiz)->esq = (*no_raiz)->esq->dir;
			temp->dir = (*no_raiz)->esq->esq;
			(*no_raiz)->esq->esq = temp;
			/*Rotacao direita no nó raiz*/
			temp = (*no_raiz);
			(*no_raiz) = (*no_raiz)->esq;
			temp->esq = (*no_raiz)->dir;
			(*no_raiz)->dir = temp;
		}
	}
	else if (__avl_fator_balanceamento(*no_raiz) == -2)
	{
		if (__avl_fator_balanceamento((*no_raiz)->dir) == -1) /*Inserção feita num extremo, RE*/
		{
			//printf("RE\n");
			temp = (*no_raiz);
			(*no_raiz) = (*no_raiz)->dir;
			temp->dir = (*no_raiz)->esq;
			(*no_raiz)->esq = temp;
		}
		else if (__avl_fator_balanceamento((*no_raiz)->dir) == 1) /*Inserção feita em uma sub-árvore */
		{
			/*Rotacao direita no nó da direita*/
			//printf("RDE\n");
			temp = (*no_raiz)->dir;
			(*no_raiz)->dir = (*no_raiz)->dir->esq;
			temp->esq = (*no_raiz)->dir->dir;
			(*no_raiz)->dir->dir = temp;
			/*Rotacao esquerda no nó raiz*/
			temp = (*no_raiz);
			(*no_raiz) = (*no_raiz)->dir;
			temp->dir = (*no_raiz)->esq;
			(*no_raiz)->esq = temp;
		}
	}
}

int __avl_insere(No** no_raiz, int valor, No* no_inserido)
{
	int cr; //codigo de retorno

	if (no_inserido == NULL) return ERRO;
	if ((*no_raiz) == NULL)
	{
		no_inserido->altura = 1;
		(*no_raiz) = no_inserido;
		return SUCESSO;
	}

	if ((*no_raiz)->valor == valor) return EXISTE;

	//se o valor atual é maior que o valor que inserimos, insere à esquerda dele
	if ((*no_raiz)->valor > valor)
	{
		cr = __avl_insere(&(*no_raiz)->esq, valor, no_inserido);
	}
	else //caso contrário, insere à direita
	{
		cr = __avl_insere(&(*no_raiz)->dir, valor, no_inserido);
	}
		//atualiza a altura do nó após a inserção

	__avl_atualiza_altura(*no_raiz);
	__avl_balanceia(no_raiz);
	return cr; 
}

No* avl_insere(void* essa_arvore, int valor, No* no_inserido, int* err)
{
	*err = __avl_insere(&((AVL*)essa_arvore)->raiz, valor, no_inserido);
	return ((AVL*)essa_arvore)->raiz;
}

void __avl_libera(No* no_raiz)
{
	//a_pos_ordem(no_raiz, imprime_valor);
	a_pos_ordem(no_raiz, no_libera);
}

void avl_libera(void* essa_arvore)
{
	__avl_libera( ((AVL*)essa_arvore)->raiz );
	free(essa_arvore);
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

void a_pos_ordem(No* no_raiz, void (*exec)(No*))
{
	//printf("ptr: %p\n", no_raiz);
	if (no_raiz == NULL) return;
	if (no_raiz->esq != NULL)
	{
		a_pos_ordem(no_raiz->esq, exec);
	}

	if (no_raiz->dir != NULL)
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

//DEBUG

/*IMPRIME NÓ*/

void imprime_valor(No* esse_no)
{
	//printf("no: %d..altura:%d\n", esse_no->valor, esse_no->altura);
}
