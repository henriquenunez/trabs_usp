#include <stdio.h>
#include <stdlib.h>
#include "newborns.h"
#include "binarioNaTela.c"

#define TRUE 1
#define FALSE 0

//Função main deste programa funcionará apenas como o menu para lidar com a entrada do usuário
int main(void){
    while(TRUE){
        //Instancia um newborns
        NEWBORNS *bb; 
        //Variável para manutenção do menu
        int sair_do_programa = FALSE;
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
                //cria um arquivo binário
                bb = NBCreateInstance(arq_bin);
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
                // printf("Imprimindo informações do arquivo armazenado em %s\n", arq_bin);
                // Verifica se existe o arquivo
                FILE* fp = fopen(arq_bin, "rb");
                if(fp == NULL){
                    printf("Falha no processamento do arquivo.\n");
                    break;
                }
                fclose(fp);
                //Lê o arquivo binário
                bb = NBCreateInstance(arq_bin);
                //Imprime os newborns
                NBPrintAllNewborns(bb);
                NBDeleteInstance(bb);
                free(arq_bin);
                break;
            
            // Qualquer outra entrada implicará na saída do programa
            default:
                sair_do_programa = TRUE;
                break;
        }
        
        if(sair_do_programa){
            break;
        }
    }
}
