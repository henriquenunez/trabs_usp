#ifndef NEWBORNS_H
#define NEWBORNS_H

typedef struct _newborns NEWBORNS;
typedef enum _nb_error nb_err_t;

enum _nb_error {
	NB_OK
};

/*Instanciation functions*/
NEWBORNS* NBCreateInstance(const char* gen_filename);
void  NBDeleteInstance(NEWBORNS*);

/*Importing data into binary file*/
nb_err_t NBImportCSV(NEWBORNS*, const char* csv_filename );
nb_err_t NBPrintAllNewborns();

#endif

