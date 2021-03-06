#ifndef BIN_FILE_H
#define BIN_FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errno.h"

typedef struct _bin_file BIN_FILE;

typedef enum _bin_error bin_err_t;
enum _bin_error {
    OK,
    END_OF_FILE,
    WRITE_ERROR,
    NO_ENTRY,
    REMOVED_ENTRY
};

//Self-descripting functions.
BIN_FILE* openBinFile(const char* filename, size_t register_size);
bin_err_t closeBinFile(BIN_FILE*);
size_t getNumRegistersBinFile(BIN_FILE*);

/*insertRegisterBinFile parameters:
- insert_func: a function that receives a struct pointed by ins_data
- ins_data: pointer to struct that can be cast into known struct type
- rrn: relative register number for the data to be inserted in.
*/
bin_err_t insertRegisterBinFile(BIN_FILE*,
				void*(*insert_func)(void* data),
				void* ins_data,
				int rrn);

/*updateRegisterBinFile parameters:
- insert_func: a function that receives a struct pointed by ins_data
- ins_data: pointer to struct that can be cast into known struct type
- rrn: relative register number for the data to be inserted in.
*/
bin_err_t updateRegisterBinFile(BIN_FILE*,
				void*(*insert_func)(void*, void*),
				void* ins_data,
				int rrn);



/*appendRegisterBinFile parameters:
- insert_func: a function that receives a struct pointed by ins_data
- ins_data: pointer to struct that can be cast into known struct type
*/
bin_err_t appendRegisterBinFile(
            BIN_FILE* ,
            void*(*insert_func)(void* data),
            void* ins_data);

/* getRegistersBinFile:
Subsequent calls to this function will iterate through the binary file.

parameters:
- ret: GENERIC POINTER, that will point to next register in file,
  following rrn order. By the first call to this function, the value MUST be
  NULL, otherwise it will free some random address. The function handles memory
  management on subsequent calls.
*/
bin_err_t getRegistersBinFile(BIN_FILE*, void** ret);

bin_err_t removeRegistersBinFile(BIN_FILE*, size_t rrn);

bin_err_t searchRegisterBinFile(BIN_FILE* this_file, size_t rrn, void** buff);

void resetFileIterBinFile(BIN_FILE*);
#endif

