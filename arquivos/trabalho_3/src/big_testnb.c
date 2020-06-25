#include <stdio.h>
#include "newborns.h"

#include <stdlib.h>

#include <string.h>
#define CRIT_NUM 2

int main() {

//	printf("OWO %d\n", strlen(""));

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
    printf("Testing Data Import\n");

    NBImportCSV(bb, "arquivoEntrada.csv");
    STRING_PAIR criterion_0;
    STRING_PAIR criterion_1;

#define TEST_NB_MATCHING_FIELDS
#ifdef TEST_NB_MATCHING_FIELDS

//SEARCHING BY MATCHING FIELDS

//FIRST QUERY
    //Making filters.

    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = ESTADOBEBE_I;
   	criterion_1.value = "RS";
   	criteria.data[1] = criterion_1;

    //Search using filter
    printf("\tFIRST QUERY!\n");
    NBSearchMatchingFields(bb, criteria);
/*
//SECOND QUERY
    //Making filters.

    //Criterion 0
   	criterion_0.key = IDNASCIMENTO_I;
   	criterion_0.value = "2";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = ESTADOBEBE_I;
   	criterion_1.value = "GO";
   	criteria.data[1] = criterion_1;

    //Search using filter
    printf("\tSECOND QUERY!\n");
    NBSearchMatchingFields(bb, criteria);

//THIRD QUERY
    //Making filters.

    //Criterion 0
   	criterion_0.key = IDNASCIMENTO_I;
   	criterion_0.value = "4";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = SEXOBEBE_I;
   	criterion_1.value = "1";
   	criteria.data[1] = criterion_1;

    //Search using filter
    printf("\tTHIRD QUERY!\n");
    NBSearchMatchingFields(bb, criteria);

//FOURTH QUERY
    //Making filters.

    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "2";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = IDADEMAE_I;
   	criterion_1.value = "24";
   	criteria.data[1] = criterion_1;

    //Search using filter
    printf("\tFOURTH QUERY!\n");
    NBSearchMatchingFields(bb, criteria);

//FIFTH QUERY
    //Making filters.

    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "";
   	criteria.data[0] = criterion_0;
*/
/*
    //Criterion 1
   	criterion_1.key = IDADEMAE_I;
   	criterion_1.value = "";
   	criteria.data[1] = criterion_1;

    criteria.size = 1;
    //Search using filter
    printf("\tFIFTH HARMONY!\n");
    if(NBSearchMatchingFields(bb, criteria) != NB_OK)
	printf("registro inexistente.\n");
*/
#endif
#ifdef TEST_NB_GET_RRN

//Testing register number
    printf("SEARCH BY RRN\n");
    printf("RRN = 0: ");
    NBSearchByRegisterNumber(bb, 0);
    printf("RRN = 3: ");
    NBSearchByRegisterNumber(bb, 3);
    printf("RRN = 5: ");
    NBSearchByRegisterNumber(bb, 5);

    if(NBSearchByRegisterNumber(bb, 100) != NB_OK)
	printf("registro inexistente.\n");
#endif
#ifdef TEST_NB_REMOVE_MATCHING_FIELDS

//Time to remove registers.
    printf("REMOVING BY MATCHING FIELDS\n");

    printf("Before.\n");
    NBPrintAllNewborns(bb);

    //CRITERIA FOR REMOVAL!!!
    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "2";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = IDADEMAE_I;
   	criterion_1.value = "24";
   	criteria.data[1] = criterion_1;

    NBRemoveMatchingFields(bb, criteria);
    printf("After.\n");
    NBPrintAllNewborns(bb);
#endif
//#define TEST_NB_UPDATE_REGISTER
#ifdef TEST_NB_UPDATE_REGISTER

    printf("UPDATING REGISTER\n");

    printf("Before.\n");
    NBPrintAllNewborns(bb);

    //FIELDS TO BE UPDATED
    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "4";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = IDADEMAE_I;
   	criterion_1.value = "99";
   	criteria.data[1] = criterion_1;

    NBUpdateByRegisterNumber(bb, 23, criteria);
    printf("After.\n");
    NBPrintAllNewborns(bb);




#endif
//#define TEST_NB_APPEND_REGISTER
#ifdef TEST_NB_APPEND_REGISTER

    printf("APPENDING REGISTER\n");

    printf("Before.\n");
    NBPrintAllNewborns(bb);

    //FIELDS TO BE UPDATED
    //Criterion 0
   	criterion_0.key = SEXOBEBE_I;
   	criterion_0.value = "4";
   	criteria.data[0] = criterion_0;

    //Criterion 1
   	criterion_1.key = IDADEMAE_I;
   	criterion_1.value = "99";
   	criteria.data[1] = criterion_1;

    NBInsertNewbornAtEnd(bb, criteria);
    printf("After.\n");
    NBPrintAllNewborns(bb);


#endif

    NBDeleteInstance(bb);
    free(criteria.data);

    return 0;
}
