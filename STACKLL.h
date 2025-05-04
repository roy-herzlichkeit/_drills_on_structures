#ifndef STACKLL_H
#define STACKLL_H

#include "SLL.h"

typedef struct stack_structure_ll {
    int top;
    node *root;
} stack;

void init(stack *);
void destroy_stack(stack *);
void push(stack *, int);
int pop(stack *);

void init(stack *sp) {
    sp->top = 0;
    sp->root = (node *)malloc(sizeof *sp->root);
    if (!sp->root) {
        perror("__malloc__\n");
        exit(1);
    }
}

void destroy_stack(stack *sp) {
    destroy(&sp->root);
    free(sp);
}

void push(stack *sp, int value) {
    insert_front(&sp->root, value);
    sp->top++;
}

int pop(stack *sp) {
    if (sp->top == 0) {
        return INT_MIN;
    }
    int value = delete_front(&sp->root);
    sp->top--;
    return value;
}

#endif