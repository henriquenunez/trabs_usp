#include "newborns.h"
#include "csv.h"
#include "bin.h"


#include <stdlib.h>
#include <string.h>

BIN_FILE *loadBinFile(char *file_name);

typedef struct _nascimento nascimento;

struct _newborns {
    BIN_FILE* binary_file;
};

NEWBORNS* NBCreateInstance(const char* gen_filename) {
    NEWBORNS* ret_instance;
    ret_instance = (NEWBORNS*) malloc(sizeof(NEWBORNS));

    ret_instance->binary_file = openBinFile();

    //Instanciation error-checking
    if (ret_instance->binary_file == NULL) {
	//dealloc stuff
	//closeBinFile();
	free(ret_instance);
	return NULL;
    }


    return ret_instance;
}


/*////////////////////////////////////////////////////////////////////////////

NOT MY CODE BEYOND THIS POINT

*/


/*****************************************************************
 * Funções relativos ao tipo de dado que será armazenado
 * O tipo de dado é nascimento e está guardado numa struct
 * Esse tipo é público e será usado para facilitar a administração 
 * dos dados a serem guardados no arquivo
 * ***************************************************************/

nascimento* createNascimento(	int id,
				int idadeMae,
				char data[10],
				char sexo,
				char estadoMae[2],
				char estadoBebe[2],
				char* cidadeMae,
				char* cidadeBebe);


struct _nascimento{
    int id;
    int idadeMae;
    char data[10];
    char sexo;
    char estadoMae[2];
    char estadoBebe[2];
    char* cidadeMae;
    char* cidadeBebe;
};

//Cria um objeto do tipo nascimento.
nascimento* createNascimento(int id, int idadeMae, char data[10], char sexo, char estadoMae[2], char estadoBebe[2], char* cidadeMae, char* cidadeBebe){
    nascimento *n = (nascimento*) malloc(sizeof(nascimento));
    n->id = id;
    n->idadeMae = idadeMae;
    strcpy(n->data, data);
    n->sexo = sexo;
    strcpy(n->estadoMae, estadoMae);
    strcpy(n->estadoBebe, estadoBebe);
    strcpy(n->cidadeMae, cidadeMae);
    strcpy(n->cidadeBebe, cidadeBebe);
    return n;
}

BIN_FILE *loadBinFile(char* fileName){
    BIN_FILE *bf = openBinFile(fileName, 128);
    return bf;
}

nascimento *readCsvEntry(CSV_FILE *cf){
    int id;
    int idadeMae;
    char *dataP;
    char data[10];
    char sexo;
    char *estadoMaeP;
    char estadoMae[2];
    char *estadoBebeP;
    char estadoBebe[2];
    char* cidadeMae;
    char* cidadeBebe;

    cidadeMae = getNextString(cf);
    cidadeBebe = getNextString(cf);
    id = getNextInt(cf);
    idadeMae = getNextInt(cf);
    dataP = getNextString(cf);
    sexo = getNextString(cf);
    estadoMaeP = getNextString(cf);
    estadoBebeP = getNextString(cf);

    strcpy(data, dataP);
    strcpy(estadoMae, estadoMaeP);
    strcpy(estadoBebe, estadoBebeP);

    return createNascimento(id, idadeMae, data, sexo, estadoMae, estadoBebe, cidadeMae, cidadeBebe);
}

void ReadCsvNewborns(BIN_FILE *bf, char* filename){
    CSV_FILE *cf = openCsvFile(filename);
    nascimento *n;
    while(n = readCsvEntry(cf)){
        NBInsertBaby(bf, n);
        free(n);
    }

    closeCsvFile(cf);
    free(cf);
}

void *NBtoByte(nascimento *n){
    void *buffer = malloc(128);
    int offset = 0;
    *((int*) buffer + offset) = strlen(((nascimento*)n)->cidadeMae);
    offset += sizeof(int);
    *((int*) buffer + offset) = strlen(((nascimento*)n)->cidadeBebe);
    offset += sizeof(int);
    *((char*) buffer + offset) = ((nascimento*)n)->cidadeMae;
    offset += strlen(((nascimento*)n)->cidadeMae);
    *((char*) buffer + offset) = ((nascimento*)n)->cidadeBebe;
    offset += strlen(((nascimento*)n)->cidadeBebe);
    *((int*) buffer + offset) = ((nascimento*)n)->id;
    offset += sizeof(int);
    *((int*) buffer + offset) = ((nascimento*)n)->idadeMae;
    offset += sizeof(int);
    *((char*) buffer + offset) = ((nascimento*)n)->data;
    offset += 10;
    *((char*) buffer + offset) = ((nascimento*)n)->sexo;
    offset++;
    *((char*)buffer + offset) = ((nascimento*)n)->estadoMae;
    offset += 2;
    *((char*)buffer + offset) = ((nascimento*)n)->estadoBebe;
    return buffer;
}

void NBInsertBaby(BIN_FILE* bf, nascimento* n) {
    appendRegisterBinFile(bf, &NBtoByte, n);
}

nascimento *readBinFile(void *data){
    int id;
    int idadeMae;
    char date[10];
    char sexo;
    char estadoMae[2];
    char estadoBebe[2];
    char* cidadeMae;
    char* cidadeBebe;

    int sizeMae;
    int sizeBebe;

    int offset = 0;
    sizeMae = *((int*) data + offset);
    offset += sizeof(int);
    sizeBebe = *((int*) data + offset);
    offset += sizeof(int);
    memcpy(cidadeMae, (char*)data+offset, sizeMae);
    offset += sizeMae;
    memcpy(cidadeBebe, (char*)data+offset, sizeBebe);
    offset += (105 - 8 - sizeMae);
    id = *((int*) data + offset);
    offset += sizeof(int);
    idadeMae = *((int*) data + offset);
    offset += sizeof(int);
    memcpy(date, (char*)data+offset, 10);
    offset += 10;
    sexo = *((char*)data+offset);
    offset += 1;
    memcpy(estadoMae, (char*)data+offset, 2);
    offset += 2;
    memcpy(estadoBebe, (char*)data+offset, 2);
    offset += 2;
    

    return createNascimento(id, idadeMae, date, sexo, estadoMae, estadoBebe, cidadeMae, cidadeBebe);
}

nascimento *NBReadBaby(BIN_FILE *bf, int rrn){
    return readBinFile(bf, &byteToNB, rrn);
}

void printNewborn(nascimento *n){
    char *sex;
    if(n->sexo == '1'){
        sex = "MASCULINO";
    }else if(n->sexo == '2'){
        sex = "FEMININO";
    }else{
        sex = "IGNORADO";
    }
    printf("Nasceu em %s, em %s, um bebe do sexo %s\n", (n->cidadeBebe)? n->cidadeBebe : "-", (n->data)? n->data: "-", sex);

}

PrintAllNewborns(BIN_FILE *bf){
    nascimento *n;
    for(int i = 0 ; ; i++){
        if(!(n = NBReadBaby(bf, 128*i))){
            break;
        }
        printNewborn(n);
    }
}