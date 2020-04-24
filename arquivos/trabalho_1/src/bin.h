#ifndef SUS_BIN
#define SUS_BIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

typedef struct _nascimento nascimento;

FILE_NODE *loadBinFile(char *file_name);
nascimento* createNascimento(int id, int idadeMae, char data[10], char sexo, char estadoMae[2], char estadoBebe[2], char* cidadeMae, char* cidadeBebe);

#endif