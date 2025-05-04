#ifndef DLL_H
#define DLL_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct doubly_linked_list_structure
{
    int val;
    struct doubly_linked_list_structure *next, *prev;
} node;

node *create_node(int);
void insert_front(node **, int);
void insert_rear(node **, int);
void insert_after(node **, int, int);
void insert_before(node **, int, int);
int delete_front(node **);
int delete_rear(node **);
int delete_node(node **, int);
void view(const node *);
void destroy(node **);
node *read_file(const char *);
void write_file(const char *, const node *);
node *reverse(node *);

node *create_node(int value)
{
    node *n = (node *)malloc(sizeof *n);
    if (!n)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    n->val = value;
    n->next = n->prev = NULL;
    return n;
}

void insert_front(node **head, int value)
{
    node *n = create_node(value);
    n->next = *head;
    if (*head)
        (*head)->prev = n;
    *head = n;
}

void insert_rear(node **head, int value)
{
    node *n = create_node(value);
    if (!*head)
    {
        *head = n;
        return;
    }
    node *it = *head;
    while (it->next)
        it = it->next;
    it->next = n;
    n->prev = it;
}

void insert_after(node **head, int value, int location)
{
    node *it = *head;
    while (it && it->val != location)
        it = it->next;
    if (!it)
        return;
    node *n = create_node(value);
    n->prev = it;
    n->next = it->next;
    if (it->next)
        it->next->prev = n;
    it->next = n;
}

void insert_before(node **head, int value, int location)
{
    node *it = *head;
    while (it && it->val != location)
        it = it->next;
    if (!it)
        return;
    node *n = create_node(value);
    n->next = it;
    n->prev = it->prev;
    if (it->prev)
        it->prev->next = n;
    else
        *head = n;
    it->prev = n;
}

int delete_front(node **head)
{
    if (!*head)
        return INT_MAX;
    node *n = *head;
    int v = n->val;
    *head = n->next;
    if (*head)
        (*head)->prev = NULL;
    free(n);
    return v;
}

int delete_rear(node **head)
{
    if (!*head)
        return INT_MAX;
    node *it = *head;
    while (it->next)
        it = it->next;
    int v = it->val;
    if (it->prev)
    {
        it->prev->next = NULL;
    }
    else
    {
        *head = NULL;
    }
    free(it);
    return v;
}

int delete_node(node **head, int value)
{
    if (!*head)
        return INT_MAX;
    node *it = *head;
    while (it && it->val != value)
        it = it->next;
    if (!it)
        return INT_MAX;
    if (it->prev)
        it->prev->next = it->next;
    else
        *head = it->next;
    if (it->next)
        it->next->prev = it->prev;
    int v = it->val;
    free(it);
    return v;
}

void view(const node *head)
{
    for (const node *it = head; it; it = it->next)
        printf("%d <=> ", it->val);
    printf("NULL\n");
}

void destroy(node **head)
{
    node *it = *head, *tmp;
    while (it)
    {
        tmp = it->next;
        free(it);
        it = tmp;
    }
    *head = NULL;
}

node *read_file(const char *source)
{
    FILE *fps = fopen(source, "r");
    if (!fps)
    {
        fprintf(stderr, "Error opening %s\n", source);
        return NULL;
    }
    node *head = NULL, *tail = NULL;
    int num;
    while (fscanf(fps, "%d", &num) == 1)
    {
        node *n = create_node(num);
        if (!head)
            head = tail = n;
        else
        {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
    }
    fclose(fps);
    return head;
}

void write_file(const char *dest, const node *head)
{
    FILE *fps = fopen(dest, "w");
    if (!fps)
    {
        fprintf(stderr, "Error opening %s\n", dest);
        return;
    }
    for (const node *it = head; it; it = it->next)
        fprintf(fps, "%d ", it->val);
    fclose(fps);
}

node *reverse(node *head)
{
    node *cur = head, *tmp = NULL;
    while (cur)
    {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }
    if (tmp)
        head = tmp->prev;
    return head;
}

#endif