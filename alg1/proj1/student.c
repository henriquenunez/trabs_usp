#include <stdio.h>
#include <stdlib.h>
#include "student.h"
#include "list.h"
#include "defines.h"

struct _student
{
	float hours;
	float T1;
	float T2;
};

struct _classroom
{
	LIST* thisClass;	
};

//int deallocEntry(void*, int);
int freeEntry(void* aStud);

CLASSROOM* newTable()
{
	CLASSROOM* new = (CLASSROOM*) malloc (sizeof(CLASSROOM));
	new->thisClass = newList();
	return new;
}

void dropTable(CLASSROOM* aClass)
{
	deAlloc(aClass->thisClass, freeEntry);
	free(aClass);
}

int createEntry(CLASSROOM* aClass, int key, float hours, float T1, float T2)
{
	STUDENT* newStud = (STUDENT*) malloc (sizeof(STUDENT));
	NODE* newEntry;

	if(newStud == NULL) return MEMORY_ERROR;
	newStud->hours = hours;
	newStud->T1 = T1;
	newStud->T2 = T2;

	setContent(newEntry = newNode(key), newStud);
	return insertAtEnd(aClass->thisClass, newEntry);
}

int printEntryValue(void* ptr)
{
	STUDENT* content = ptr;
	printf("\tHours: %f, Test1: %f, Test2: %f\n", 
		content->hours, content->T1, content->T2);
	return SUCCESS;
}

int printApproved(void* ptr)
{
	STUDENT* content = ptr;
	if((content->T1 + content->T2)/2 >= 5)
	{
		printf("DELBEMM\n");
	}
	else
	{
		printf("DELRUIMM\n");	
	}
	return SUCCESS;
}

void* getHours(void* ptr)
{
	STUDENT* content = ptr;
	float* study_hours = (float*) malloc (sizeof(float));
	(*study_hours) = content->hours;
	return study_hours;
}

void printTable(CLASSROOM* aClass)
{
	iterList(aClass->thisClass, printEntryValue);
}

void printApprovedTable(CLASSROOM* aClass)
{
	iterList(aClass->thisClass, printApproved);
}

float acquireAverage(CLASSROOM* aClass)
{
	void* ptr;
	float mean;
	ptr = iterListGetVals(aClass->thisClass, getHours);
	mean = *((float*)ptr);
	free(ptr);
	return mean;
}

int freeEntry(void* aStud)
{
	free((STUDENT*)aStud);
	return SUCCESS;
}

int deleteEntry(void* aClass, int key)
{
	removeContent(((CLASSROOM*)aClass)->thisClass, key, &freeEntry);
	return SUCCESS;
}