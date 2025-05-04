#ifndef STACKLL_H
#define STACKLL_H

#include "SLL.h"

typedef struct stack_structure_ll {
    int SIZE;
    int top;
    node *root;
} stack;

void init(stack *);
void destroy(stack *);
void push(stack *, int);
int pop(stack *);
void stretch(stack *);
void withdraw(stack *);

void init(stack *sp) {
    
}

#endif