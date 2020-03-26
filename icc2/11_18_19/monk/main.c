#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define HASH_SIZE 1000

void remove_trailing(char* string)
{
	int i = 0;
	while (string[i] != 0)
	{
		if (string[i] == '\n' || string[i] == '\r')
			string[i] = 0;
		i++;
	}
}

int main()
{
	int ops;
	H_TABLE *a_table;

	int place;
	char buffer[30];
	char* temp;

	a_table = table_create(HASH_SIZE, &free);
	scanf("%d", &ops);
	while(ops--)
	{
		scanf("%d %s", &place, buffer);
		temp = (char*) malloc (strlen(buffer) * sizeof(char));
		strcpy(temp, buffer);
		table_insert(a_table, place, temp);
	}
	scanf("%d", &ops);
	while(ops--)
	{
		//printf("ne\n");
		scanf("%d", &place);
		temp = table_retrieve(a_table, place);
		if (temp != NULL)
			printf("%s\n", temp);
	}

	fflush(stdout);

	table_purge(a_table);
	return 0;
}
