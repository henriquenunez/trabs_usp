#include "circlelist.h"
#include <stdlib.h>
#include <stdio.h>

struct _NODE
{
    int key;
    int value;
    NODE* next;
};

struct _LIST
{
    NODE* senti;
    NODE* end;
    int size;
};

typedef struct previous_n_current 
{
    NODE* previous;
    NODE* current;
} NODE_PAIR;

NODE* newNode(int key, int value);

NODE_PAIR searchNodePair(int key, LIST* this_list)
{
    NODE* pNODE;
    NODE* cNODE;

    NODE_PAIR nodePair;
    
    pNODE = this_list->senti;
    pNODE->key = key; //attributes key to sentinel
    cNODE = pNODE->next;

    while(cNODE->key != key)
    {
        pNODE = cNODE;
        cNODE = cNODE->next;
    }

    nodePair.previous = pNODE;
    nodePair.current = cNODE;

    return nodePair;
}

LIST* newList()
{
    LIST* aList;
    aList = (LIST*) calloc (1, sizeof(LIST));

    aList->senti = 0x00000000;

    return aList;
}

NODE* newNode(int key, int value)
{
    NODE* aNode = (NODE*) malloc (sizeof(NODE));
 
    aNode->key = key;
    aNode->value = value;

    return aNode;
}

void deleteNode(NODE* prev_node, NODE* this_node)
{
    prev_node->next = this_node->next;
    free(this_node);
}

void deleteByKey(int key, LIST* this_list)
{
    NODE_PAIR aPair = searchNodePair(key, this_list);
    deleteNode(aPair.previous, aPair.current);
}

int searchValByKey(int key, LIST* this_list)
{
    return searchNodePair(key, this_list).current->value;
}

void insertInList(int key, int value, LIST* this_list)
{
    NODE* temp;
    NODE* aNODE = this_list->senti;
    while(1)
    {
        if((aNODE->next->value >= value) || aNODE->next == this_list->senti)
        {
            temp = newNode(key, value);
            temp->next = aNODE->next;
            aNODE->next = aNODE;
            return;
        }
        aNODE = aNODE->next;
    }
}

void printList(LIST* this_list)
{
    NODE* aNode;
    while(aNode != this_list->senti)
    {
        printf("value: %d key: %d\n", aNode->value, aNode->key);
        aNode = aNode->next;
    }
}
