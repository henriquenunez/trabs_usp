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

int freeEntry(void* aStud);

/*Allocates a table containing a list*/
CLASSROOM* newTable()
{
	CLASSROOM* new = (CLASSROOM*) malloc (sizeof(CLASSROOM));
	new->thisClass = newList();
	return new;
}

/*Calls deallocation function with freeEntry as parameter*/
void dropTable(CLASSROOM* aClass)
{
	deAlloc(aClass->thisClass, freeEntry);
	free(aClass);
}

/*Receives student information, sets parameters 
  and sets list node content as this
  newly allocated type*/
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

/*Casts received pointer to STUDENT type, and gets its content*/
int printEntryValue(void* ptr)
{
	STUDENT* content = ptr;
	printf("\tHours: %.2f, Test1: %.2f, Test2: %.2f\n", 
		content->hours, content->T1, content->T2);
	return SUCCESS;
}

/*Same as above, but checks if the mean of grades was GEQ than 5*/
int printApproved(void* ptr)
{
	STUDENT* content = ptr;
	if((content->T1 + content->T2)/2 >= 5)
	{
		printf("Approved\n");
	}
	else
	{
		printf("Failed\n");	
	}
	return SUCCESS;
}

/*Returns pointer to float representing the number
  of study hours*/
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

/*Returns average of class by the result
  of iterListGetVals, passing getHours as parameter*/
float acquireAverage(CLASSROOM* aClass)
{
	void* ptr;
	float mean;
	ptr = iterListGetVals(aClass->thisClass, getHours);
	mean = *((float*)ptr);
	free(ptr);
	return mean;
}

/*Deallocates memory for this data type*/
int freeEntry(void* aStud)
{
	free((STUDENT*)aStud);
	return SUCCESS;
}

/*Calls List ADT function with 
  the above function as parameter*/
int deleteEntry(void* aClass, int key)
{
	removeContent(((CLASSROOM*)aClass)->thisClass, key, &freeEntry);
	return SUCCESS;
}