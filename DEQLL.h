#ifndef DEQLL_H
#define DEQLL_H

#include "DLL.h"
#include <limits.h>

typedef struct deque_structure_ll
{
    node *front, *rear;
    int size;
} deque;

static inline void init(deque *dq)
{
    dq->front = dq->rear = NULL;
    dq->size = 0;
}

static inline int view_front(const deque *dq)
{
    return dq->front ? dq->front->val : INT_MIN;
}
static inline int view_rear(const deque *dq)
{
    return dq->rear ? dq->rear->val : INT_MIN;
}

static inline void enqueue_front(deque *dq, int value)
{
    node *n = create_node(value);
    n->next = dq->front;
    n->prev = NULL;
    if (dq->front)
        dq->front->prev = n;
    else
        dq->rear = n;
    dq->front = n;
    dq->size++;
}

static inline void enqueue_rear(deque *dq, int value)
{
    node *n = create_node(value);
    n->prev = dq->rear;
    n->next = NULL;
    if (dq->rear)
        dq->rear->next = n;
    else
        dq->front = n;
    dq->rear = n;
    dq->size++;
}

static inline int dequeue_front(deque *dq)
{
    if (!dq->front)
        return INT_MIN;
    node *n = dq->front;
    int v = n->val;
    dq->front = n->next;
    if (dq->front)
        dq->front->prev = NULL;
    else
        dq->rear = NULL;
    free(n);
    dq->size--;
    return v;
}

static inline int dequeue_rear(deque *dq)
{
    if (!dq->rear)
        return INT_MIN;
    node *n = dq->rear;
    int v = n->val;
    dq->rear = n->prev;
    if (dq->rear)
        dq->rear->next = NULL;
    else
        dq->front = NULL;
    free(n);
    dq->size--;
    return v;
}

static inline void destroy_deque(deque *dq)
{
    destroy(&dq->front);
    dq->rear = NULL;
    dq->size = 0;
}

#endif