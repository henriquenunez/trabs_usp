#include <stdio.h>
#include <stdlib.h>

#include "bin.h"

#define REG_SIZE 40
#define BUFF_LEN 20
int idk;

typedef struct _data_writing DATA;

struct _data_writing {
    char buffer[BUFF_LEN];
};

void* getDataForWriting(void* this_data) {
    void* ret_data;
    char* databuffer = ((DATA*)this_data)->buffer;

    ret_data = malloc(REG_SIZE);

    memcpy(ret_data, databuffer, BUFF_LEN);
    memset(ret_data + BUFF_LEN, 0x24, REG_SIZE - BUFF_LEN);

    return ret_data;
}

void printAcquiredData(void* this_data) {
    char temp_buffer[BUFF_LEN + 10] = {0};

    memcpy(temp_buffer, this_data, BUFF_LEN);
    printf(temp_buffer);
}

int main() {
    BIN_FILE* this_bin_file;
    struct _data_writing DATA_TO_WRITE;
    int times = 20;
    void* hello = NULL;

    this_bin_file = openBinFile("test_bin.bin", REG_SIZE);

    while (times--) {
	sprintf(DATA_TO_WRITE.buffer, "TIMES:%10d\n", times);
	insertRegisterBinFile(	this_bin_file,
				&getDataForWriting,
				&DATA_TO_WRITE,
				-1);
    }

    closeBinFile(this_bin_file);

    //Acquire data now.

    times = 20;

    this_bin_file = openBinFile("test_bin.bin", REG_SIZE);
    while (times--) {
	if (getRegistersBinFile(this_bin_file, &hello) != OK) continue;
	printAcquiredData(hello);
    }

    free(hello);

    closeBinFile(this_bin_file);
    return 0;
}

