#include <stdio.h>
#include <stdlib.h>

#include "bin.h"

#define REG_SIZE 40
#define BUFF_LEN 20


void printAcquiredData(void* this_data) {
    char temp_buffer[BUFF_LEN + 10] = {0};

    memcpy(temp_buffer, this_data, BUFF_LEN);
    printf("%s", temp_buffer);
}

int main() {
    BIN_FILE* this_bin_file;
    void* hello = NULL;

    this_bin_file = openBinFile("delete.bin", REG_SIZE);

    removeRegistersBinFile(this_bin_file, 2);

    closeBinFile(this_bin_file);

    //Acquire data now.

    int times = 3;

    this_bin_file = openBinFile("delete.bin", REG_SIZE);
    printf("Numero de regs: %d\n", getNumRegistersBinFile(this_bin_file));
    while (times--) {
        printf("%d\n", times);
        bin_err_t status = getRegistersBinFile(this_bin_file, &hello);
        printf("status: %d\n", status);
        if (status != OK) {printf("Not OK\n"); continue;};
        printAcquiredData(hello);
    }

    free(hello);

    closeBinFile(this_bin_file);
    return 0;
}