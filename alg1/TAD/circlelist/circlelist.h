#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

typedef struct _LIST LIST;
typedef struct _NODE NODE;

LIST* newList();
void insertInList (int key, int value, LIST* this_list);
int searchByKey (int key, LIST* this_list);
void deleteByKey (int key, LIST* this_list);
void deleteList(LIST* this_list);

void printList(LIST* this_list);

#endif
