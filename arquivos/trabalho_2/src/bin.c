#include "bin.h"
#include <string.h>

#define HEADER_SIZE 128 //In this implementation, header has 128B

struct _bin_file {
    FILE* fp;			//Pointer to actual file
    size_t register_size;	//Register size, defined at instantiation
    size_t current_rrn_index;	//Variable for making accesses easier
    void* header;		//Header buffer, for easier manipulation.
};

/**********************************************************************
 * Funções relativas ao header.
 * Como o header é uma 'ferramenta administrativa' do banco, estas funções
 * são de domínio privado para que as atualizações dos dados não sejam
 * feitas de maneira inadequada.
 * ********************************************************************/

//Macros that access elements of header buffer, in BIN_FILE struct
#define __get_status_bin(bfile) ( ((char*)bfile->header)[0] )
#define __get_rrn_next_register_bin(bfile) ( *((int*)(bfile->header+1)) )
#define __get_num_registers_bin(bfile)	   ( *((int*)(bfile->header+5)) )
#define __get_num_deleted_registers_bin(bfile)	   ( *((int*)(bfile->header+9)) )
#define __get_num_updated_registers_bin(bfile)	   ( *((int*)(bfile->header+13)) )

//Helper macros
#define __byte_offset_next_rrn_bin(bfile)\
		(HEADER_SIZE +(bfile->register_size * \
					__get_rrn_next_register_bin(bfile)))
#define __byte_offset_curr_rrn_index_bin(bfile)\
		(HEADER_SIZE +(bfile->register_size * bfile->current_rrn_index))

//Writes header buffer into file
void __update_header_bin(BIN_FILE* this_file) {
    rewind(this_file->fp);
    fwrite(this_file->header, HEADER_SIZE, 1, this_file->fp);
}

//Reads header from file into buffer
void __refresh_header_bin(BIN_FILE* this_file) {
    rewind(this_file->fp);
    fread(this_file->header, HEADER_SIZE, 1, this_file->fp);
}

//Creates header when file doesn't exist
void __init_header_bin(BIN_FILE* this_file) {
    char header_buffer[HEADER_SIZE];

    header_buffer[0] = '1';
    memset(header_buffer + 1, 0x0, 16);
    memset(header_buffer + 17, 0x24, HEADER_SIZE - 17); //Fills with garbage
    memcpy(this_file->header, header_buffer, HEADER_SIZE);
    __update_header_bin(this_file);
    //printf("INIT RRN is: %d\n", __get_rrn_next_register_bin(this_file));
}

//Toggles header status
void __toggle_status_bin(BIN_FILE* this_file) {

    char status = __get_status_bin(this_file);

    if(status == '1') {
        ((char*)this_file->header)[0] = '0';
    } else {
        ((char*)this_file->header)[0] = '1';
    }
}

//Increases next register RRN
void __change_rrn_next_register_bin(BIN_FILE* this_file, int step) {
    int nrrn = __get_rrn_next_register_bin(this_file);
    nrrn+=step;
    memcpy(this_file->header + 1, &nrrn, sizeof(int));
    //printf("rrn tried to put %d>>%d\n", nrrn, *((int*)(this_file->header + 1)));
}

// Increases the number of inserted registers
void __change_num_registers_bin(BIN_FILE* this_file, int step) {
    int nri = __get_num_registers_bin(this_file);
    nri+=step;
    memcpy(this_file->header + 5, &nri, sizeof(int));
    //printf("nri tried to put %d>>%d\n", nri, *((int*)(this_file->header + 5)));
}

// Increases the number of deleted registers
void __change_num_deleted_registers_bin(BIN_FILE* this_file, int step) {
    int nri = __get_num_deleted_registers_bin(this_file);
    nri+=step;
    memcpy(this_file->header + 9, &nri, sizeof(int));
    //printf("nri tried to put %d>>%d\n", nri, *((int*)(this_file->header + 5)));
}

// Increases the number of updated registers
void __change_num_updated_registers_bin(BIN_FILE* this_file, int step) {
    int nri = __get_num_updated_registers_bin(this_file);
    nri+=step;
    memcpy(this_file->header + 13, &nri, sizeof(int));
    //printf("nri tried to put %d>>%d\n", nri, *((int*)(this_file->header + 5)));
}

//Increases next register RRN
void __increase_rrn_next_register_bin(BIN_FILE* this_file) {
    int nrrn = __get_rrn_next_register_bin(this_file);
    nrrn++;
    memcpy(this_file->header + 1, &nrrn, sizeof(int));
    //printf("rrn tried to put %d>>%d\n", nrrn, *((int*)(this_file->header + 1)));
}

// Increases the number of inserted registers
void __increase_num_registers_bin(BIN_FILE* this_file) {
    int nri = __get_num_registers_bin(this_file);
    nri++;
    memcpy(this_file->header + 5, &nri, sizeof(int));
    //printf("nri tried to put %d>>%d\n", nri, *((int*)(this_file->header + 5)));
}

//Returns entry based on rrn
void __recover_register_bin(BIN_FILE* this_file, void** ret) {
    if(ftell(this_file->fp) != __byte_offset_curr_rrn_index_bin(this_file))
    {
        fseek(  this_file->fp,
                __byte_offset_curr_rrn_index_bin(this_file),
                SEEK_SET);
    }

    fread(  *ret, this_file->register_size, 1, this_file->fp);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/*EXPOSED FUNCTIONS*/

// Opens file
BIN_FILE* openBinFile(const char* filename, size_t register_size) {
    BIN_FILE* ret_file;

    //Allocates space for struct
    ret_file = (BIN_FILE*) malloc(sizeof(BIN_FILE));

    //Allocates space for header buffer
    ret_file->header = malloc(HEADER_SIZE);

    //Tries to create file for update.
    ret_file->fp = fopen(filename, "r+b");

    //In case of file existing, try to open on read/update
    if(ret_file->fp == NULL) {
	ret_file->fp = fopen(filename, "w+bx");
	//printf("File did not exist!\n");
	 __init_header_bin(ret_file);
    }

    //In case of error, deallocate resources and leave
    if(ret_file->fp == NULL) {
	closeBinFile(ret_file);
	return NULL;
    }

    //Puts header from file into buffer
    __refresh_header_bin(ret_file);

    //Check file consistency
    if (__get_status_bin(ret_file) != '1') {

        //Will just free resources and close file, no header toggling.
        fclose(ret_file->fp);
        free(ret_file->header);
        free(ret_file);
	   
        return NULL;
    }

    //Defines register size
    ret_file->register_size = register_size;

    //Zero on RRN, so we can iter on registers from the beginning
    ret_file->current_rrn_index = 0;

    //Toggling status and writing it to file.
    __toggle_status_bin(ret_file);
    __update_header_bin(ret_file);

    return ret_file;
}

//Frees allocated heap memory and closes file
bin_err_t closeBinFile(BIN_FILE* this_file) {
    //Sets status to 1 on RAM and writes it to file.
    __toggle_status_bin(this_file);
    __update_header_bin(this_file);

    fclose(this_file->fp);
    free(this_file->header);
    free(this_file);

    return OK;
}

//Appends entry to binary file
bin_err_t appendRegisterBinFile(
            BIN_FILE* this_file,
            void*(*insert_func)(void* data),
            void* ins_data) {
    void* data_to_be_written;

    //TODO error checking
    data_to_be_written = insert_func(ins_data);
    if (data_to_be_written == NULL)
    return WRITE_ERROR;

    /*Checking if current cursor position is the position where we
    want to write
    */
    if(ftell(this_file->fp) != __byte_offset_next_rrn_bin(this_file))
    {
    fseek(  this_file->fp,
            __byte_offset_next_rrn_bin(this_file),
        SEEK_SET);
    } 

    //printf("RAM SEEK is: %d\n", __byte_offset_next_rrn_bin(this_file));
    //printf("FP  SEEK is: %d\n\n",  ftell(this_file->fp));
/*
    fseek(  this_file->fp,
        __byte_offset_rrn_bin(this_file),
        SEEK_SET);
*/

    //printf("SEEK is: %d ", ftell(this_file->fp));
    //printf("Offset is: %d\n", next_reg_rrn*this_file->register_size);
    fwrite(data_to_be_written, this_file->register_size, 1, this_file->fp);

    //Updating header on memory
    __increase_num_registers_bin(this_file);
    __increase_rrn_next_register_bin(this_file);

    free(data_to_be_written);

    //printf("number of registers: %d\n", __get_num_registers_bin(this_file));

    return OK;
}

// Insert entry to binary file. Setting rrn value to -1 appends entry to end.
bin_err_t insertRegisterBinFile(
			BIN_FILE* this_file,
			void*(*insert_func)(void* data),
			void* ins_data,
			int rrn) {
    void* data_to_be_written;

    //TODO error checking
    data_to_be_written = insert_func(ins_data);

    if (data_to_be_written == NULL)
	return WRITE_ERROR;

		// printf("rrn: %d\n", rrn);
		// Check if append or insert (append == -1)
    if(rrn == -1){
				// printf("offset: %d\n", __byte_offset_next_rrn_bin(this_file));

			// Navigate to correct position
				if(ftell(this_file->fp) != __byte_offset_next_rrn_bin(this_file))
			{
		fseek(  this_file->fp,
						__byte_offset_next_rrn_bin(this_file),
			SEEK_SET);
			// printf("@ EOF\n");
			// Update header info
			}
			__change_num_registers_bin(this_file, 1);
			__change_rrn_next_register_bin(this_file, 1);
		}else{

			// Sets correct rrn
			this_file->current_rrn_index = rrn;

			// Navigate to correct position
			if(ftell(this_file->fp) != __byte_offset_curr_rrn_index_bin(this_file)){
				fseek(  this_file->fp,
					__byte_offset_curr_rrn_index_bin(this_file),
				SEEK_SET);
				// printf("@ %d\n", rrn);
				// Update header info
			}
				__change_num_updated_registers_bin(this_file, 1);
		}

    //printf("RAM SEEK is: %d\n", __byte_offset_next_rrn_bin(this_file));
    //printf("FP  SEEK is: %d\n\n",  ftell(this_file->fp));
/*
    fseek(  this_file->fp,
	    __byte_offset_rrn_bin(this_file),
	    SEEK_SET);
*/

    //printf("SEEK is: %d ", ftell(this_file->fp));
    //printf("Offset is: %d\n", next_reg_rrn*this_file->register_size);
    fwrite(data_to_be_written, this_file->register_size, 1, this_file->fp);

    // //Updating header on memory
    // __change_num_registers_bin(this_file, 1);
    // __change_rrn_next_register_bin(this_file, 1);

    free(data_to_be_written);

    //printf("number of registers: %d\n", __get_num_registers_bin(this_file));

    return OK;
}

// Update entry on binary file.
bin_err_t updateRegisterBinFile(
			BIN_FILE* this_file,
			void*(*insert_func)(void* data, void* old_bin_data),
			void* ins_data,
			int rrn) {
    
    bin_err_t err_code;
    //void* data_to_be_written;
    void* curr_bin_data = NULL;

    //First, we must retrieve the bin data from given rrn.
    err_code = searchRegisterBinFile(this_file, rrn, &curr_bin_data);
    if (err_code != OK) return err_code;

	curr_bin_data = insert_func(ins_data, curr_bin_data);

//    if (data_to_be_written == NULL)
//	return WRITE_ERROR;

	// printf("rrn: %d\n", rrn);
	// Sets correct rrn
	this_file->current_rrn_index = rrn;

	// Navigate to correct position
	if(ftell(this_file->fp) != __byte_offset_curr_rrn_index_bin(this_file)){
		fseek(  this_file->fp,
		__byte_offset_curr_rrn_index_bin(this_file),
		SEEK_SET);
		// printf("@ %d\n", rrn);
		// Update header info
	}
	
	__change_num_updated_registers_bin(this_file, 1);

	//printf("RAM SEEK is: %d\n", __byte_offset_next_rrn_bin(this_file));
	//printf("FP  SEEK is: %d\n\n",  ftell(this_file->fp));
	/*
	fseek(  this_file->fp,
	__byte_offset_rrn_bin(this_file),
	SEEK_SET);
	*/

	//printf("SEEK is: %d ", ftell(this_file->fp));
	//printf("Offset is: %d\n", next_reg_rrn*this_file->register_size);
	fwrite(curr_bin_data, this_file->register_size, 1, this_file->fp);

	//free(data_to_be_written);
	free(curr_bin_data);

    return OK;
}

void resetFileIterBinFile(BIN_FILE* this_file) {
	this_file->current_rrn_index = 0;
}

// Saves an entry to ret buffer and returns status
bin_err_t getRegistersBinFile(BIN_FILE* this_file, void** ret) {

    if (*ret != NULL) free(*ret);
    //TODO handle memory management when last register is read.

    //Tests whether there are no more registers to fetch, and resets index
    if (this_file->current_rrn_index >= __get_num_registers_bin(this_file) ) {
	*ret = NULL;
	this_file->current_rrn_index = 0;
	return END_OF_FILE;
    }

    *ret = malloc(this_file->register_size);

    __recover_register_bin(this_file, ret);
    this_file->current_rrn_index++;

    int firstNum;
    memcpy(&firstNum, *ret, sizeof(int));
    // Checks if first number is -1, returning if entry is deleted or not
    if(firstNum == -1) return REMOVED_ENTRY;

    return OK;
}

// Getter mask for number of entries in file
size_t getNumRegistersBinFile(BIN_FILE* this_file) {
    return __get_num_registers_bin(this_file);
}

// Get by relative register number.
bin_err_t searchRegisterBinFile(BIN_FILE* this_file, size_t rrn, void** ret){

    // Sets RRN in binary file
    this_file->current_rrn_index = rrn;

    // Gets entry in RRN
    return getRegistersBinFile(this_file, ret);

}

// Removes register of the given RRN.
bin_err_t removeRegistersBinFile(BIN_FILE* this_file, size_t rrn){

    //Check if rrn is WITHIN file, leq than last rrn.
    if(rrn > getNumRegistersBinFile(this_file)){
        return END_OF_FILE;
    }
    //fill accordingly, with -1
    this_file->current_rrn_index = rrn;
    // printf("offset: %d\n", __byte_offset_curr_rrn_index_bin(this_file));
    fseek(  this_file->fp,
	        __byte_offset_curr_rrn_index_bin(this_file),
		SEEK_SET);

    putw(-1,  this_file->fp);

    // Update header
    // __change_num_registers_bin(this_file, -1);
		__change_num_deleted_registers_bin(this_file, 1);

}
