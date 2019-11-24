#ifndef STACK_H
#define STACK_H

//stack for storing chars

typedef struct _stack STACK;

STACK* stack_create();
void stack_push(STACK*, char);
char stack_pop(STACK*);

#endif
