#ifndef NEWBORNS_H
#define NEWBORNS_H

typedef struct __newborns NEWBORNS;
typedef enum __nb_error nb_err_t;

/*Instanciation functions*/
NEWBORNS* NBCreateInstance(const char* gen_filename);
void  NBDeleteInstance(NEWBORNS*);

/*Importing data into binary file*/
nb_err_t NBImportCSV(NEWBORNS* instance, const char* csv_filename );

#endif

