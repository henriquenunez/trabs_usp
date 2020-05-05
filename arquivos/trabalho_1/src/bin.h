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
    WRITE_ERROR
};


BIN_FILE* openBinFile(const char* filename, size_t register_size);
bin_err_t closeBinFile(BIN_FILE*);

/*Insert a generic register

appendRegisterBinFile parameters:
-insert_func: a function that receives a

*/
bin_err_t appendRegisterBinFile(BIN_FILE*,
				void*(*insert_func)(void* data),
				void* ins_data);

bin_err_t getRegistersBinFile(BIN_FILE*, void** ret);

size_t getNumRegistersBinFile(BIN_FILE*);

#endif

