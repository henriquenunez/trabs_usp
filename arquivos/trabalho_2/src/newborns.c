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

    nascimento *n = (nascimento*) calloc(1, sizeof(nascimento));

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
        //printf("\tentry n: %d\n", temp - csv_entries);
        n = readCsvEntry(cf);
        appendRegisterBinFile(these_babies->bf, &__build_bin_data_nb, n);
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


/* Field index on search args:
0    id
1    idadeMae
2    data
3    sexo
4    estadoMae
5    estadoBebe
6    cidadeMae
7    cidadeBebe
*/

nascimento* __parse_data_key_value_based_nb(STRING_PAIR_VECTOR key_val_vec) {
    //Here we are expecting a vector of STRING_PAIR.
    int id = -1;
    int idadeMae = -1;
    char date[11] = {0};
    char sexo = '0';
    char estadoMae[4] = {0};
    char estadoBebe[4] = {0};
    char cidadeMae[99] = {0};
    char cidadeBebe[99] = {0};

    #define KVP (key_val_vec.data[i])
    for (int i = 0; i < key_val_vec.size; ++i)
    {
	printf("Filter is {%s} {%s}\n", KVP.key, KVP.value);
        //Accessing ith pointer of our vector.
        if (strcmp(KVP.key, "cidadeMae") == 0) {//This entry is for cidadeMae
            strcpy(cidadeMae, (char*)KVP.value); //Copying into buffer
            continue; }

        if (strcmp(KVP.key, "cidadeBebe") == 0) {//This entry is for cidadeBebe
	    strcpy(cidadeBebe, (char*)KVP.value); //Copying into buffer
            continue; }

        if (strcmp(KVP.key, "idNascimento") == 0) {//This entry is for idNascimento
            id = atoi((char*)KVP.value);
            continue; }

        if (strcmp(KVP.key, "idadeMae") == 0) {//This entry is for idadeMae
            idadeMae = atoi((char*)KVP.value);
            continue; }

        if (strcmp(KVP.key, "dataNascimento") == 0) {//This entry is for dataNascimento
            strncpy(date, (char*)KVP.value, 10); //Copying into buffer
            continue; }

        if (strcmp(KVP.key, "sexoBebe") == 0) {//This entry is for sexoBebe
            sexo = ((char*)KVP.value)[0];
            continue; }

        if (strcmp(KVP.key, "estadoMae") == 0) {//This entry is for estadoMae
            strncpy(estadoMae, (char*)KVP.value, 2);
            continue; }

        if (strcmp(KVP.key, "estadoBebe") == 0) {//This entry is for estadoBebe
            strncpy(estadoBebe, (char*)KVP.value, 2);
            continue; }
        return NULL; //No rules for the filter...
    }
    #undef KVP

    return createNascimento(id,
                idadeMae,
                date,
                sexo,
                estadoMae,
                estadoBebe,
                cidadeMae,
                cidadeBebe);
}

// Searchs for register that matches fields.
nb_err_t NBSearchMatchingFields(NEWBORNS* these_babies, STRING_PAIR_VECTOR args) {
    //Receives a STRING_PAIR_VECTOR
    nascimento* filter;

    filter = __parse_data_key_value_based_nb(args);
    if (filter == NULL) {
        //Filter wrong.
        return NOT_FOUND;
    }

    //Iter through binary file.
    size_t nregs;   //Number of registers retrieved from file
    nascimento *n;  //Temporary structure
    void* ptr = NULL;   //Ptr to receive data

    nregs = getNumRegistersBinFile(these_babies->bf);

    printf("SEARCH RESULTS\n");
/*
printf("filter:\n%d\n%d\n%s\n%c\n%s\n%s\n%s\n%s\n", filter->id,
						    filter->idadeMae,
						    filter->data,
						    filter->sexo,
						    filter->estadoMae,
						    filter->estadoBebe,
						    filter->cidadeMae,
						    filter->cidadeBebe);

*/
    for(int i = 0 ; i < nregs; i++) {

        //Retrieving register of given index.
        if (searchRegisterBinFile(these_babies->bf, i, &ptr) != OK) {
                return NOT_FOUND;
        }
        //Parsing acquired data.
        n = __parse_bin_data_nb(ptr);

	//Applying filter.
        if( ( (filter->id != -1) ? filter->id == n->id : 1) &&

            ( (filter->idadeMae != -1) ? filter->idadeMae == n->idadeMae : 1) &&

            ( (filter->data[0] != 0) ? strcmp(filter->data, n->data) == 0  : 1) &&

            ( (filter->sexo != '0') ? filter->sexo == n->sexo : 1) &&

            ( (filter->estadoMae[0] != 0) ?
                            strcmp(filter->estadoMae, n->estadoMae) == 0  : 1) &&

            (filter->estadoBebe[0] != 0 ?
                            strcmp(filter->estadoBebe, n->estadoBebe) == 0 : 1) &&

            (filter->cidadeMae[0] != 0 ?
                            strcmp(filter->cidadeMae, n->cidadeMae) == 0 : 1) &&

            (filter->cidadeBebe[0] != 0 ?
		((n->cidadeBebe[0] != 0) ?
		    (strcmp(filter->cidadeBebe, n->cidadeBebe)) == 0 : 0) : 1)
            ) {
            //TODO: se o nasicmento tem capo de string nula, ta retornando 0. tem q checar
                printNewborn(n);
        }

        free(n);
    }

    if (ptr != NULL) free(ptr);
    free(filter);
}

nb_err_t NBSearchByRegisterNumber(NEWBORNS* these_babies, int reg_number) {
    void* ptr = NULL;
    nascimento* this_baby;

    if (searchRegisterBinFile(these_babies->bf, reg_number, &ptr) != OK) {
        return NOT_FOUND;
    }

    this_baby = __parse_bin_data_nb(ptr); //Parse acquired data.
    printNewborn(this_baby);

    //Freeing allocated data.
    free(this_baby);
    free(ptr);
}
