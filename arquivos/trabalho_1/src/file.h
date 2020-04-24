#ifndef _FILE
#define _FILE

typedef struct _FILE_NODE FILE_NODE;

FILE_NODE* openFile(char file_name[50], char option[3]);
int readIntFile(FILE_NODE* fn, int times);
float readFloatFile(FILE_NODE* fn, int times);
char* readStringFile(FILE_NODE* fn, int size);
void writeIntFile(FILE_NODE* fn, int data);
void writeFloatFile(FILE_NODE* fn, float data);
void writeStringFile(FILE_NODE* fn, char* data);
void seekFile(FILE_NODE* fn, int whereTo);
void seekFromStartFile(FILE_NODE* fn, int whereTo);
void goToEOF(FILE_NODE* fn);
int isEOF(FILE_NODE* fn);
int getLengthFile(FILE_NODE* fn);
int whereFile(FILE_NODE*fn);
void closeFile(FILE_NODE* fn);

#endif