#ifndef STACK_H
#define STACK_H

typedef struct _stack STACK;

STACK* stack_create();
void* stack_pop(STACK*);
void* stack_iter(STACK*);
int stack_push(STACK*, void*);
int stack_purge(STACK*);
int stack_get_num(STACK*);
void stack_reset_iter(STACK*);

#endif
