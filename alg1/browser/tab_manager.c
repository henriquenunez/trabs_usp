#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "tab_manager.h"

#define OK 0
#define _OK 1

typedef struct _node NODE;

/*
Data structure used: Circular, double linked list with sentinel
Reasons why:
    -Insertions must be made before and after nodes, and double
        linked lists make this task easier.
    -Searches within the list must be made. The sentinel node
        simplifies this.
    -Circular lists generalize the insertion operation, since
        there won't be nodes which pointers to previous or next
        are NULL.
*/

struct _node
{
    char name[40];
    char url[512];
    NODE* prev;
    NODE* next;
};

struct _browser
{
    NODE* vigilis;
    int tab_num;
};

NODE* new_node();
int insert_node(NODE*, NODE*);
int insert_node_before(NODE*, NODE*);
int remove_node(NODE*);
int free_node(NODE*);

NODE* search_tab(NODE*, char*);

BROWSER* new_browser()
{
    BROWSER* new = (BROWSER*) malloc(sizeof(BROWSER));
    new->vigilis = new_node();
    new->vigilis->next = new->vigilis;
    new->vigilis->prev = new->vigilis;
    new->tab_num = 0;

    return new;
}

void free_browser(BROWSER* this_browser)
{
    NODE *aux, *temp = this_browser->vigilis->next;
    while(temp != this_browser->vigilis)
    {
        aux = temp;
        temp = temp->next;
        free(aux);
    }
}

int add_tab(BROWSER* this_browser, char* name, char* url)
{
    NODE* new = new_node();
    memcpy(new->name, name, 40);
    memcpy( new->url,  url, 512);
   
    insert_node(this_browser->vigilis->prev, new);
    this_browser->tab_num++;
 
    return OK;
}

int move_tab(BROWSER* this_browser, char* name, int position)
{
    NODE* moved, *temp;
    moved = search_tab(this_browser->vigilis, name);
    int aux_tab_num = this_browser->tab_num;
    if (moved == NULL || position < 1) return _OK;
    remove_node(moved);
    temp = this_browser->vigilis->next;
    while(--position && --aux_tab_num)
    {
        temp = temp->next;
    }
    
    insert_node_before(temp, moved);
    
    return OK;
}

NODE* search_tab(NODE* sentry, char* name)
{
    NODE* temp;
    memcpy(sentry->name, name, 40);
    strcpy(sentry->url, "NaN");
    temp = sentry;

    while(1)
    {
        temp = temp->next;
        if(strcmp(name, temp->name) == 0) break;   
    }

    if(temp != sentry) return temp;
    return NULL;
}

void print_tabs(BROWSER* this_browser)
{
    NODE* temp;
    temp = this_browser->vigilis;

    do
    {
        temp = temp->next;
        printf("%s %s\n", temp->name, temp->url);
        //sleep(1);
    }while(temp->next != this_browser->vigilis);
}

NODE* new_node()
{
    NODE* new = (NODE*) malloc(sizeof(NODE));

    return new;
}

int insert_node(NODE* previous, NODE* this_node)
{
    this_node->next = previous->next;
    this_node->next->prev = this_node;

    this_node->prev = previous;
    this_node->prev->next = this_node;

    return OK;
}

int insert_node_before(NODE* next, NODE* this_node)
{
    this_node->prev = next->prev;
    this_node->next = next;

    this_node->prev->next = this_node;
    this_node->next->prev = this_node;    

    return OK;
}

int remove_node(NODE* this_node)
{
    this_node->prev->next = this_node->next;
    this_node->next->prev = this_node->prev;

    return OK;
}

int free_node(NODE* this_node)
{
    this_node->next = NULL;
    this_node->prev = NULL;
    free(this_node);

    return OK;
}
