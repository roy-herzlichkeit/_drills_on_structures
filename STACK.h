#ifndef STACK_H
#define STACK_H

// header files
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// stack structure
typedef struct stack_structure
{
    int SIZE;
    int top;
    int *items;
} stack;

// prototypes
void init(stack *);
void destroy(stack *);
void push(stack *, int);
int pop(stack *);
void stretch(stack *);
void withdraw(stack *);

// stack initialiser
void init(stack *sp)
{
    sp->SIZE = 1;
    sp->top = 0;
    sp->items = (int *)malloc(sp->SIZE * sizeof *sp->items);
    if (!sp->items)
    {
        perror("malloc");
        exit(1);
    }
}

// stack destroyer
void destroy(stack *sp)
{
    free(sp->items);
    free(sp);
}

// stack stretcher
void stretch(stack *sp)
{
    int new_size = sp->SIZE * 2;
    int *tmp = (int *)realloc(sp->items, new_size * sizeof *sp->items);
    if (!tmp)
    {
        perror("realloc");
        exit(1);
    }
    sp->items = tmp;
    sp->SIZE = new_size;
}

// stack withdrawer
void withdraw(stack *sp)
{
    int new_size = sp->SIZE / 2;
    if (new_size < 1)
        new_size = 1;
    int *tmp = (int *)realloc(sp->items, new_size * sizeof *sp->items);
    if (!tmp)
    {
        perror("realloc");
        exit(1);
    }
    sp->items = tmp;
    sp->SIZE = new_size;
}

// stack insertor
void push(stack *sp, int value)
{
    if (sp->top == sp->SIZE)
    {
        stretch(sp);
    }
    sp->items[sp->top++] = value;
}

// stack popper
int pop(stack *sp)
{
    if (sp->top == 0)
    {
        fprintf(stderr, "__stack_underflow__\n");
        return INT_MIN;
    }
    int value = sp->items[--sp->top];
    if (sp->top < sp->SIZE / 2)
    {
        withdraw(sp);
    }
    return value;
}

#endif