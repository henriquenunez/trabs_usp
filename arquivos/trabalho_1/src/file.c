#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

struct _FILE_NODE{
    FILE* file;
    char* file_name;
    int canRead;
    int canWrite;
    int isBinary;
    int isEndFile;
};

//Faz a verificação da opção para setar permissões
void setOption(FILE_NODE* fn, char option[3]){
    if(option[0] == 'a'){
        fn->canRead = 0;
        fn->canWrite = 1;
        fn->isBinary = 0;
        fn->isEndFile = 1;
    }else if(option[0] == 'r'){
        fn->canRead = 1;
        fn->canWrite = 0;
        fn->isBinary = 0;
        fn->isEndFile = 1;
    }else if(option[0] == 'w'){
        fn->canRead = 0;
        fn->canWrite = 1;
        fn->isBinary = 0;
        fn->isEndFile = 0;
    }
    if(option[1] == '\0') return;
    if(option[1] == '+'){
        fn->canRead = 1;
        fn->canWrite = 1;
    }else if(option[1] == 'b'){
        fn->isBinary = 1;
    }
    if(option[2] == '\0') return;
    if(option[2] == '+'){
        fn->canRead = 1;
        fn->canWrite = 1;
    }else if(option[2] == 'b'){
        fn->isBinary = 1;
    }
    return;
}

//Abre arquivo e cadastra perrmissões
FILE_NODE* openFile(char file_name[50], char option[3]){
    FILE* fp = fopen(file_name, option);
    if(fp){
        FILE_NODE* fn = (FILE_NODE*) malloc(sizeof(FILE_NODE));
        fn->file = fp;
        fn->file_name = file_name;
        setOption(fn, option);
        return fn;
    }else{
        printf("[!] Couldn't open file [!]\n");
        return NULL;
    }
}

//Lê os 'times' int logo em seguida do arquivo
int readIntFile(FILE_NODE* fn, int times){
    if(!fn->canRead){
        printf("[!] Permission denied: Can't read file [!]\n");
        return 0;
    }
    int num;
    fread(&num, sizeof(int), times, fn->file);
    return num;
}

//Lê os 'times' float logo em seguida do arquivo
float readFloatFile(FILE_NODE* fn, int times){
    if(!fn->canRead){
        printf("[!] Permission denied: Can't read file [!]\n");
        return 0;
    }
    float num;
    fread(&num, sizeof(float), times, fn->file);
    return num;
}

//Lê a String de tamanho 'size' logo em seguida do arquivo
char* readStringFile(FILE_NODE* fn, int size){
    if(!fn->canRead){
        printf("[!] Permission denied: Can't read file [!]\n");
        return NULL;
    }
    char* string = (char*) malloc(sizeof(char)*size);
    fread(string, sizeof(char), size, fn->file);
    return string;
}

//Escreve um int no lugar do ponteiro do arquivo
void writeIntFile(FILE_NODE* fn, int data){
    if(!fn->canWrite){
        printf("[!] Permission denied: Can't read file [!]\n");
        return;
    }
    fwrite(&data, sizeof(int), 1, fn->file);
}

//Escreve um float no lugar do ponteiro do arquivo
void writeFloatFile(FILE_NODE* fn, float data){
    if(!fn->canWrite){
        printf("[!] Permission denied: Can't read file [!]\n");
        return;
    }
    fwrite(&data, sizeof(float), 1, fn->file);
}

//Escreve uma string no lugar do ponteiro do arquivo
void writeStringFile(FILE_NODE* fn, char* data){
    if(!fn->canWrite){
        printf("[!] Permission denied: Can't read file [!]\n");
        return;
    }
    fwrite(data, sizeof(char), strlen(data), fn->file);
}

//Procura no arquivo a partir desse ponto
void seekFile(FILE_NODE* fn, int whereTo){
    fseek(fn->file, whereTo, SEEK_CUR);
}

//Procura no arquivo a partir do início
void seekFromStartFile(FILE_NODE* fn, int whereTo){
    fseek(fn->file, whereTo, SEEK_SET);
}

//Vai para o final do arquivo
void goToEOF(FILE_NODE* fn){
    fseek(fn->file, 0, SEEK_END);
}

//Verifica se é o fim do arquivo. Retorna 0 se for o fim.
int isEOF(FILE_NODE* fn){
    FILE* test = fn->file;
    fseek(test, 1, SEEK_CUR);
    char dump;
    if(fread(&dump, sizeof(char), 1, test)){
        fseek(test, -2, SEEK_CUR);
        return 1;
    }else{
        fseek(test, -2, SEEK_CUR);
        return 0;
    }
}

int getLengthFile(FILE_NODE* fn){
    goToEOF(fn);
    return ftell(fn->file);
}

int whereFile(FILE_NODE*fn){
    return ftell(fn->file);
}

//Fecha o arquivo
void closeFile(FILE_NODE* fn){
    fclose(fn->file);
    free(fn);
    return;
}