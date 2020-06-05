#ifndef NEWBORNS_H
#define NEWBORNS_H

#include "data_structures.h"

typedef struct _newborns NEWBORNS;
typedef enum _nb_error nb_err_t;

enum _nb_error {
	NB_OK,
	NOT_FOUND,
	FILTER_ERROR
};

/*Instanciation functions*/
NEWBORNS* NBCreateInstance(const char* gen_filename);
void  NBDeleteInstance(NEWBORNS*);

/*Importing data into binary file*/
nb_err_t NBImportCSV(NEWBORNS*, const char* csv_filename );
nb_err_t NBPrintAllNewborns(NEWBORNS*);

/*Insert new register*/
nb_err_t NBInsertNewbornAtEnd(NEWBORNS*, STRING_PAIR_VECTOR);

/*Searching*/
nb_err_t NBSearchMatchingFields(NEWBORNS*, STRING_PAIR_VECTOR);

nb_err_t NBSearchByRegisterNumber(NEWBORNS*, int reg_number);

/*Updating*/
/*nb_err_t NBUpdateNextMatchingFields(NEWBORNS*,
				    char *curr_fields[],
				    char *new_fields[]); //NOT NEEDED ;) */

nb_err_t NBUpdateByRegisterNumber(NEWBORNS*,
				    int reg_number,
				    STRING_PAIR_VECTOR);

/*Removing*/
nb_err_t NBRemoveMatchingFields(NEWBORNS*, STRING_PAIR_VECTOR);

//nb_err_t NBRemoveByRegisterNumber(NEWBORNS*, int reg_number); NOT NEEDED

#endif

