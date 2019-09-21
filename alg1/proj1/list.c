#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "defines.h"

struct _node
{
	void* content;
	int key;
	NODE* next;
	NODE* prev;
};

struct _list
{
	int size;
	NODE* first;
	NODE* last;
};

int deAlloc(LIST* aList, int (*clearfunc)(void*))
{
	NODE* temp = aList->first;
	do
	{
		clearfunc(temp->content);
		temp = temp->next;
		free(temp->prev);
	}while(temp!=aList->first);
	free(aList);
	return SUCCESS;
}
/*
int deAlloc(LIST* aList)
{
	NODE* temp = aList->first;
	do
	{
		//pointer to func clearcont(temp->cont)
		temp = temp->next;
		free(temp->prev);
	}while(temp!=aList->first);
	free(aList);
	return SUCCESS;
}
*/
NODE* searchByKey(LIST* aList, int key)
{
	NODE* temp = aList->first;
	do
	{
		if(temp->key == key)
		{
			return temp;
		}
		temp = temp->next;
	}while(temp!=aList->first);

	return NULL;
}

int removeByKey(LIST* aList, int key)
{
	NODE* temp = searchByKey(aList, key);
	if (temp == NULL) return ERROR;
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->prev = NULL;
	temp->next = NULL;
	//weird func temp->cont
	free(temp);
	aList->size = aList->size - 1;
	return SUCCESS;
}

int removeContent(LIST* aList, int key, int (*removeFunc)(void*))
{
	NODE* temp = searchByKey(aList, key);
	if (temp == NULL) return ERROR;
	
	removeFunc(temp->content);
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	temp->prev = NULL;
	temp->next = NULL;
	
	aList->size = aList->size - 1;
	free(temp);	
	return SUCCESS;
}

void* pointerToContents(NODE* aNode)
{
	return aNode->content;
}

int insertFirst(LIST* aList, NODE* new)
{
	//NODE* new = newNode(key);
	
	if(new == NULL) return ERROR;

	aList->first = new;
	aList->last = new;
	new->next = new;
	new->prev = new;

	return SUCCESS;
}

int insertAtNode(LIST* aList, NODE* prev, NODE* new)
{
	if(new == NULL || aList == NULL)
	{
		return NULL_POINTER_EXCEPTION;
	}

	if(prev == NULL)
	{
		//printf("prev is null\n");
		insertFirst(aList, new);
		//printf(" new->next %p\n", new->next);
		//printf(" new->prev %p\n\n\n", new->prev);
		return SUCCESS;
	}
//TODO treat "last" case

/*
	printf("prev->next %p\n", prev->next);
	printf("prev->prev %p\n\n", prev->prev);
*/
	new->next = prev->next;
	new->prev = prev;

	new->next->prev = new;
	new->prev->next = new;
/*
	printf("prev->next %p\n", prev->next);
	printf("prev->prev %p\n", prev->prev);
	printf(" new->next %p\n", new->next);
	printf(" new->prev %p\n\n\n", new->prev);
*/
	if (new->next == aList->first)
	{
		aList->last = new;
	}
	aList->size = aList->size + 1;
	return SUCCESS;
}

int insertAtEnd(LIST* aList, NODE* new)
{
	int retCode;
	retCode = insertAtNode(aList, aList->last, new);
	aList->last = new;
	aList->size = aList->size + 1;
	return retCode;
}

NODE* newNode(int key)
{
	NODE* new = (NODE*) malloc (sizeof(NODE));
	new->key = key;
	return new;
}

LIST* newList()
{
	LIST* new = (LIST*) malloc (sizeof(LIST));
	new->first = NULL;
	new->last = NULL;
	new->size = 0;
	return new;
}

int setContent(NODE* aNode, void* content)
{
	aNode->content = content;
	if (aNode->content == NULL) return ERROR;
	return SUCCESS;
}

void printList(LIST* aList)
{
	NODE* temp = aList->first;
	if(temp == NULL)
	{
		printf("error\n");
		return;
	}
	do
	{
		printf("element key: %d\n", temp->key);
		temp = temp->next;
	}while(temp != aList->first);
	printf("\n");
}

void iterList(LIST* aList, int (*customFunc)(void*))
{
	NODE* temp = aList->first;
	if(temp == NULL)
	{
		printf("error:no items\n");
		return;
	}
	do
	{
		printf("calling da thing\n");
		printf("ID: %d ", temp->key);
		(*customFunc)(temp->content);
		temp = temp->next;
	}while(temp != aList->first);
}
/*
void iterListDeAlloc(LIST* aList, int (*customFunc)(void*, int))
{
	NODE* temp = aList->first;
	if(temp == NULL)
	{
		printf("error:no items\n");
		return;
	}
	do
	{
		printf("calling da thing\n");
		printf("ID: %d ", temp->key);
		(*customFunc)(temp->content, temp->key);
		temp = temp->next;
	}while(temp != aList->first);
}
*/
void* iterListGetVals(LIST* aList, void* (*customFunc)(void*))
{
	float* accumulator = (float*) malloc (sizeof(float));
	(*accumulator) = 0;
	void* ptr;

	NODE* temp = aList->first;
	if(temp == NULL)
	{
		printf("error:no items\n");
		return NULL;
	}
	do
	{
		printf("calling da thing\n");
		
		ptr = (*customFunc)(temp->content);
		(*accumulator) += *((float*)(ptr));
		free(ptr);
		printf("valbynow: %f ", *accumulator);
		
		temp = temp->next;
	}while(temp != aList->first);

	(*accumulator) /= aList->size;

	return accumulator;
}