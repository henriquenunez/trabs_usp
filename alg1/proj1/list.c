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

/*Runs through list deallocating the node and their contents with
  its ADT specific function*/
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

/*Runs through list checking whether the key is the
  same or not*/
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

int removeContent(LIST* aList, int key, int (*removeFunc)(void*))
{
	NODE* temp = searchByKey(aList, key);
	if (temp == NULL) return ERROR;
	
	removeFunc(temp->content);
	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;
	
	aList->size = aList->size - 1;
	if (temp == aList->first)
	{
		aList->first = temp->next;
	}
	if (temp == aList->last)
	{
		aList->last = temp->prev;
	}
	
	temp->prev = NULL;
	temp->next = NULL;
	
	free(temp);	
	return SUCCESS;
}

int insertFirst(LIST* aList, NODE* new)
{
	if(new == NULL) return ERROR;

	aList->first = new;
	aList->last = new;
	new->next = new;
	new->prev = new;
	aList->size = aList->size + 1;
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
		insertFirst(aList, new);
		return SUCCESS;
	}

	new->next = prev->next;
	new->prev = prev;

	new->next->prev = new;
	new->prev->next = new;

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

/*iters through list, calling customFunc at every node*/
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
		printf("ID: %d ", temp->key);
		(*customFunc)(temp->content);
		temp = temp->next;
	}while(temp != aList->first);
}

/*iters through list, using customFunc return value
  to calculate the mean of all nodes content values*/
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
		ptr = (*customFunc)(temp->content);
		(*accumulator) += *((float*)(ptr));
		free(ptr);
		temp = temp->next;
	}while(temp != aList->first);

	(*accumulator) /= aList->size;

	return accumulator;
}