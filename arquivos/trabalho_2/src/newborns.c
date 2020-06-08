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

    // Theses values are helpers, so we know whether
    // a value is null or not.
    char nullId;
    char nullIdadeMae;
    char nullData;
    char nullSexo;
    char nullEstadoMae;
    char nullEstadoBebe;
    char nullCidadeMae;
    char nullCidadeBebe;
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
	// printf("Inserindo BB %s em %d\n", n->cidadeBebe, rrn);
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

    //Null values
    char nullId = 0;
    char nullIdadeMae = 0;
    char nullData = 0;
    char nullSexo = 0;
    char nullEstadoMae = 0;
    char nullEstadoBebe = 0;
    char nullCidadeMae = 0;
    char nullCidadeBebe = 0;

    /* The logic here is the following:
	- If a value is NOT given, null* will be 0, and the reference value will
	  be the default one (i.e. -1 for 'id', "\0\0\0\0\0" for string.)
	- The filter will first check for the value to be NULL (null* == 1), if
	  null, the filter will try to find the very default value.
	- In case field is not NULL, the filter will compare both values.
    */

    #define KVP (key_val_vec.data[i])
    for (int i = 0; i < key_val_vec.size; ++i)
    {
	// printf("Filter is {%s} {%s}\n", KVP.key, KVP.value);
        //Accessing ith pointer of our vector.
        if (strcmp(KVP.key, "cidadeMae") == 0) {//This entry is for cidadeMae
	    if (strlen(KVP.value) == 0)
		nullCidadeMae = 1;
	    else
		strcpy(cidadeMae, (char*)KVP.value); //Copying into buffer
            continue;
	}

        if (strcmp(KVP.key, "cidadeBebe") == 0) {//This entry is for cidadeBebe
	    if (strlen(KVP.value) == 0)
		nullCidadeBebe = 1;
	    else
	        strcpy(cidadeBebe, (char*)KVP.value); //Copying into buffer
            continue;
	}

        if (strcmp(KVP.key, "idNascimento") == 0) {//This entry is for idNascimento
            if (strlen(KVP.value) == 0)
		nullId = 1;
	    else
		id = atoi((char*)KVP.value);
            continue;
	}

        if (strcmp(KVP.key, "idadeMae") == 0) {//This entry is for idadeMae
 	    if (strlen(KVP.value) == 0)
		nullIdadeMae = 1;
	    else
		idadeMae = atoi((char*)KVP.value);
            continue;
	}

        if (strcmp(KVP.key, "dataNascimento") == 0) {//This entry is for dataNascimento
 	    if (strlen(KVP.value) == 0)
		nullData = 1;
	    else
		strncpy(date, (char*)KVP.value, 10); //Copying into buffer
            continue;
	}

        if (strcmp(KVP.key, "sexoBebe") == 0) {//This entry is for sexoBebe
	    if (strlen(KVP.value) == 0)
		nullSexo = 1;
	    else
		sexo = ((char*)KVP.value)[0];
            continue;
	}

        if (strcmp(KVP.key, "estadoMae") == 0) {//This entry is for estadoMae
            if (strlen(KVP.value) == 0)
		nullEstadoMae = 1;
	    else
		strncpy(estadoMae, (char*)KVP.value, 2);
            continue;
	}

        if (strcmp(KVP.key, "estadoBebe") == 0) {//This entry is for estadoBebe
	    if (strlen(KVP.value) == 0)
		nullEstadoBebe = 1;
	    else
		strncpy(estadoBebe, (char*)KVP.value, 2);
            continue;
	}

	return NULL; //No rules for the filter...
    }
    #undef KVP

    nascimento *n;

    n = createNascimento(id,
                idadeMae,
                date,
                sexo,
                estadoMae,
                estadoBebe,
                cidadeMae,
                cidadeBebe);


    n->nullId	       = nullId;
    n->nullIdadeMae    = nullIdadeMae;
    n->nullData	       = nullData;
    n->nullSexo	       = nullSexo;
    n->nullEstadoMae   = nullEstadoMae;
    n->nullEstadoBebe  = nullEstadoBebe;
    n->nullCidadeMae   = nullCidadeMae;
    n->nullCidadeBebe  = nullCidadeBebe;

    return n;
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

    bin_err_t get_registers_ret;

    //Resetting file iteration.
    resetFileIterBinFile(these_babies->bf);

    nregs = getNumRegistersBinFile(these_babies->bf) + 5;

    for(int i = 0 ; i < nregs; i++){

	get_registers_ret = getRegistersBinFile(these_babies->bf, &ptr);
	if (get_registers_ret == OK) {
	    n = __parse_bin_data_nb(ptr);
	} else if(get_registers_ret == REMOVED_ENTRY) {
	    continue;
	} else break;
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

//This may not be the most beautiful one. Searchs if current baby matches
//filter.
int __apply_filter(nascimento *n, nascimento *filter) {

/*
printf("filter nulls:\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", filter->nullId,
						    filter->nullIdadeMae,
						    filter->nullData,
						    filter->nullSexo,
						    filter->nullEstadoMae,
						    filter->nullEstadoBebe,
						    filter->nullCidadeMae,
						    filter->nullCidadeBebe);

printf("filter:\n%d\n%d\n%s\n%c\n%s\n%s\n%s\n%s\n", filter->id,
						    filter->idadeMae,
						    filter->data,
						    filter->sexo,
						    filter->estadoMae,
						    filter->estadoBebe,
						    filter->cidadeMae,
						    filter->cidadeBebe);

printf("n:\n%d\n%d\n%s\n%c\n%s\n%s\n%s\n%s\n",	    n->id,
						    n->idadeMae,
						    n->data,
						    n->sexo,
						    n->estadoMae,
						    n->estadoBebe,
						    n->cidadeMae,
						    n->cidadeBebe);

*/

char m = 0;

m= (
    //If filter IS NULL, match null id (-1).
    ((filter->nullId) ? (n->id == -1) :
	//Else see if value is nonexistant.
	( (filter->id != -1) ? filter->id == n->id : 1)) &&

    //If filter IS NULL, match null idadeMae (-1).
    ((filter->nullIdadeMae) ? (n->idadeMae == -1) :
	//Else see if value is nonexistant.
        ( (filter->idadeMae != -1) ? filter->idadeMae == n->idadeMae : 1)) &&

    //If filter IS NULL, match null data ("\0......").
    ((filter->nullData) ? (n->data[0] == 0) :
	//Else see if value is nonexistant.
	( (filter->data[0] != 0) ?
	    (n->data[0] != 0 ?
		strcmp(filter->data, n->data) == 0 : 0)  : 1)) &&

    //If filter IS NULL, match null sexo ('0').
    ((filter->nullSexo) ? (n->sexo == '0') :
	//Else see if value is nonexistant.
	( (filter->sexo != '0') ? filter->sexo == n->sexo : 1)) &&

    //If filter IS NULL, match null estadoMae ("\0...").
    ((filter->nullEstadoMae) ? (n->estadoMae[0] == 0) :
	//Else see if value is nonexistant.
	( (filter->estadoMae[0] != 0) ?
	    (n->estadoMae[0] != 0 ?
		strcmp(filter->estadoMae, n->estadoMae) == 0 : 0)  : 1)) &&

    //If filter IS NULL, match null estadoBebe ("\0...").
    ((filter->nullEstadoBebe) ? (n->estadoBebe[0] == 0) :
	//Else see if value is nonexistant.
	(filter->estadoBebe[0] != 0 ?
	    (n->estadoBebe[0] != 0 ?
		strcmp(filter->estadoBebe, n->estadoBebe) == 0 : 0) : 1)) &&

    //If filter IS NULL, match null cidadeMae ("\0...").
    ((filter->nullCidadeMae) ? (n->cidadeMae[0] == 0) :
	//Else see if value is nonexistant.
	(filter->cidadeMae[0] != 0 ?
	    (n->cidadeMae[0] != 0 ?
		strcmp(filter->cidadeMae, n->cidadeMae) == 0 : 0) : 1)) &&

    //If filter IS NULL, match null cidadeBebe ("\0...").
    ((filter->nullCidadeBebe) ? (n->cidadeBebe[0] == 0) :
	//Else see if value is nonexistant.
	(filter->cidadeBebe[0] != 0 ?
	    (n->cidadeBebe[0] != 0 ?
		strcmp(filter->cidadeBebe, n->cidadeBebe) == 0 : 0) : 1))
    );

//printf("Matches ? {%d}\n", m);

    return m;
}

// Searchs for register that matches fields.
nb_err_t NBSearchMatchingFields(NEWBORNS* these_babies, STRING_PAIR_VECTOR args) {
    //Receives a STRING_PAIR_VECTOR
    nascimento* filter;
    int any_found_flag = 0;

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

    // printf("SEARCH RESULTS\n");
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
        if(__apply_filter(n, filter)) {
                printNewborn(n);
		any_found_flag = 1;
        }

        free(n);
    }

    if (ptr != NULL) free(ptr);
    free(filter);

    if (any_found_flag) return NB_OK;
    return NOT_FOUND;
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

    return NB_OK;
}

nb_err_t NBRemoveMatchingFields(NEWBORNS* these_babies, STRING_PAIR_VECTOR args) {
    //Receives a STRING_PAIR_VECTOR
    nascimento* filter;

    filter = __parse_data_key_value_based_nb(args);

    if (filter == NULL) {
        //Filter wrong.
        return NOT_FOUND; //TODO define some error.
    }

    //Iter through binary file.
    size_t nregs;   //Number of registers retrieved from file
    nascimento *n;  //Temporary structure
    void* ptr = NULL;   //Ptr to receive data

    nregs = getNumRegistersBinFile(these_babies->bf);

    //i here is the rrn of the current register.
    for(int i = 0 ; i < nregs; i++) {
        //Retrieving register of given index.
        // if (searchRegisterBinFile(these_babies->bf, i, &ptr) != OK) {
					bin_err_t response = searchRegisterBinFile(these_babies->bf, i, &ptr);
					if (response != OK) {
				// printf("%d\n", response);
								if(response == REMOVED_ENTRY) continue;
                return NOT_FOUND; //TODO DEFINE ERROR
        }
        //Parsing acquired data.
        n = __parse_bin_data_nb(ptr);

	//Applying filter.
        if(__apply_filter(n, filter)) {
                //If matches criteria, remove and exit loop.
		removeRegistersBinFile(these_babies->bf, i);
		// printf(">>>");
		// printNewborn(n); //Removed register.
		free(n);
		break;
        }

        free(n);
    }

    if (ptr != NULL) free(ptr);
    free(filter);

    return NB_OK;
}

// Inserts newborn at end.
nb_err_t NBInsertNewbornAtEnd(NEWBORNS* these_babies, STRING_PAIR_VECTOR args) {
    //First, we build data from args.
    nascimento *new_baby;

    new_baby = __parse_data_key_value_based_nb(args);
    appendRegisterBinFile(these_babies->bf, &__build_bin_data_nb, new_baby);

    free(new_baby);
}

//#undef DEBUG

// Updating fields of current register.
void* __update_bin_data_nb(void *n_data, void *curr_data) {
    int offset = 0;
    int aux;

    #define NAS ((nascimento*)n_data) //n_data is a pointer to a struct.
    #define BUFFOFF (curr_data + offset)

    if (strlen(NAS->cidadeMae)) {
	*((int*) BUFFOFF) = strlen(NAS->cidadeMae);
    } else if(NAS->nullCidadeMae) {
	*((int*) BUFFOFF) = 0;
    }
    offset += sizeof(int);

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif

    if (strlen(NAS->cidadeBebe)) {
	*((int*) BUFFOFF) = strlen(NAS->cidadeBebe);
    } else if(NAS->nullCidadeBebe) {
	*((int*) BUFFOFF) = 0;
    }
    offset += sizeof(int);

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    // printf("offset: %d\n", offset);

    /*Variable length fields max size: 96*/
    if (strlen(NAS->cidadeMae)) {
        memcpy(BUFFOFF, NAS->cidadeMae, strlen(NAS->cidadeMae));
	offset += strlen(NAS->cidadeMae);
    } else
	offset += *((int*)(curr_data + 0));
	//Getting strlen of field. Will be 0 if field was NULL.

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    // printf("offset: %d\n", offset);

    if (strlen(NAS->cidadeBebe)) {
        memcpy(BUFFOFF, NAS->cidadeBebe, strlen(NAS->cidadeBebe));
	offset += strlen(NAS->cidadeBebe);
    } else
	offset += *((int*)(curr_data + sizeof(int)));
	//Getting strlen of field. Will be 0 if field was NULL.

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    // printf("offset: %d\n", offset);

    /* In my opinion, this function MUST fill remaining space with garbage, but
     * according to the specification, there must be the previous bytes in this
     * very space.
    memset(BUFFOFF,
	    0x24,
	VAR_FIELDS_MAX_LEN -
	  (((strlen(NAS->cidadeMae) > 0)?(strlen(NAS->cidadeMae)):0) +
	  ((strlen(NAS->cidadeBebe) > 0)?(strlen(NAS->cidadeBebe)):0))
	);
    */

    offset +=
	VAR_FIELDS_MAX_LEN -
	    (*((int*)(curr_data + 0)) + //cidadeMae length
	    *((int*)(curr_data + sizeof(int)))); //cidadeMae length

    // printf("offset: %d\n", offset);

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    /*Static fields*/
    if (NAS->id != -1) //If id is not null
        *((int*) BUFFOFF) = NAS->id;
    else if (NAS->nullId)
        *((int*) BUFFOFF) = 0;

    offset += sizeof(int);
    // printf("offset: %d\n", offset);

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    if (NAS->idadeMae != -1) //If idadeMae is not null
        *((int*) BUFFOFF) = NAS->idadeMae;
    else if (NAS->nullIdadeMae)
        *((int*) BUFFOFF) = -1;
    offset += sizeof(int);
    // printf("offset: %d\n", offset);

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    /*Date string*/
    if (strlen(NAS->data)) {
	memcpy(BUFFOFF, NAS->data, 10);
    } else if (NAS->nullData) {
	memcpy(BUFFOFF, "\0$$$$$$$$$", 10);
    }
    offset += 10;
    // printf("offset: %d\n", offset);

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    //TODO maybe weird stuff will happen here, due to the '0' stuff.
    if (NAS->sexo != '0')
	*((char*) BUFFOFF) = NAS->sexo;
    else if (NAS->nullSexo)
        *((char*) BUFFOFF) = '0';
    offset += 1;

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    if (strlen(NAS->estadoMae))
	memcpy(BUFFOFF, NAS->estadoMae, 2);
    else if (NAS->nullEstadoMae)
	memcpy(BUFFOFF, "\0$", 2);
    offset += 2;

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif


    if (strlen(NAS->estadoBebe))
	memcpy(BUFFOFF, NAS->estadoBebe, 2);
    else if (NAS->nullEstadoBebe)
	memcpy(BUFFOFF, "\0$", 2);

    offset += 2;

    #ifdef DEBUG
    printf("offset: %d\n", offset);
    #endif

    #undef NAS
    #undef BUFFOFF

    return curr_data;
}

nb_err_t NBUpdateByRegisterNumber(NEWBORNS* these_babies,
				    int rrn,
				    STRING_PAIR_VECTOR args) {
    nascimento *update_fields_baby;
    void* current_baby_bin = NULL;

    //First, we build data from args.
    update_fields_baby = __parse_data_key_value_based_nb(args);
    if (update_fields_baby == NULL) return FILTER_ERROR;

    //Retrieve binary data.

    updateRegisterBinFile(these_babies->bf,
			    &__update_bin_data_nb,
			    update_fields_baby,
			    rrn);

    free(update_fields_baby);
}

