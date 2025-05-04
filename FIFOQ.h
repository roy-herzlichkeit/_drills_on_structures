#ifndef FIFOQ_H
#define FIFOQ_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 4

typedef struct queue_structure {
    int FRONT;
    int REAR;
    int SIZE;
    int *items;
} queue;

void init(queue *q) {
    q->FRONT = q->REAR = 0;
    q->SIZE = 0;
    q->items = (int *)calloc(MAX_SIZE, sizeof(int));
    if (!q->items) {
        perror("calloc failed");
        exit(EXIT_FAILURE);
    }
}

int dequeue(queue *q) {
    if (q->SIZE == 0) {
        return INT_MAX;
    }
    int res = q->items[q->FRONT];
    q->FRONT++;
    q->SIZE--;
    return res;
}

void enqueue(queue *q, int value) {
    if (q->SIZE == MAX_SIZE) {
        fprintf(stderr, "__QUEUE_LIMIT_REACHED__\n");
        return;
    }
    q->REAR++;
    q->items[q->REAR] = value;
    q->SIZE++;
}

void destroy(queue *q) {
    free(q->items);
    q->items = NULL;
    q->SIZE = q->FRONT = q->REAR = 0;
    free(q);
}

#endif