/************************************************************************************
 * Henrique Hiram Libutti Núñez - 11275300
 * Rafael Tavares Oliveira - 11219071
 * *********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "newborns.h"
#include "binarioNaTela.c"

#define TRUE 1
#define FALSE 0

//Função main deste programa funcionará apenas como o menu para lidar com a entrada do usuário
int main(void)
{
	FILE *fp;

	//Instancia um newborns
	NEWBORNS *bb;
	//Lẽ a entrda do usuário para a funcionalidade
	int func = 0;
	scanf("%d", &func);
	//Variáveis buffer para processar a entrada
	char *arq_csv, *arq_bin;
	//Verifica qual foi a funcionalidade chamada
	switch (func){
		//Lê arquivo CSV e transforma em binário
	case 1:
		scanf(" %ms %ms", &arq_csv, &arq_bin);
		// printf("Lendo arquivo CSV %s e armazenando em %s\n", arq_csv, arq_bin);
		// apaga o binário por problemas na plataforma.
		remove(arq_bin);

		bb = NBCreateInstance(arq_bin);
		if (bb == NULL)
		{
			printf("Falha no processamento do arquivo.\n");
			break;
		}

		//Lê o arquivo csv e escreve no binário
		NBImportCSV(bb, arq_csv);
		NBDeleteInstance(bb);
		// printf("Binário na tela: ");
		binarioNaTela(arq_bin);
		free(arq_csv);
		free(arq_bin);
		break;

	//Lê binário e imprime algumas informações para todas as entradas
	case 2:
		scanf(" %ms", &arq_bin);
		//printf("{%s}", arq_bin);
		// Verifica se existe o arquivo
		fp = fopen(arq_bin, "rb");
		if (fp == NULL)
		{
			printf("Falha no processamento do arquivo.\n");
      free(arq_bin);
			break;
		}
		fclose(fp);
		//Lê o arquivo binário
		bb = NBCreateInstance(arq_bin);

		// printf("Imprimindo informações do arquivo armazenado em %s\n", arq_bin);
		// Verifica erro no arquivo
		if (bb == NULL)
		{
			printf("Falha no processamento do arquivo.\n");
			break;
		}

		//Imprime os newborns
		NBPrintAllNewborns(bb);
		fflush(0);
		NBDeleteInstance(bb);
		free(arq_bin);
		break;

	case 3:

		scanf(" %ms", &arq_bin);
    // printf("%s\n", arq_bin);
		// Verifica se existe o arquivo
		fp = fopen(arq_bin, "rb");
		if (fp == NULL)
		{
			printf("Falha no processamento do arquivo.\n");
      free(arq_bin);
			break;
		}
		fclose(fp);

		// Abre arquivo binário
		bb = NBCreateInstance(arq_bin);
		if(bb == NULL){
			printf("Falha no processamento do arquivo.\n");
		}

		// Getting vector size
		int m = 0;
		scanf("%d", &m);

		// Inicializing vector
		STRING_PAIR_VECTOR vector;
		vector.size = m;
		vector.data = (STRING_PAIR*) malloc(m*sizeof(STRING_PAIR));

		// Filling vector data
		for(int i = 0 ; i < m ; i++){
			char *key;
			char *value = (char*) malloc(97*sizeof(char));
			scanf(" %ms", &key);
			if(strcmp(key, "idadeMae") == 0 || strcmp(key, "idNascimento") == 0){
				scanf(" %s", value);
			}else{
				scan_quote_string(value);
			}
			STRING_PAIR node;
			node.key = key;
			node.value = value;
			vector.data[i] = node;
		}

		// Calling search
    nb_err_t response = NBSearchMatchingFields(bb, vector);
		if(response != NB_OK) printf("Registro Inexistente.\n");

		// Freeing vector
		for(int i = 0 ; i < m ; i++){
			free(vector.data[i].key);
			free(vector.data[i].value);
		}
		free(vector.data);

		fflush(0);
		NBDeleteInstance(bb);
		free(arq_bin);
		break;
	
	case 4:
		scanf(" %ms", &arq_bin);

		// Verifica se existe arquivo
		fp = fopen(arq_bin, "rb");
		if(fp == NULL){
			printf("Falha no processamento do arquivo.\n");
      free(arq_bin);
			break;
		}
		fclose(fp);

		// Abre arquivo binário
		bb = NBCreateInstance(arq_bin);
		if(bb == NULL){
			printf("Falha no processamento do arquivo.\n");
		}

		// Gets RRN
		int rrn = 0;
		scanf("%d", &rrn);

		// Calling search
    response = NBSearchByRegisterNumber(bb, rrn);
		if(response != NB_OK) printf("Registro Inexistente.\n");

		// Clering memory
		fflush(0);
		NBDeleteInstance(bb);
		free(arq_bin);
		break;

	case 5:
		scanf(" %ms", &arq_bin);

		// Verifica se existe arquivo
		fp = fopen(arq_bin, "rb");
		if(fp == NULL){
			printf("Falha no processamento do arquivo.\n");
			free(arq_bin);
			break;
		}
		fclose(fp);

		// Abre arquivo binário
		bb = NBCreateInstance(arq_bin);
		if(bb == NULL){
			printf("Falha no processamento do arquivo.\n");
			break;
		}

		// Repeats remove process
		int times = 0;
		scanf("%d", &times);
		for(int i = 0 ; i < times ; i++){
			int m = 0;
			scanf("%d", &m);

			// Inicializing vector
			STRING_PAIR_VECTOR vector;
			vector.size = m;
			vector.data = (STRING_PAIR*) malloc(m*sizeof(STRING_PAIR));

			// Filling vector data
			for(int i = 0 ; i < m ; i++){
				char *key;
				char *value = (char*) malloc(97*sizeof(char));
				scanf(" %ms", &key);
				if(strcmp(key, "idadeMae") == 0 || strcmp(key, "idNascimento") == 0){
					scanf(" %s", value);
				}else{
					scan_quote_string(value);
				}
				STRING_PAIR node;
				node.key = key;
				node.value = value;
				vector.data[i] = node;
			}

			response = NBRemoveMatchingFields(bb, vector);
			// if(response != NB_OK) printf("Registro Inexistente.\n");

			// Freeing vector
			for(int i = 0 ; i < m ; i++){
				free(vector.data[i].key);
				free(vector.data[i].value);
			}
			free(vector.data);
		}
		
		fflush(0);
		NBDeleteInstance(bb);
    	binarioNaTela(arq_bin);
		free(arq_bin);
		break;

	case 6:
		scanf(" %ms", &arq_bin);

		// Verifica se existe arquivo
		fp = fopen(arq_bin, "rb");
		if(fp == NULL){
			printf("Falha no processamento do arquivo.\n");
      		free(arq_bin);
			break;
		}
		fclose(fp);

		// Abre arquivo binário
		bb = NBCreateInstance(arq_bin);
		if(bb == NULL){
			printf("Falha no processamento do arquivo.\n");
			break;
		}

		times = 0;
		scanf("%d", &times);
		for(int i = 0 ; i < times ; i++){
      // Inicializing vector
			STRING_PAIR_VECTOR vector;
			vector.size = 8;
			vector.data = (STRING_PAIR*) malloc(8*sizeof(STRING_PAIR));

      char* keyVector[] = {"cidadeMae", "cidadeBebe", "idNascimento", "idadeMae", "dataNascimento", "sexoBebe", "estadoMae", "estadoBebe"};

      // Getting inputs
      for(int j = 0 ; j < 8 ; j++){
        // printf("Data: %d\n", j);
        STRING_PAIR node;
        node.key = keyVector[j];
        node.value = (char*) malloc(50*sizeof(char));
        scan_quote_string(node.value);
        vector.data[j] = node;
      }

      // Calling function
      response = NBInsertNewbornAtEnd(bb, vector);
      // if(NBInsertNewbornAtEnd(bb, vector) != NB_OK){ printf("Falha no processamento do arquivo.\n");}

      // Freeing vector
			for(int i = 0 ; i < 8 ; i++){
				// free(vector.data[i].key);
				free(vector.data[i].value);
			}
			free(vector.data);

		}
		fflush(0);
		NBDeleteInstance(bb);
    binarioNaTela(arq_bin);
		free(arq_bin);
		break;

	case 7:
		scanf(" %ms", &arq_bin);

		// Verifica se existe arquivo
		fp = fopen(arq_bin, "rb");
		if(fp == NULL){
			printf("Falha no processamento do arquivo.\n");
			free(arq_bin);
			break;
		}
		fclose(fp);

		// Abre arquivo binário
		bb = NBCreateInstance(arq_bin);
		if(bb == NULL){
			printf("Falha no processamento do arquivo.\n");
			break;
		}

		times = 0;
		scanf("%d", &times);
		for(int i = 0 ; i < times ; i++){
			int rrn = 0;
			scanf("%d", &rrn);

      int m = 0;
			scanf("%d", &m);

			// Inicializing vector
			STRING_PAIR_VECTOR vector;
			vector.size = m;
			vector.data = (STRING_PAIR*) malloc(m*sizeof(STRING_PAIR));

			// Filling vector data
			for(int i = 0 ; i < m ; i++){
				char *key;
				char *value = (char*) malloc(97*sizeof(char));
				scanf(" %ms", &key);
				if(strcmp(key, "idadeMae") == 0 || strcmp(key, "idNascimento") == 0){
					scanf(" %s", value);
				}else{
					scan_quote_string(value);
				}
				STRING_PAIR node;
				node.key = key;
				node.value = value;
				vector.data[i] = node;
			}

			response = NBUpdateByRegisterNumber(bb, rrn, vector);
			// if(response != NB_OK) printf("Registro Inexistente.\n");

			// Freeing vector
			for(int i = 0 ; i < m ; i++){
				free(vector.data[i].key);
				free(vector.data[i].value);
			}
			free(vector.data);
		}
		fflush(0);
		NBDeleteInstance(bb);
    binarioNaTela(arq_bin);
		free(arq_bin);
		break;
	}
}
