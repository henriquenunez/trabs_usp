#include <stdio.h>
#include "csv.h"

#define STRING_FIELDS 5000
#define	   INT_FIELDS 100

int main (){
    CSV_FILE* file;
    int i;

    file = openCsvFile("arquivoEntrada.csv");
    skipHeaderCsvFile(file);

    i = STRING_FIELDS;
    while (i--)
	printf("FIELD(STR) %4d: {%s}\n", STRING_FIELDS - i, getNextString(file));

    closeCsvFile(file);

    file = openCsvFile("arquivoEntrada.csv");
    i = INT_FIELDS;
    while (i--)
	printf("FIELD(INT) %4d: %d\n", INT_FIELDS - i, getNextInt(file));

    printf("Nlines: %d\n", countLinesCsvFile(file));

    closeCsvFile(file);

    return 0;
}
