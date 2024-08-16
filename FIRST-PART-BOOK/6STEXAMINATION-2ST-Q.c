#ifndef _IMPL2
#define _IMPL2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define L1 10
#define L2 5

struct node {
    int key;
    struct node *left;
    struct node *right;
};

#endif

// #include "impl2.h"

static void path_write_r(struct node *root, int height, int level, struct node **vet);

void path_write(struct node *root, int height) {
    // Array of pointers to nodes of type struct node
    struct node **vet;
    vet = (struct node **) malloc(height * sizeof(struct node *));
    if (vet == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    path_write_r(root, height, 0, vet);

    free(vet);
}

static void path_write_r(struct node *root, int height, int level, struct node **vet) {
    int i;

    if (root == NULL) {
        fprintf(stdout, "Path: ");
        for (i = 0; i < level; i++) {
            fprintf(stdout, "%d ", vet[i]->key);
        }
        fprintf(stdout, "\n");// just for the beautiy :))
        return;
    }

    vet[level] = root;
    path_write_r(root->left, height, level + 1, vet);
    path_write_r(root->right, height, level + 1, vet);
}
