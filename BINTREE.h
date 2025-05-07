#ifndef BINTREE_H
#define BINTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct BINARY_TREE_STRUCTURE {
    int val;
    struct BINARY_TREE_STRUCTURE *left, *right;
} node;

node* create_node(int);
void inorder(node*, char*, int);
void preorder(node*, char*, int);
void postorder(node*, char*, int);
node* read(char*);
void write(char*, node*);
node* make_phi(char*, char*);
node* make_psi(char*, char*);
void destroy(node**);

static void inorder_print(node *root, FILE *fps);
static void preorder_print(node *root, FILE *fps);
static void postorder_print(node *root, FILE *fps);

node* create_node(int val) {
    node* nptr = (node*)malloc(sizeof(node));
    if (!nptr) return NULL;
    nptr->val = val;
    nptr->left = nptr->right = NULL;
    return nptr;
}

void inorder(node* root, char* s, int i) {
    if (root == NULL) return;
    inorder(root->left, s, i);
    s[i++] = root->val;
    inorder(root->right, s, i);
}

void preorder(node* root, char* s, int i) {
    if (root == NULL) return;
    s[i++] = root->val;
    preorder(root->left, s, i);
    preorder(root->right, s, i);
}

void postorder(node* root, char* s, int i) {
    if (root == NULL) return;
    s[i++] = root->val;
    postorder(root->left, s, i);
    postorder(root->right, s, i);
}

void write(char *dest, node *root) {
    FILE *fps = fopen(dest, "w");
    if (!fps) return;
    inorder_print(root, fps);
    fprintf(fps, "\n");
    preorder_print(root, fps);
    fprintf(fps, "\n");
    postorder_print(root, fps);
    fprintf(fps, "\n");
    fclose(fps);
}

static void inorder_print(node *root, FILE *fps) {
    if (!root) return;
    inorder_print(root->left, fps);
    fprintf(fps, "%d ", root->val);
    inorder_print(root->right, fps);
}
static void preorder_print(node *root, FILE *fps) {
    if (!root) return;
    fprintf(fps, "%d ", root->val);
    preorder_print(root->left, fps);
    preorder_print(root->right, fps);
}
static void postorder_print(node *root, FILE *fps) {
    if (!root) return;
    postorder_print(root->left, fps);
    postorder_print(root->right, fps);
    fprintf(fps, "%d ", root->val);
}

node* read(char *src) {
    FILE *fps = fopen(src, "r");
    if (!fps) return NULL;
    node *dummy = create_node(0), *tail = dummy;
    char *s1 = (char*)malloc(100), *s2 = (char*)malloc(100);
    int num;
    fscanf(fps, "%d\n", &num);
    fgets(s1, 100, fps);
    fgets(s2, 100, fps);
    {
        char *p = s1, *w = s1;
        int val, nch;
        while (sscanf(p, "%d%n", &val, &nch) == 1) {
            *w++ = (char)val;
            p += nch;
        }
        *w = '\0';
    }
    {
        char *p = s2, *w = s2;
        int val, nch;
        while (sscanf(p, "%d%n", &val, &nch) == 1) {
            *w++ = (char)val;
            p += nch;
        }
        *w = '\0';
    }

    node *res = num == 0 ? make_phi(s1, s2) : make_psi(s1, s2);
    fclose(fps);
    free(s1);
    free(s2);
    free(dummy);
    return res;
}

static node* build_tree_phi(const char* in, int in_lo, int in_hi, const char* pre, int pre_lo, int pre_hi) {
    if (pre_lo > pre_hi || in_lo > in_hi) return NULL;
    int root_val = (int)pre[pre_lo];
    node* root = (node*)malloc(sizeof(node));
    if (!root) return NULL;
    root->val = root_val;
    root->left = root->right = NULL;
    int i = in_lo;
    while (i <= in_hi && (int)in[i] != root_val) ++i;
    int left_size = i - in_lo;
    root->left = build_tree_phi(in, in_lo, i - 1, pre, pre_lo + 1, pre_lo + left_size);
    root->right = build_tree_phi(in, i + 1, in_hi, pre, pre_lo + left_size + 1, pre_hi);
    return root;
}

node* make_phi(char* s_in, char* s_pre) {
    if (!s_in || !s_pre || s_pre[0] == '\0') return NULL;
    int n = 0;
    while (s_pre[n]) ++n;
    return build_tree_phi(s_in, 0, n - 1, s_pre, 0, n - 1);
}

static node* build_tree_psi(const char* in, int in_lo, int in_hi, const char* post, int post_lo, int post_hi) {
    if (post_lo > post_hi || in_lo > in_hi) return NULL;
    int root_val = (int)post[post_hi];
    node* root = (node*)malloc(sizeof(node));
    if (!root) return NULL;
    root->val = root_val;
    root->left = root->right = NULL;
    int i = in_lo;
    while (i <= in_hi && (int)in[i] != root_val) ++i;
    int left_size = i - in_lo;
    root->left = build_tree_psi(in, in_lo, i - 1, post, post_lo, post_lo + left_size - 1);
    root->right = build_tree_psi(in, i + 1, in_hi, post, post_lo + left_size, post_hi - 1);
    return root;
}

node* make_psi(char* s_in, char* s_post) {
    if (!s_in || !s_post || s_post[0] == '\0') return NULL;
    int n = 0;
    while (s_post[n]) ++n;
    return build_tree_psi(s_in, 0, n - 1, s_post, 0, n - 1);
}

void destroy(node **root) {
    if (!root || !*root) return;
    destroy(&(*root)->left);
    destroy(&(*root)->right);
    free(*root);
    *root = NULL;
}

#endif
