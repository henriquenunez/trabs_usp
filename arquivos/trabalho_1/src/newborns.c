#include "newborns.h"
#include "csv.h"
#include "bin.h"

#include <stdlib.h>
#include <string.h>

FILE_NODE *loadBinFile(char *file_name);

typedef struct _nascimento nascimento;

struct _newborns {
    BIN* binary_file;
};

NEWBORNS* NBCreateInstance(const char* gen_filename) {
    NEWBORNS* ret_instance;
    ret_instance = (NEWBORNS*) malloc(sizeof(NEWBORNS));

    ret_instance->binary_file = openBinFile();

    //Instanciation error-checking
    if (ret_instance->binary_file == NULL) {
	//dealloc stuff
	//closeBinFile();
	free(ret_instance);
	return NULL;
    }


    return ret_instance;
}


/*////////////////////////////////////////////////////////////////////////////

NOT MY CODE BEYOND THIS POINT

*/


/*****************************************************************
 * Funções relativos ao tipo de dado que será armazenado
 * O tipo de dado é nascimento e está guardado numa struct
 * Esse tipo é público e será usado para facilitar a administração 
 * dos dados a serem guardados no arquivo
 * ***************************************************************/

nascimento* createNascimento(	int id,
				int idadeMae,
				char data[10],
				char sexo,
				char estadoMae[2],
				char estadoBebe[2],
				char* cidadeMae,
				char* cidadeBebe);


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

NBInsertBaby() {
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
}

