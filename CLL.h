#ifndef CLL_H
#define CLL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct circular_linked_list_structure {
    int val;
    struct circular_linked_list_structure *next;
} node;

static inline node*  create_node(int value);
static inline void   insert_front(node **head, node **tail, int value);
static inline void   insert_rear (node **head, node **tail, int value);
static inline void   insert_after(node **head, node **tail, int value, int location);
static inline void   insert_before(node **head, node **tail, int value, int location);
static inline int    delete_front(node **head, node **tail);
static inline int    delete_rear (node **head, node **tail);
static inline int    delete_node (node **head, node **tail, int value);
static inline void   view       (const node *head);
static inline void   destroy    (node **head, node **tail);
static inline node*  reverse    (node **head, node **tail);
static inline node*  get_rear   (const node *head);

static inline node* create_node(int value) {
    node *nptr = (node*)calloc(1, sizeof *nptr);
    if (!nptr) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    nptr->val  = value;
    nptr->next = nptr;   
    return nptr;
}

static inline void insert_rear(node **head, node **tail, int value) {
    node *nptr = create_node(value);
    if (!*head) {
        *head = *tail = nptr;
    } else {
        (*tail)->next = nptr;
        nptr->next    = *head;
        *tail         = nptr;
    }
}

static inline void insert_front(node **head, node **tail, int value) {
    node *nptr = create_node(value);
    if (!*head) {
        *head = *tail = nptr;
    } else {
        nptr->next    = *head;
        (*tail)->next = nptr;
        *head         = nptr;
    }
}

static inline void insert_before(node **head, node **tail, int value, int location) {
    if (!*head) return;
    if ((*head)->val == location) {
        insert_front(head, tail, value);
        return;
    }
    node *prev = *head, *curr = (*head)->next;
    while (curr != *head && curr->val != location) {
        prev = curr;
        curr = curr->next;
    }
    if (curr->val == location) {
        node *nptr = create_node(value);
        prev->next = nptr;
        nptr->next = curr;
    }
}

static inline void insert_after(node **head, node **tail, int value, int location) {
    if (!*head) return;
    node *curr = *head;
    do {
        if (curr->val == location) {
            node *nptr = create_node(value);
            nptr->next = curr->next;
            curr->next = nptr;
            if (curr == *tail) 
                *tail = nptr;
            return;
        }
        curr = curr->next;
    } while (curr != *head);
}

static inline int delete_front(node **head, node **tail) {
    if (!*head) return INT_MIN;
    node *ptr = *head;
    int    v   = ptr->val;
    if (*head == *tail) {
        *head = *tail = NULL;
    } else {
        *head         = ptr->next;
        (*tail)->next = *head;
    }
    free(ptr);
    return v;
}

static inline int delete_rear(node **head, node **tail) {
    if (!*head) return INT_MIN;
    node *ptr = *head;
    int    v;
    if (*head == *tail) {
        v = (*tail)->val;
        free(*tail);
        *head = *tail = NULL;
    } else {
        while (ptr->next != *tail) 
            ptr = ptr->next;
        node *tmp    = *tail;
        v            = tmp->val;
        ptr->next    = *head;
        *tail        = ptr;
        free(tmp);
    }
    return v;
}

static inline int delete_node(node **head, node **tail, int value) {
    if (!*head) return INT_MIN;
    if ((*head)->val == value) 
        return delete_front(head, tail);
    if ((*tail)->val == value) 
        return delete_rear(head, tail);
    node *prev = *head, *curr = prev->next;
    while (curr != *head && curr->val != value) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == *head) 
        return INT_MIN;
    prev->next = curr->next;
    int ret    = curr->val;
    free(curr);
    return ret;
}

static inline void view(const node *head) {
    if (!head) {
        printf("List is empty.\n");
        return;
    }
    const node *it = head;
    printf("HEAD -> ");
    do {
        printf("%d -> ", it->val);
        it = it->next;
    } while (it != head);
    printf("HEAD\n");
}

static inline void destroy(node **head, node **tail) {
    if (!*head) return;
    (*tail)->next = NULL;      
    node *curr = *head, *next;
    while (curr) {
        next = curr->next;
        free(curr);
        curr = next;
    }
    *head = *tail = NULL;
}

static inline node* reverse(node **head, node **tail) {
    if (!*head) return NULL;
    node *prev = *tail, *curr = *head, *next;
    do {
        next       = curr->next;
        curr->next = prev;
        prev       = curr;
        curr       = next;
    } while (curr != *head);
    node *old_head = *head;
    *head = *tail;
    *tail = old_head;
    return *head;
}

static inline node* get_rear(const node *head) {
    if (!head) return NULL;
    const node *it = head;
    while (it->next != head) 
        it = it->next;
    return (node*)it;
}

#endif  // CLL_H