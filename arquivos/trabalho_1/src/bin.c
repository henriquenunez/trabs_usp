#include "bin.h"
#include <string.h>

#define HEADER_SIZE 128

struct _bin_file {
    FILE* fp;
//    size_t header_size
    size_t register_size;
};

enum _bin_error {
    END_OF_FILE,
    WRITE_ERROR
}
/**********************************************************************
 * Funções relativas ao header.
 * Como o header é uma 'ferramenta administrativa' do banco, estas funções
 * são de domínio privado para que as atualizações dos dados não sejam
 * feitas de maneira inadequada.
 * ********************************************************************/

//Cria o header inicial quando não existe arquivo
void __write_header_bin__write_header(FILE_NODE *fn) {
    char header_buffer[128];

    header_buffer[0] = '1';
    memset(header_buffer + 1, 16, 0);
    memset(header_buffer + 17, HEADER_SIZE - 17, '$'); //Fills with garbage
    //fwrite(header_buffer, 128, this_file);
}

//Get o status do header
char __get_status_bin(FILE_NODE *fn) {
    //Salva a posição original do ponteiro
    int originalPlace = whereFile(fn);
    //Get o valor do status
    seekFromStartFile(fn, 0);
    char status = readStringFile(fn, 1);
    //Devolve o ponteiro para a posição original
    seekFromStartFile(fn, originalPlace);
    return status;
}

//Troca o status do header
void __toggle_status_bin(FILE_NODE *fn) {
    //Salva a posição original do ponteiro
    int originalPlace = whereFile(fn);
    //Get o valor do status
    seekFromStartFile(fn, 0);
    char status = readStringFile(fn, 1);
    //Retorna e troca o vlor do status
    seekFile(fn, -1);
    if(status == '1') {
        writeStringFile(fn, "0");
    } else {
        writeStringFile(fn, "1");
    }
    //Devolve o ponteiro para a posição original
    seekFromStartFile(fn, originalPlace);
}

//Get o RRN do próximo registro
int __get_rrn_next_register_bin(FILE_NODE *fn) {
    //Salva a posição original do ponteiro
    int originalPlace = whereFile(fn);
    //Get o RRNproxRegistro
    seekFromStartFile(fn, 1);
    int rrn = readIntFile(fn, 1);
    //Devolve o ponteiro para a posição original
    seekFromStartFile(fn, originalPlace);
    //Retorna RRNproxRegistro
    return rrn;
}

//Update o RRN do próximo registro
void __update_rrn_next_register_bin(FILE_NODE *fn) {
    //Salva a posição original do ponteiro
    int originalPlace = whereFile(fn);
    //Get o RRNproxRegistro
    seekFromStartFile(fn, 1);
    int rrn = readIntFile(fn, 1);
    //Atualiza o RRNproxRegistro
    rrn++;
    seekFile(fn, -1);
    writeIntFile(fn, rrn);
    //Devolve o ponteiro para a posição original
    seekFromStartFile(fn, originalPlace);
}

//Aumenta o contador numeroRegistrosInseridos
void __update_num_registers_bin(FILE_NODE *fn) {
    //Salva a posição original do ponteiro
    int originalPlace = whereFile(fn);
    //Get o RRNproxRegistro
    seekFromStartFile(fn, 5);
    int nri = readIntFile(fn, 1);
    //Atualiza o RRNproxRegistro
    nri++;
    seekFile(fn, -1);
    writeIntFile(fn, nri);
    //Devolve o ponteiro para a posição original
    seekFromStartFile(fn, originalPlace);
}

/*Open and close binary file*/
BIN_FILE* openBinFile(const char* filename, size_t register_size) {
    BIN_FILE* ret_file;

    ret_file = (BIN_FILE*) malloc(sizeof(BIN_FILE));

    ret_file->fp = fopen();
    ret_file->register_size = register_size;

    __write_header_bin();

    return ret_file;
}

bin_err_t closeBinFile(BIN_FILE* this_file) {
    fclose(this_file->fp);
    free(this_file);

    return OK;
}



/***********************************************
 * Funções relativas ao banco de dados
 * Essas são as funções de acesso público
 * ********************************************/
/*
//Carrega o arquivo ou cria, se não existe
FILE_NODE *loadBinFile(char *file_name) {
    FILE_NODE *fn = openFile(file_name, "w+b");
    //Verifica se arquivo existe e retorna o ponteiro do arquivo se sim.
    if(fn) {
        return fn;
    } else {
        //Caso contrário, cria o arquivo, escreve o header e retorna o arquivo aberto em w+b
        fn = openFile(file_name, "wb");
        if(fn) {
            __write_header_bin(fn);
            closeFile(fn);
            return(fn);
        } else {
            //Tratamento de erro
            printf("[!] Error tentando abrir arquivo [!]\n");
            return NULL;
        }
    }
}

//Escreve um nascimento n no arquivo marcado por fn
void writeBinFile(FILE_NODE *fn, nascimento *n) {
    //Muda o status do header para inconsistente
    __toggle_status_bin(fn);
    //Get o RRN prox registro
    int RRNproxRegistro = __get_rrn_next_register_bin(fn);
    //Escreve o nascimento n em fn na posição RRNproxRegistro
    seekFromStartFile(fn, (RRNproxRegistro*128)+128);//Navega-se + 128 para pular o header

    //Atualiza o valor do rrn
    __update_rrn_next_register_bin(fn);
    //Aumenta o contador do numero de registros inseridos
    __update_num_registers_bin(fn);
    //Devolve o status do header para consistente
    __toggle_status_bin(fn);
}
*/

