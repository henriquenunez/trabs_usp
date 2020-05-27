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
nb_err_t NBPrintAllNewborns(NEWBORNS*);

/*Searching*/
nb_err_t NBSearchMatchingFields(NEWBORNS*, char *args[]);

nb_err_t NBSearchByRegisterNumber(NEWBORNS*, int reg_number);

/*Updating*/
nb_err_t NBUpdateNextMatchingFields(NEWBORNS*,
				    char *curr_fields[],
				    char *new_fields[]);

nb_err_t NBUpdateByRegisterNumber(NEWBORNS*, int reg_number);

/*Removing*/
nb_err_t NBRemoveMatchingFields(NEWBORNS*, char *args[]);

nb_err_t NBRemoveByRegisterNumber(NEWBORNS*, int reg_number);

#endif

