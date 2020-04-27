#include <stdio.h>
#include <stdlib.h>

#include "bin.h"

#define REG_SIZE 128
int idk;

struct _data_writing {
    char buffer[20];
};

void* getDataForWriting(void* this_data) {
    void* ret_data;

    ret_data = malloc(REG_SIZE);
    memset(ret_data, REG_SIZE, 0xAB);

    return ret_data;
}

int main() {
    BINFILE* this_bin_file;
    struct _data_writing DATA_TO_WRITE;
    int times = 10;

    this_bin_file = openBinFile("test_bin.bin", REG_SIZE);

    while (times--) {
	sprintf(DATA_TO_WRITE.buffer, "TIMES:%d//", times);
	appendRegisterBinFile(	this_bin_file,
				&getDataForWriting
				&DATA_TO_WRITE);
    }

    closeBinFile(this_bin_file);

    return 0;
}

