#include <stdio.h>
#include <stdlib.h>

#include "bin.h"

#define REG_SIZE 128
int idk;

typedef struct _data_writing DATA;

struct _data_writing {
    char buffer[20];
};

void* getDataForWriting(void* this_data) {
    void* ret_data;
    char* databuffer = ((DATA*)this_data)->buffer;

    ret_data = malloc(REG_SIZE);

    memcpy(ret_data, databuffer, 20);
    memset(ret_data + 20, 0xAB, REG_SIZE - 21);

    return ret_data;
}

int main() {
    BIN_FILE* this_bin_file;
    struct _data_writing DATA_TO_WRITE;
    int times = 20;

    this_bin_file = openBinFile("test_bin.bin", REG_SIZE);

    while (times--) {
	sprintf(DATA_TO_WRITE.buffer, "TIMES:%d//", times);
	appendRegisterBinFile(	this_bin_file,
				&getDataForWriting,
				&DATA_TO_WRITE);
    }

    closeBinFile(this_bin_file);

    return 0;
}

