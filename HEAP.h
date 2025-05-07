#ifndef HEAP_C
#define HEAP_C

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct heap_structure {
    int SIZE;    
    int *A;     
} heap;

/* PROTOTYPES */
int PARENT(int);
int LEFT(int);
int RIGHT(int);
void max_heapify(heap*, int);
void build_max_heap(heap*);
void heapsort(heap*);
int heap_extract_max(heap*);
void heap_increase_key(heap*, int, int);
void max_heap_insert(heap*, int);

int PARENT(int i) {
    return i / 2;
}

int LEFT(int i) {
    return 2 * i;
}

int RIGHT(int i) {
    return 2 * i + 1;
}

void max_heapify(heap* H, int i) {
    int l = LEFT(i),
        r = RIGHT(i),
        largest = i;
    if (l <= H->SIZE && H->A[l] > H->A[largest])
        largest = l;
    if (r <= H->SIZE && H->A[r] > H->A[largest])
        largest = r;
    if (largest != i) {
        int tmp = H->A[i];
        H->A[i] = H->A[largest];
        H->A[largest] = tmp;
        max_heapify(H, largest);
    }
}

void build_max_heap(heap* H) {
    for (int i = H->SIZE / 2; i >= 1; --i)
        max_heapify(H, i);
}

void heapsort(heap* H) {
    build_max_heap(H);
    int original_size = H->SIZE;
    for (int i = H->SIZE; i >= 2; --i) {
        int tmp = H->A[1];
        H->A[1] = H->A[i];
        H->A[i] = tmp;
        H->SIZE--;
        max_heapify(H, 1);
    }
    H->SIZE = original_size;
}

int heap_extract_max(heap* H) {
    if (H->SIZE < 1) {
        fprintf(stderr, "__heap underflow__\n");
        exit(EXIT_FAILURE);
    }
    int max = H->A[1];
    H->A[1] = H->A[H->SIZE];
    H->SIZE--;
    max_heapify(H, 1);
    return max;
}

void heap_increase_key(heap* H, int i, int key) {
    if (key < H->A[i]) {
        fprintf(stderr, "__provide a larger key__\n");
        exit(EXIT_FAILURE);
    }
    H->A[i] = key;
    while (i > 1 && H->A[PARENT(i)] < H->A[i]) {
        int tmp = H->A[i];
        H->A[i] = H->A[PARENT(i)];
        H->A[PARENT(i)] = tmp;
        i = PARENT(i);
    }
}

void max_heap_insert(heap* H, int key) {
    H->A = (int*)realloc(H->A, (H->SIZE + 2) * sizeof(int));
    if (!H->A) {
        perror("__realloc failed__");
        exit(EXIT_FAILURE);
    }
    H->SIZE++;
    H->A[H->SIZE] = INT_MIN;
    heap_increase_key(H, H->SIZE, key);
}

#endif