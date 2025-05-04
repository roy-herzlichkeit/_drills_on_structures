#ifndef FIFOQLL_H
#define FIFOQLL_H

#include "SLL.h"

typedef struct queue_structure_ll {
    node *root;
    int SIZE = 0;
} queue;

void init(queue*);
int dequeue(queue*);
void enqueue(queue*, int);
void destroy(queue*);

static inline void init(queue *q) {
    q->root = NULL;
    q->SIZE = 0;
}

static inline int dequeue(queue *q) {
    if (!q->root)
        return INT_MIN;
    q->SIZE--;
    return delete_front(&q->root);
}

static inline void enqueue(queue *q, int value) {
    q->SIZE++;
    insert_front(&q->root, value);
}

static inline void destroy_queue(queue *q) {
    destroy(&q->root);
    q->SIZE = 0;
}

#endif