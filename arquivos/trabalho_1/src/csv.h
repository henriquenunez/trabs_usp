#ifndef _CSV_READER
#define _CSV_READER

typedef struct _csv_file CSV_FILE;

CSV_FILE* openCsvFile();
int getNextInt(CSV_FILE*);
float getNextFloat(CSV_FILE*);
char* getNextString(CSV_FILE*);
void closeCsvFile(CSV_FILE);

#endif

