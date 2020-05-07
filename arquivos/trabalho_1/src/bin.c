#include "bin.h"
#include <string.h>

#define HEADER_SIZE 128

struct _bin_file {
    FILE* fp;
//    size_t header_size
    size_t register_size;
    size_t current_rrn_index;
    void* header;
};

/**********************************************************************
 * Funções relativas ao header.
 * Como o header é uma 'ferramenta administrativa' do banco, estas funções
 * são de domínio privado para que as atualizações dos dados não sejam
 * feitas de maneira inadequada.
 * ********************************************************************/

//Cria o header inicial quando não existe arquivo
#define __get_status_bin(bfile) ( ((char*)bfile->header)[0] )
#define __get_rrn_next_register_bin(bfile) ( *((int*)(bfile->header+1)) )
#define __get_num_registers_bin(bfile)	   ( *((int*)(bfile->header+5)) )

void __update_header_bin(BIN_FILE* this_file) {
    rewind(this_file->fp);
    fwrite(this_file->header, HEADER_SIZE, 1, this_file->fp);
}

void __refresh_header_bin(BIN_FILE* this_file) {
    rewind(this_file->fp);
    fread(this_file->header, HEADER_SIZE, 1, this_file->fp);
}

void __init_header_bin(BIN_FILE* this_file) {
    char header_buffer[HEADER_SIZE];

    header_buffer[0] = '1';
    memset(header_buffer + 1, 0x0, 16);
    memset(header_buffer + 17, 0x24, HEADER_SIZE - 17); //Fills with garbage
    memcpy(this_file->header, header_buffer, HEADER_SIZE);
    __update_header_bin(this_file);
    //printf("INIT RRN is: %d\n", __get_rrn_next_register_bin(this_file));
}

//Troca o status do header
void __toggle_status_bin(BIN_FILE* this_file) {

    char status = __get_status_bin(this_file);

    if(status == '1') {
        ((char*)this_file->header)[0] = '0';
    } else {
        ((char*)this_file->header)[0] = '1';
    }
}

//Increases next register RRN
void __increase_rrn_next_register_bin(BIN_FILE* this_file) {
    int nrrn = __get_rrn_next_register_bin(this_file);
    nrrn++;
    memcpy(this_file->header + 1, &nrrn, sizeof(int));
    //printf("rrn tried to put %d>>%d\n", nrrn, *((int*)(this_file->header + 1)));
}

//Aumenta o contador numeroRegistrosInseridos
void __increase_num_registers_bin(BIN_FILE* this_file) {
    int nri = __get_num_registers_bin(this_file);
    nri++;
    memcpy(this_file->header + 5, &nri, sizeof(int));
    //printf("nri tried to put %d>>%d\n", nri, *((int*)(this_file->header + 5)));
}

//Retorna o registro baseado no rrn
void __recover_register_bin(BIN_FILE* this_file, void** ret) {
    fseek(  this_file->fp,
	    HEADER_SIZE+this_file->current_rrn_index*this_file->register_size,
	    SEEK_SET);

    fread(  *ret, this_file->register_size, 1, this_file->fp);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*EXPOSED FUNCTIONS*/

/*Open and close binary file*/
BIN_FILE* openBinFile(const char* filename, size_t register_size) {
    BIN_FILE* ret_file;

    ret_file = (BIN_FILE*) malloc(sizeof(BIN_FILE));

    //Tries to create file for update.
    ret_file->fp = fopen(filename, "w+bx");
    ret_file->header = malloc(HEADER_SIZE);

    //In case of file existing, try to open on read/update
    if(ret_file->fp == NULL) {
	ret_file->fp = fopen(filename, "r+b");
	//printf("File exists!\n");
    } else {
	//File does not exist in first place. Initializes header.
	 __init_header_bin(ret_file);
	//printf("File did not exist!\n");
    }

    //In case error, deallocate resources and leave
    if(ret_file->fp == NULL) {
	closeBinFile(ret_file);
	return NULL;
    }

    //Puts header into working buffer
    __refresh_header_bin(ret_file);
    ret_file->register_size = register_size;
    ret_file->current_rrn_index = 0;

    return ret_file;
}

//Frees allocated heap memory and closes file
bin_err_t closeBinFile(BIN_FILE* this_file) {
    fclose(this_file->fp);
    free(this_file->header);
    free(this_file);

    return OK;
}

//Appends register to binary file
bin_err_t appendRegisterBinFile(
			BIN_FILE* this_file,
			void*(*insert_func)(void* data),
			void* ins_data) {
    void* data_to_be_written;
    int next_reg_rrn;

    //Gets next position to be written
    next_reg_rrn = __get_rrn_next_register_bin(this_file);

    //Logically toggles header and immediately updates header in file
    __toggle_status_bin(this_file);
    __update_header_bin(this_file);

    //TODO error checking
    data_to_be_written = insert_func(ins_data);
    fseek(  this_file->fp,
	    HEADER_SIZE + next_reg_rrn * this_file->register_size,
	    SEEK_SET);

    //printf("SEEK is: %d ", ftell(this_file->fp));
    //printf("Offset is: %d\n", next_reg_rrn*this_file->register_size);
    fwrite(data_to_be_written, this_file->register_size, 1, this_file->fp);

    //Updating header and writing it
    __increase_num_registers_bin(this_file);
    __increase_rrn_next_register_bin(this_file);
    __toggle_status_bin(this_file);
    __update_header_bin(this_file);

    //Refreshing written header, just to be sure
    __refresh_header_bin(this_file);

    free(data_to_be_written);

    //printf("number of registers: %d\n", __get_num_registers_bin(this_file));

    return OK;
}

bin_err_t getRegistersBinFile(BIN_FILE* this_file, void** ret) {

    if (*ret != NULL) free(*ret);

    //Tests whether there are no more registers to fetch, and resets index
    if (this_file->current_rrn_index >= __get_num_registers_bin(this_file) ) {
	*ret = NULL;
	this_file->current_rrn_index = 0;
	return END_OF_FILE;
    }

    *ret = malloc(this_file->register_size);

    __recover_register_bin(this_file, ret);
    this_file->current_rrn_index++;

    return OK;
}

size_t getNumRegistersBinFile(BIN_FILE* this_file) {
    return __get_num_registers_bin(this_file);
}