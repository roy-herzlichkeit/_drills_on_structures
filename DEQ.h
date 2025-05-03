#ifndef DEQ_H
#define DEQ_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#define MAX_SIZE 1024

typedef struct double_ended_queue_structure {
    int FRONT, REAR, SIZE;
    int *items;
} deque;

void init(deque*);
int view_front(deque*);
int view_rear(deque*);
void enqueue_front(deque*, int);
void enqueue_rear(deque*, int);
int dequeue_front(deque*);
int dequeue_rear(deque*);
void destroy(deque*);

void init(deque *dq) {
    dq->FRONT = 0;
    dq->REAR = MAX_SIZE - 1;
    dq->SIZE = 0;
    dq->items = (int *)calloc(MAX_SIZE, sizeof(int));
}

int view_front(deque *dq) {
    return dq->FRONT;
}

int view_rear(deque *dq) {
    return dq->REAR;
}

void enqueue_front(deque *dq, int value) {
    dq->FRONT = (dq->FRONT + MAX_SIZE - 1) % MAX_SIZE;
    dq->items[dq->FRONT] = value;
    dq->SIZE++;
}

void enqueue_rear(deque *dq, int value) {
    dq->REAR = (dq->REAR + 1) % MAX_SIZE;
    dq->items[dq->REAR] = value;
    dq->SIZE++;
}

int dequeue_front(deque *dq) {
    if (dq->SIZE == 0) 
        return INT_MAX;
    int res = dq->items[dq->FRONT];
    dq->FRONT = (dq->FRONT + 1) % MAX_SIZE;
    dq->SIZE--;
    if (dq->SIZE == 0) {
        dq->FRONT = 0;
        dq->REAR = MAX_SIZE - 1;
    }
    return res;
}

int dequeue_rear(deque *dq) {
    if (dq->SIZE == 0) 
        return INT_MAX;
    
    int res = dq->items[dq->REAR];
    dq->REAR = (dq->REAR + MAX_SIZE - 1) % MAX_SIZE;
    dq->SIZE--;
    if (dq->SIZE == 0) {
        dq->REAR = 0;
        dq->REAR = MAX_SIZE - 1;
    }
    return res;
}

void destroy(deque *dq) {
    free(dq->items);
    dq->items = NULL;
    dq->SIZE  = 0;
    dq->FRONT = 0;
    dq->REAR  = MAX_SIZE - 1;
}

#endif