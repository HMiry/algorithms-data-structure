#ifndef _IMPL2
#define _IMPL2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int key;
    struct node *right;
    struct node *left;
} node_t;

#endif
// #include "impl2.h"

void tree_dup(struct node *root) {
    node_t *tmp;

    // Check termination and (eventually) recur
    if (root == NULL) {
        return;
    }

    tree_dup(root->left);
    tree_dup(root->right);

    // Once back, duplicate the node
    tmp = (node_t *) malloc(sizeof(node_t));
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }


    tmp->key = root->key;
    tmp->left = root->left;
    tmp->right = NULL;
    // Link from parent to new node
    root->left = tmp;

    return;
    
}

