#ifndef SLL_H
#define SLL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef struct linked_list_structure {
    int val;
    struct linked_list_structure *next;
} node;

node* create_node(int);
void insert_front(node**, int);
void insert_rear(node**, int);
void insert_after(node*, int, int);
void insert_before(node**, int, int);
int delete_front(node**);
int delete_rear(node**);
int delete_node(node**, int);
void view(node *);
void destroy(node **);
node* read_file(char*);
void write_file(char*, node*);
node* reverse(node *);

node* create_node(int value) {
    node *nptr = (node*)malloc(sizeof *nptr);
    if (!nptr) {
        perror("__malloc__\n");
        exit(EXIT_FAILURE);
    }
    nptr->val = value;
    nptr->next = NULL;
    return nptr;
}

void insert_front(node **ptr, int value) {
    node *nptr = create_node(value);
    nptr->next = *ptr;
    *ptr = nptr;
}

void insert_rear(node **ptr, int value) {
    node *nptr = create_node(value);
    if (!*ptr) {
        *ptr = nptr;
        return;
    }
    node *it = *ptr;
    while (it->next != NULL)
        it = it->next;
    it->next = nptr;
}

void insert_after(node *ptr, int value, int location) {
    if (!ptr) 
        return;
    node *it = ptr;
    while (it != NULL && it->val != location)
        it = it->next;
    if (it != NULL) {
        node *nptr = create_node(value);
        nptr->next = it->next;
        it->next = nptr;
    }
}

void insert_before(node **ptr, int value, int location) {
    if (!*ptr)
        return;
    if ((*ptr)->val == location) {
        insert_front(ptr, value);
        return;
    }
    node *it = *ptr, *prev = NULL;
    while (it != NULL && it->val != location) {
        prev = it;
        it = it->next;
    }
    if (it != NULL) {
        node *nptr = create_node(value);
        prev->next = nptr;
        nptr->next = it;
    }
}

int delete_front(node **ptr) {
    if (!*ptr)
        return INT_MAX;
    node *nptr = *ptr;
    int temp = (*ptr)->val;
    *ptr = (*ptr)->next;
    nptr->next = NULL;
    destroy(&nptr);
    return temp;
}

int delete_rear(node **ptr) {
    if (!*ptr)
        return INT_MAX;
    int temp;
    if ((*ptr)->next == NULL) {
        temp = (*ptr)->val;
        destroy(ptr);
        return temp;
    }
    node *prev = NULL, *it = *ptr;
    while (it->next != NULL) {
        prev = it;
        it = it->next;
    }
    temp = it->val;
    prev->next = NULL;
    destroy(&it);
    return temp;
}

int delete_node(node **ptr, int value) {
    if (!*ptr)
        return INT_MAX;
    int temp = INT_MAX;
    if ((*ptr)->val == value) {
        delete_front(ptr);
        return value;
    }
    node *rear = NULL, *it = *ptr, *front = it->next;
    while (it->val != value && front != NULL) {
        rear = it;
        it = front;
        front = front->next;
    }
    if (front == NULL && it->val == value) {
        temp = value;
        delete_rear(ptr);
    } else if (it->val == value) {
        temp = value;
        rear->next = front;
        it->next = NULL;
        destroy(&it);
    }
    return temp;
}

void view(node *ptr) {
    for (node *it = ptr; it != NULL; it = it->next) {
        printf("%d -> ", it->val);
    }
    printf("NULL\n");
}

void destroy(node **ptr) {
    node *tmp;
    while (*ptr) {
        tmp = (*ptr)->next;
        free(*ptr);
        *ptr = tmp;
    }
    *ptr = NULL;
}

node* read_file(char *source) {
    FILE *fps = fopen(source, "r");
    if (!fps) {
        fprintf(stderr, "Error opening file %s\n", source);
        return NULL;
    }
    node *dummy = create_node(0), *tail = dummy;
    int num;
    while (fscanf(fps, "%d", &num) == 1) {
        node *nptr = create_node(num);
        tail->next = nptr;
        tail = tail->next;
    }
    fclose(fps);
    node *head = dummy->next;
    free(dummy);
    return head;
}

void write_file(char *dest, node *head) {
    FILE *fps = fopen(dest, "w");
    if (!fps) {
        fprintf(stderr, "Error opening file %s\n", dest);
        return;
    }
    for (node *it = head; it; it = it->next)
        fprintf(fps, "%d ", it->val);
    fclose(fps);
}

node* reverse(node *head) {
    node* prev, *curr, *next;
    prev = NULL;
    if (head != NULL) 
        curr = head;
    else    
        return head;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = curr;
    return prev;
}

#endif