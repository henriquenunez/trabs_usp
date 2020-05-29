#include <stdio.h>
#include <stdlib.h>

#include "bin.h"

#define REG_SIZE 128
#define VAR_FIELDS_MAX_LEN 97


typedef struct _nascimento{
    int  id;
    int  idadeMae;
    char data[11];
    char sexo;
    char estadoMae[3];
    char estadoBebe[3];
    char cidadeMae[98];
    char cidadeBebe[98];
} nascimento;

//Builds struct nascimento.
nascimento* createNascimento(	int   id,
				int   idadeMae,
				char* data,
				char  sexo,
				char* estadoMae,
				char* estadoBebe,
				char* cidadeMae,
				char* cidadeBebe) {

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

void* __build_bin_data_nb(void *n_data) {
    void *buffer = malloc(128);
    int offset = 0;
    int aux;

    #define NAS ((nascimento*)n_data)
    #define BUFFOFF (buffer + offset)

    if (strlen(NAS->cidadeMae)) {
	*((int*) BUFFOFF) = strlen(NAS->cidadeMae);
    } else {
	*((int*) BUFFOFF) = 0;
    }
    offset += sizeof(int);

    // printf("offset: %d\n", offset);

    if (strlen(NAS->cidadeBebe)) {
	*((int*) BUFFOFF) = strlen(NAS->cidadeBebe);
    } else {
	*((int*) BUFFOFF) = 0;
    }

    offset += sizeof(int);
    // printf("offset: %d\n", offset);

    /*Variable length fields max size: 96*/
    if (strlen(NAS->cidadeMae)) {
        memcpy(BUFFOFF, NAS->cidadeMae, strlen(NAS->cidadeMae));
	offset += strlen(NAS->cidadeMae);
    }
    // printf("offset: %d\n", offset);

    if (strlen(NAS->cidadeBebe)) {
        memcpy(BUFFOFF, NAS->cidadeBebe, strlen(NAS->cidadeBebe));
	offset += strlen(NAS->cidadeBebe);
    }
    // printf("offset: %d\n", offset);

    memset(BUFFOFF,
	    0x24,
	VAR_FIELDS_MAX_LEN -
	  (((strlen(NAS->cidadeMae) > 0)?(strlen(NAS->cidadeMae)):0) +
	  ((strlen(NAS->cidadeBebe) > 0)?(strlen(NAS->cidadeBebe)):0))
	);

    offset +=
	VAR_FIELDS_MAX_LEN -
	    (((strlen(NAS->cidadeMae) > 0)?(strlen(NAS->cidadeMae)):0) +
	    ((strlen(NAS->cidadeBebe) > 0)?(strlen(NAS->cidadeBebe)):0));
    // printf("offset: %d\n", offset);

    /*Static fields*/
    *((int*) BUFFOFF) = NAS->id;
    offset += sizeof(int);
    // printf("offset: %d\n", offset);

    if (NAS->idadeMae > 0)
        *((int*) BUFFOFF) = NAS->idadeMae;
    else
        *((int*) BUFFOFF) = -1;
    offset += sizeof(int);
    // printf("offset: %d\n", offset);

    /*Date string*/
    if (strlen(NAS->data)) {
	memcpy(BUFFOFF, NAS->data, 10);
    } else {
	memcpy(BUFFOFF, "\0$$$$$$$$$", 10);
    }
    offset += 10;
    // printf("offset: %d\n", offset);
    if (NAS->sexo)
        *((char*) BUFFOFF) = NAS->sexo;
    else
        *((char*) BUFFOFF) = '0';
    offset += 1;
    // printf("offset: %d\n", offset);

    if (strlen(NAS->estadoMae)) {
	memcpy(BUFFOFF, NAS->estadoMae, 2);
    } else {
	memcpy(BUFFOFF, "\0$", 2);
    }
    offset += 2;
    // printf("offset: %d\n", offset);

    if (strlen(NAS->estadoBebe)) {
	memcpy(BUFFOFF, NAS->estadoBebe, 2);
    } else {
	memcpy(BUFFOFF, "\0$", 2);
    }
    offset += 2;

    // printf("offset: %d\n", offset);
    #undef NAS
    #undef BUFFOFF

    return buffer;
}

int main() {
    BIN_FILE* this_bin_file;
		nascimento* n = createNascimento(5, 32, "2020-12-07", 1, "SE", "SE", "Aracaju", "Aracaju");
    // void* hello = NULL;

    this_bin_file = openBinFile("insert.bin", REG_SIZE);

    bin_err_t response =  insertRegisterBinFile(this_bin_file, __build_bin_data_nb, n, 2);

    if(response != OK){
        printf("response not ok\n");
        return 1;
    }

    closeBinFile(this_bin_file);
		free(n);

    // FILE* fp = fopen("response.bin", "wb");
    // fwrite(hello, REG_SIZE, 1, fp);
    // fclose(fp);

    // free(hello);

    // //Acquire data now.

    // int times = 3;

    // this_bin_file = openBinFile("delete.bin", REG_SIZE);
    // printf("Numero de regs: %ld\n", getNumRegistersBinFile(this_bin_file));
    // while (times--) {
    //     printf("%d\n", times);
    //     bin_err_t status = getRegistersBinFile(this_bin_file, &hello);
    //     printf("status: %d\n", status);
    //     if (status != OK) {printf("Not OK\n"); continue;};
    // }

    // free(hello);

    // closeBinFile(this_bin_file);
    return 0;
}