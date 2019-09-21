#include <stdlib.h>
#include <stdio.h>
#include "student.h"

int main()
{
	CLASSROOM* bcc;
	bcc = newTable();

	createEntry(bcc, 10, 2,  1,  2);
	createEntry(bcc, 11, 2,  1,  2);
	createEntry(bcc, 12, 6666666,  1,  2);
	createEntry(bcc, 13, 3, 10,  2);
	createEntry(bcc, 14, 3, 10, 10);
	
	printTable(bcc);

	deleteEntry(bcc, 12);

	printf("\n");

	printTable(bcc);

	printf("\n");

	printApprovedTable(bcc);

	printf("AVG: %f\n", acquireAverage(bcc));

	dropTable(bcc);

	return 0;
}