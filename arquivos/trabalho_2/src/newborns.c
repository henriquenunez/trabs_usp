#include "newborns.h"
#include "csv.h"
#include "bin.h"

#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define REG_SIZE 128 //128B per register
#define VAR_FIELDS_MAX_LEN 97

//const int garbage_s = 12; //12B for garbage
//const char garbage[] = {'\0','$','$','$','$','$','$','$','$','$','$','$'};

BIN_FILE *loadBinFile(char *file_name);

typedef struct _nascimento nascimento;

struct _newborns {
    BIN_FILE* bf;
};

/*****************************************************************
 * Funções relativos ao tipo de dado que será armazenado
 * O tipo de dado é nascimento e está guardado numa struct
 * Esse tipo é público e será usado para facilitar a administração
 * dos dados a serem guardados no arquivo
 * ***************************************************************/

nascimento* createNascimento(	int   id,
				int   idadeMae,
				char* data,
				char  sexo,
				char* estadoMae,
				char* estadoBebe,
				char* cidadeMae,
				char* cidadeBebe);


struct _nascimento{
    int  id;
    int  idadeMae;
    char data[11];
    char sexo;
    char estadoMae[3];
    char estadoBebe[3];
    char cidadeMae[98];
    char cidadeBebe[98];
};

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

// Reads csv entry and turns it into a nascimento instance
nascimento* readCsvEntry(CSV_FILE *cf) {
    int id = -1;
    int idadeMae = -1;
    char data[11] = {0};
    char sexo = 0;
    char estadoMae[4] = {0};
    char estadoBebe[4] = {0};
    char cidadeMae[99] = {0};
    char cidadeBebe[99] = {0};
    char *temp;

    temp = getNextString(cf);
    //printf("GOT{%s}\n", temp);
    if (temp != NULL)
        strcpy(cidadeMae, temp);

    temp = getNextString(cf);
    //printf("GOT{%s}\n", temp);
    if (temp != NULL)
        strcpy(cidadeBebe, temp);

    id = getNextInt(cf);

    idadeMae = getNextInt(cf);

    temp = getNextString(cf);
    //printf("GOT{%s}\n", temp);
    if (temp != NULL)
        strcpy(data, temp);

    temp = getNextString(cf);
    //printf("GOT{%s}\n", temp);
    if (temp != NULL)
        sexo = temp[0];

    temp = getNextString(cf);
    //printf("GOT{%s}\n", temp);
    if (temp != NULL)
        strcpy(estadoMae, temp);

    temp = getNextString(cf);
    //printf("GOT{%s}\n", temp);
    if (temp != NULL)
        strcpy(estadoBebe, temp);

    return createNascimento(id,
			    idadeMae,
			    data,
			    sexo,
			    estadoMae,
			    estadoBebe,
			    cidadeMae,
			    cidadeBebe);
}

// Builds a byte array with the data to be stored in .bin file
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

// Inserts baby as new entry to .bin file
void __insert_baby_nb(BIN_FILE* bf, nascimento* n,  int rrn) {
    insertRegisterBinFile(bf, &__build_bin_data_nb, n, rrn);
}

//Properly builds struct from binary data
nascimento* __parse_bin_data_nb(void *data){
    int id = -1;
    int idadeMae = -1;
    char date[11] = {0};
    char sexo = 0;
    char estadoMae[4] = {0};
    char estadoBebe[4] = {0};
    char cidadeMae[99] = {0};
    char cidadeBebe[99] = {0};

    char *temp;

    int sizeMae;
    int sizeBebe;

    int offset = 0;

    #define DATAOFF (data+offset)

    sizeMae = *((int*) DATAOFF);
    offset += sizeof(int);

    sizeBebe = *((int*) DATAOFF);
    offset += sizeof(int);

    if (sizeMae > 0) {
        memcpy(cidadeMae, (char*)DATAOFF, sizeMae);
	offset += sizeMae;
    }

    if (sizeBebe > 0) {
        memcpy(cidadeBebe, (char*)DATAOFF, sizeBebe);
	offset += sizeBebe;
    }

    offset += VAR_FIELDS_MAX_LEN;

    if (sizeMae > 0) {
	offset -= sizeMae;
    }

    if (sizeBebe > 0) {
	offset -= sizeBebe;
    }

    id = *((int*) DATAOFF);
    offset += sizeof(int);

    idadeMae = *((int*) DATAOFF);
    offset += sizeof(int);

    memcpy(date, DATAOFF, 10);
    offset += 10;

    sexo = *((char*)DATAOFF);
    offset += 1;

    memcpy(estadoMae, DATAOFF, 2);
    offset += 2;

    memcpy(estadoBebe, DATAOFF, 2);
    offset += 2;


    return createNascimento(id,
			    idadeMae,
			    date,
			    sexo,
			    estadoMae,
			    estadoBebe,
			    cidadeMae,
			    cidadeBebe);
}

// Specification for printing the data on one entry
void printNewborn(nascimento *n){
    char *sex;

    if(n->sexo == '1'){
        sex = "MASCULINO";
    }else if(n->sexo == '2'){
        sex = "FEMININO";
    }else{
        sex = "IGNORADO";
    }
    printf("Nasceu em %s/%s, em %s, um bebê de sexo %s.\n",
					strlen(n->cidadeBebe)? n->cidadeBebe : "-",
                    strlen(n->estadoBebe)? n->estadoBebe : "-",
					strlen(n->data)? n->data: "-",
					sex);

}

/*EXPOSED FUNCTIONS*/

// Opens .bin file with newborns to read
NEWBORNS* NBCreateInstance(const char* gen_filename) {
    NEWBORNS* ret_instance;
    ret_instance = (NEWBORNS*) malloc(sizeof(NEWBORNS));

    ret_instance->bf = openBinFile(gen_filename, REG_SIZE);

    //Instanciation error-checking
    if (ret_instance->bf == NULL) {
	//dealloc stuff
	//closeBinFile();
	free(ret_instance);
	return NULL;
    }


    return ret_instance;
}

// Gets all entries from .csv file and appends it on .bin file
nb_err_t NBImportCSV(NEWBORNS* these_babies , const char* filename){
    CSV_FILE *cf;
    nascimento *n;
    int csv_entries;
    int temp;

    cf = openCsvFile(filename);
    csv_entries = countLinesCsvFile(cf);

    temp = csv_entries;

    skipHeaderCsvFile(cf);

    if (csv_entries > 0)
    while(--csv_entries){ //Count one less because of header
	// printf("\tentry n: %d\n", temp - csv_entries);
	n = readCsvEntry(cf);
	__insert_baby_nb(these_babies->bf, n, -1);
        free(n);
    }

    closeCsvFile(cf);
}

// Prints all entries in .bin newborns file in the pattern defined
nb_err_t NBPrintAllNewborns(NEWBORNS* these_babies){
    size_t nregs;	//Number of registers retrieved from file
    nascimento *n;	//Temporary structure
    void* ptr = NULL;	//Ptr to receive data


    nregs = getNumRegistersBinFile(these_babies->bf) + 5;

    for(int i = 0 ; i < nregs; i++){

        if (getRegistersBinFile(these_babies->bf, &ptr) == OK) {
	    n = __parse_bin_data_nb(ptr);
	} else
	    break;
	//printf("PTR: %p\n", ptr);
        printNewborn(n);
	free(n);    //TODO should be changed to getRegistersBinFile, when funct
		    //is ready
    }

    if (ptr != NULL) free(ptr);
}

// Closes and frees the .bin file used
void NBDeleteInstance(NEWBORNS* these_babies) {
    if (these_babies->bf != NULL) closeBinFile(these_babies->bf);
    free(these_babies);
}

