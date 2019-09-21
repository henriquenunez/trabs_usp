#ifndef _LIST_H
#define _LIST_H

typedef struct _node NODE;
typedef struct _list LIST;

int deAlloc(LIST*, int (*clearfunc)(void*));
//int deAlloc(LIST*);

NODE* searchByKey(LIST*, int);
int removeByKey(LIST*, int);
int removeContent(LIST* aList, int key, int (*removeFunc)(void*));
int insertAtEnd(LIST*, NODE*);
int insertAtNode(LIST*, NODE*, NODE*);
int insertFirst(LIST*, NODE*);

NODE* newNode(int);
LIST* newList();

void printList(LIST*);

int setContent(NODE*, void*);
void doSomething(LIST*, int, void (*customFunc)(void*));
void iterList(LIST*, int (*customFunc)(void*)); //takes callbacks
void iterListDeAlloc(LIST*, int (*customFunc)(void*, int)); //takes callbacks
void* iterListGetVals(LIST* aList, void* (*customFunc)(void*));
//void* pointerToContents(NODE*);

#endif