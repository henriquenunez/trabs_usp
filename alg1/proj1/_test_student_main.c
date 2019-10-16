#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int main()
{
	CLASSROOM* bcc;
	bcc = newTable();

	createEntry(bcc, 10, 2,  1,  2);
	createEntry(bcc, 11, 4,  1,  2);
	createEntry(bcc, 12, 8,  1,  2);
	createEntry(bcc, 13, 16, 10,  2);
	createEntry(bcc, 14, 32, 10, 10);
	
	printTable(bcc);

	deleteEntry(bcc, 10);

	printf("\n");

	printTable(bcc);

	printf("\n");

	printApprovedTable(bcc);

	printf("AVG: %f\n", acquireAverage(bcc));

	dropTable(bcc);

	return 0;
}