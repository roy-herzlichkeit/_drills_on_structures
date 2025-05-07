#ifndef BST_H
#define BST_H

#include <cstdlib>
#include "BINTREE.h"

/*PROTOTYPES*/
static inline node* insert_node(node*, int);
static inline node* delete_node(node*, int);
inline static node* find_minima(node*);

static inline node* insert_node(node *root, int value) {
    if (!root) {
        return create_node(value);
    }
    if (value > root->val) {
        root->right = insert_node(root->right, value);
    } else {
        root->left = insert_node(root->left, value);
    }
    return root;
}

static inline node* delete_node(node *root, int value) {
        if (root) {
            if (value > root->val) {
            if (value > root->val) {
                root->right = delete_node(root->right, value);
            } else if (value < root->val) {
                root->left = delete_node(root->left, value);
            } else {
                if (!root->left && !root->right) {
                    free(root);
                    return NULL;
                } else if (!root->left || !root->right) {
                    node *temp = root->left ? root->left : root->right;
                    free(root);
                    return temp;
                } else {
                    node *minima = find_minima(root->right);
                    root->val = minima->val;
                    root->right = delete_node(root->right, minima->val);
                }
            }
        }
        return root;
    }
}

static inline node* find_minima(node* root) {
    while (root->left)
        root = root->left;
    return root;
}

#endif