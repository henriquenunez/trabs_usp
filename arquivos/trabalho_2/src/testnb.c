#include <stdio.h>
#include "newborns.h"

#include <stdlib.h>

#define CRIT_NUM 2

int main() {
	STRING_PAIR_VECTOR criteria;

	criteria.data = (STRING_PAIR*) malloc(CRIT_NUM * sizeof(STRING_PAIR));
	criteria.size = CRIT_NUM;

//cidadeMae,cidadeBebe,idNascimento,idadeMae,dataNascimento,sexoBebe,estadoMae,estadoBebe
	char CIDADEMAE_I[] = "cidadeMae";
	char CIDADEBEBE_I[] = "cidadeBebe";
	char IDNASCIMENTO_I[] = "idNascimento";
	char IDADEMAE_I[] = "idadeMae";
	char DATANASCIMENTO_I[] = "dataNascimento";
	char SEXOBEBE_I[] = "sexoBebe";
	char ESTADOMAE_I[] = "estadoMae";
	char ESTADOBEBE_I[] = "estadoBebe";

    NEWBORNS* bb;

    bb = NBCreateInstance("test_nb_file.bin");
    //Importing minified CSV
    NBImportCSV(bb, "little.csv");

    STRING_PAIR criterion_0;
    STRING_PAIR criterion_1;

/*SEARCHING BY MATCHING FIELDS*/

/*FIRST QUERY*/
    //Making filters.
    printf("\tFIRST QUERY!\n");

    //Criterion 0
   	criterion_0.key = DATANASCIMENTO_I;
   	criterion_0.value = "2016-01-11";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = CIDADEBEBE_I;
   	criterion_1.value = "NOVA FRIBURGO";
   	criteria.data[1] = criterion_1;

    //Search using filter
    NBSearchMatchingFields(bb, criteria);

/*SECOND QUERY*/
    //Making filters.
    printf("\tSECOND QUERY!\n");

    //Criterion 0
   	criterion_0.key = IDNASCIMENTO_I;
   	criterion_0.value = "2";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = ESTADOBEBE_I;
   	criterion_1.value = "GO";
   	criteria.data[1] = criterion_1;

    //Search using filter
    NBSearchMatchingFields(bb, criteria);

/*THIRD QUERY*/
    //Making filters.
    printf("\tTHIRD QUERY!\n");

    //Criterion 0
   	criterion_0.key = IDNASCIMENTO_I;
   	criterion_0.value = "4";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = SEXOBEBE_I;
   	criterion_1.value = "1";
   	criteria.data[1] = criterion_1;

    //Search using filter
    NBSearchMatchingFields(bb, criteria);

/*FOURTH QUERY*/
    //Making filters.
    printf("\tFOURTH QUERY!\n");

    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "2";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = IDADEMAE_I;
   	criterion_1.value = "24";
   	criteria.data[1] = criterion_1;

    //Search using filter
    NBSearchMatchingFields(bb, criteria);




    NBDeleteInstance(bb);
    free(criteria.data);

    return 0;
}
