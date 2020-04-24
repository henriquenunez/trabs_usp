#include "bin.h"

/*****************************************************************
 * Funções relativos ao tipo de dado que será armazenado
 * O tipo de dado é nascimento e está guardado numa struct
 * Esse tipo é público e será usado para facilitar a administração 
 * dos dados a serem guardados no arquivo
 * ***************************************************************/

struct _nascimento{
    int id;
    int idadeMae;
    char data[10];
    char sexo;
    char estadoMae[2];
    char estadoBebe[2];
    char* cidadeMae;
    char* cidadeBebe;
};

//Cria um objeto do tipo nascimento.
nascimento* createNascimento(int id, int idadeMae, char data[10], char sexo, char estadoMae[2], char estadoBebe[2], char* cidadeMae, char* cidadeBebe){
    nascimento *n = (nascimento*) malloc(sizeof(nascimento));
    n->id = id;
    n->idadeMae = idadeMae;
    strcpy(n->data, data);
    n->sexo = sexo;
    strcpy(n->estadoMae, estadoMae);
    strcpy(n->estadoBebe, estadoBebe);
    strcpy(n->cidadeMae, cidadeMae);
    strcpy(n->cidadeBebe, cidadeBebe);
    return n;
}

/**********************************************************************
 * Funções relativas ao header.
 * Como o header é uma 'ferramenta administrativa' do banco, estas funções
 * são de domínio privado para que as atualizações dos dados não sejam
 * feitas de maneira inadequada.
 * ********************************************************************/

//Cria o header inicial quando não existe arquivo
void writeHeader(FILE_NODE *fn){
    //Status
    writeStringFile(fn, "1");
    //RRNproxRegistro
    writeIntFile(fn, 0);
    //numeroRegistrosInseridos
    writeIntFile(fn, 0);
    //numeroRegistrosRemovidos
    writeIntFile(fn, 0);
    //numeroRegistrosAtualizados
    writeIntFile(fn, 0);
    //111 bytes de lixo '$'
    for(int i = 0 ; i < 111 ; i++){
        writeStringFile(fn, "$");
    }
}

//Get o status do header
char getStatus(FILE_NODE *fn){
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
void toggleStatus(FILE_NODE *fn){
    //Salva a posição original do ponteiro
    int originalPlace = whereFile(fn);
    //Get o valor do status
    seekFromStartFile(fn, 0);
    char status = readStringFile(fn, 1);
    //Retorna e troca o vlor do status
    seekFile(fn, -1);
    if(status == '1'){
        writeStringFile(fn, "0");
    }else{
        writeStringFile(fn, "1");
    }
    //Devolve o ponteiro para a posição original
    seekFromStartFile(fn, originalPlace);
}

//Get o RRN do próximo registro
int getRRNproxRegistro(FILE_NODE *fn){
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
void updateRRNproxRegistro(FILE_NODE *fn){
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
void updateNumeroRegistrosInseridos(FILE_NODE *fn){
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

/***********************************************
 * Funções relativas ao banco de dados
 * Essas são as funções de acesso público
 * ********************************************/

//Carrega o arquivo ou cria, se não existe
FILE_NODE *loadBinFile(char *file_name){
    FILE_NODE *fn = openFile(file_name, "w+b");
    //Verifica se arquivo existe e retorna o ponteiro do arquivo se sim.
    if(fn){
        return fn;
    }else{
        //Caso contrário, cria o arquivo, escreve o header e retorna o arquivo aberto em w+b
        fn = openFile(file_name, "wb");
        if(fn){
            writeHeader(fn);
            closeFile(fn);
            return(fn);
        }else{
            //Tratamento de erro
            printf("[!] Error tentando abrir arquivo [!]\n");
            return NULL;
        }
    }
}

//Escreve um nascimento n no arquivo marcado por fn
void writeBinFile(FILE_NODE *fn, nascimento *n){
    //Muda o status do header para inconsistente
    toggleStatus(fn);
    //Get o RRN prox registro
    int RRNproxRegistro = getRRNproxRegistro(fn);
    //Escreve o nascimento n em fn na posição RRNproxRegistro
    seekFromStartFile(fn, (RRNproxRegistro*128)+128);//Navega-se + 128 para pular o header
    writeIntFile(fn, strlen(n->cidadeMae));
    writeIntFile(fn, strlen(n->cidadeBebe));
    writeStringFile(fn, n->cidadeMae);
    writeStringFile(fn, n->cidadeBebe);
    //Coloca lixo depois dos campos de tamanho variável
    for(int i = 0 ; i < 97-(strlen(n->cidadeMae) + strlen(n->cidadeBebe)) ; i++){
        writeStringFile(fn, "$");
    }
    writeIntFile(fn, n->id);
    writeIntFile(fn, n->idadeMae);
    writeStringFile(fn, n->estadoMae);
    writeStringFile(fn, n->estadoBebe);
    //Atualiza o valor do rrn
    updateRRNproxRegistro(fn);
    //Aumenta o contador do numero de registros inseridos
    updateNumeroRegistrosInseridos(fn);
    //Devolve o status do header para consistente
    toggleStatus(fn);
}