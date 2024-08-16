// Defines a function to calculate distance for BSTs given a root node and two keys
// to find the longest path which values are also increasing 
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node_t;

int visit_ver1(node_t *root, int key1, int key2) {
    int d, d_left, d_right;

    // Base case: if current node is NULL, return 0
    if (root == NULL) {
        return (0);
    }

    // Case when both keys are on different sides of the root
    if (key1<root->key && key2>root->key) {
        d_left = visit_ver1(root->left, key1, key2); // Visit left subtree
        d_right = visit_ver1(root->right, key1, key2); // Visit right subtree
        d = d_left + d_right; // Distance is the sum of distances from left and right
    } else if (key1>root->key && key2>root->key) {
        // Case when both keys are greater than root's key, go right
        d = visit_ver1(root->right, key1, key2);
    } else {
        // Case when both keys are less or one matches the root, find individual distances
        d_left = visit(root, key1);
        d_right = visit(root, key2);
        d = d_left + d_right;
    }

    // Return the calculated distance
    return (d);
}

// Helper function to find the distance of a key from the root in a BST or calculating the depth
static int visit(node_t *root, int key) {
    int d;

    // Base case: if current node is NULL, return -1
    if (root == NULL) {
        return (-1);
    }

    // If key is less than root's key, go left and add 1 to distance if found
    if (key<root->key) {
        d = visit(root->left, key);
        if (d>-1) {
            return (d+1);
        }
    }

    // If key is greater than root's key, go right and add 1 to distance if found
    if (key>root->key) {
        d = visit(root->right, key);
        if (d>-1) {
            return (d+1);
        }
    }

    // If key matches the root's key, return 0 as distance
    return (0);
}
