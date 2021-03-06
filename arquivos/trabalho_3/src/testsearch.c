#include <stdio.h>
#include <stdlib.h>

#include "bin.h"

#define REG_SIZE 128

int main() {
    BIN_FILE* this_bin_file;
    void* hello = NULL;

    this_bin_file = openBinFile("delete.bin", REG_SIZE);

    bin_err_t response =  searchRegisterBinFile(this_bin_file, 1, &hello);

    if(response != OK){
        printf("response not ok\n");
        return 1;
    }

    closeBinFile(this_bin_file);

    FILE* fp = fopen("response.bin", "wb");
    fwrite(hello, REG_SIZE, 1, fp);
    fclose(fp);

    free(hello);

    // //Acquire data now.

    // int times = 3;

    // this_bin_file = openBinFile("delete.bin", REG_SIZE);
    // printf("Numero de regs: %ld\n", getNumRegistersBinFile(this_bin_file));
    // while (times--) {
    //     printf("%d\n", times);
    //     bin_err_t status = getRegistersBinFile(this_bin_file, &hello);
    //     printf("status: %d\n", status);
    //     if (status != OK) {printf("Not OK\n"); continue;};
    // }

    // free(hello);

    // closeBinFile(this_bin_file);
    return 0;
}