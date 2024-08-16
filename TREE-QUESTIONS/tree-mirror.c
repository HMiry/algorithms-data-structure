#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node_s{
    int key;
    struct node_s *left;
    struct node_s *right;

}node_t;
// Function prototype for creating a new node.


// Function to create a mirror of a binary tree.
node_t *tree_mirror(node_t *root) {
    node_t *node;

    if (root==NULL) {
        return NULL;
    }

    node = (node_t *) malloc(1 * sizeof(node_t));
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);}

    node->key = root->key;
    node->right = tree_mirror(root->left);
    node->left = tree_mirror(root->right);
    return (node);
}



