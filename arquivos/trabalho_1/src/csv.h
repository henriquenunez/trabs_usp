#ifndef _CSV_READER
#define _CSV_READER

#include <stddef.h>

typedef struct _csv_file CSV_FILE;
typedef enum _csv_error csv_err_t;

CSV_FILE* openCsvFile(const char* filename);
size_t countLinesCsvFile(CSV_FILE*);
void skipHeaderCsvFile(CSV_FILE*);
int getNextInt(CSV_FILE*);
float getNextFloat(CSV_FILE*);
char* getNextString(CSV_FILE*);
void closeCsvFile(CSV_FILE*);

#endif

