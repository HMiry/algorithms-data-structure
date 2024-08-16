// Defines a function to calculate distance for BSTs given a root node and two keys
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
-----------------------------------------------------------------------------------------------------------

// Defines a function to calculate distance for non-BST binary trees given a root node and two keys
int visit_ver2(node_t *root, int key1, int key2) {
    int t_right, t_left, t_here;

    // Initialize variables to track distances and presence of keys
    t_here = 0; // Flag to check if current node contains either key
    t_right = t_left = 0; // Distances to the right and left child

    // Base case: if current node is NULL, return -1
    if (root == NULL) {
        return (-1);
    }

    // Check if current node contains either of the keys
    if ((key1==root->key) || (key2==root->key)) {
        t_here = 1; // Mark that one key is found at this node
    }

    // Recursively visit left and right children
    t_left = visit_ver2(root->left, key1, key2);
    t_right = visit_ver2(root->right, key1, key2);

    // If both keys are found in different subtrees, calculate and print the distance
    if (t_left != -1 && t_right != -1) {
        fprintf(stdout, "Distance between %d and %d: ", key1, key2);
        fprintf(stdout, "%d edges\n", t_left + t_right);
        return (t_left + t_right + (t_here ? 0 : -1));
    } else if (t_here) {
        // If one key is at the current node and the other is in one of the subtrees
        return (t_left + t_right + 1);
    }

    // If one key is found in one of the subtrees, print the distance considering the current node as well
    if (t_left != -1 || t_right != -1) {
        fprintf(stdout, "Distance between %d and %d: ", key1, key2);
        fprintf(stdout, "%d edges\n", t_left + t_right + 1);
    }
    // Return the total distance or -1 if neither key is found
    return (t_left + t_right + 1);
}
