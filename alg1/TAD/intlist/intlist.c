#include <stdio.h>
#include <stdlib.h>
#include "intlist.h"

struct _list
{
    int len;
    int* content;
    int compNum;
};

int retLen(integerList8 list)
{
    return list->len;
}
int compNum(integerList8 list)
{
    return list->compNum;
}

int dat_num(integerList8 list, int pos)
{
    return list->content[pos];
}

void insElement(integerList* list, int d)
{
    list->content = (int*) realloc (list->content, (list->len + 1) * sizeof(int));
    list->content[list->len] = d;
    list->len++;
}

int whetherInList(integerList* list, int num)
{
    if (list->content == NULL) return 0;
    for (int i = 0; i < list->len; i++)
    {
        list->compNum++;
        if(num == list->content[i])
        {
            return 1;
        }
    }
    return 0;
}

void printList(integerList* list)
{
    for (int i = 0; i < list->len; i++)
    {
        fprintf(stderr, "%d\t", list->content[i]);
        fprintf(stdout, "%d\t", list->content[i]);
    }
    fprintf(stderr, "\n");
    fprintf(stdout, "\n");
}

integerList8 newList()
{
    integerList* a_list = (integerList8) malloc(sizeof(integerList));
    a_list->compNum = 0;
    a_list->content = NULL;
    a_list->len;

    return a_list;
}