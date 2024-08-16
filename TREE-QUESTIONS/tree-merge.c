#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *key;
    struct node *left;
    struct node *right;
} node;

// This function merges the trees as specified.
// It searches for the node to replace in tree 'in' and then replaces it with 'merge'.
void merge_into(node **in, node *merge) {
    // Base case: if the current node is NULL or we find the node to replace
    if (*in == NULL || strcmp((*in)->key, merge->key) == 0) {
        // Replace the node in 'in' with 'merge'
        *in = merge;
        return;
    }

    // Recursively search in the left and right subtrees
    merge_into(&((*in)->left), merge);
    merge_into(&((*in)->right), merge);
}

void treeMerge(node **in, int n) {
    // Start from the second tree and merge it into the first one, then the result with the third, and so on.
    for (int i = 1; i < n; ++i) {
        merge_into(&in[0], in[i]);
    }
}
