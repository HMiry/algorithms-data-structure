#include <stdio.h>
#include <stdlib.h>

// Define the struct element as a binary tree node.
typedef struct element {
    int key;
    struct element *left;
    struct element *right;
} element_t;

// Helper function to find and print similar pairs recursively
void find_similar_pairs(element_t *node, element_t *ancestor, int k) {
    if (node == NULL || ancestor == NULL) {
        return;
    }
    
    // Check if the current node and its ancestor satisfy the condition
    if (abs(ancestor->key - node->key) <= k) {
        printf("(%d, %d)\n", ancestor->key, node->key);
    }

    // Recur for left and right subtrees
    find_similar_pairs(node->left, ancestor, k);
    find_similar_pairs(node->right, ancestor, k);
}

// Wrapper function to initiate recursive search from each node
void tree_similar_pairs(element_t *root, int k) {
    if (root == NULL) {
        return;
    }

    // Start recursion for each subtree
    find_similar_pairs(root->left, root, k);
    find_similar_pairs(root->right, root, k);

    // Continue with the rest of the tree
    tree_similar_pairs(root->left, k);
    tree_similar_pairs(root->right, k);
}

// Example usage and tree construction
int main() {
    // Construct the tree as given in the example
    element_t n1 = {1, NULL, NULL};
    element_t n9 = {9, NULL, NULL};
    element_t n3 = {3, &n1, &n9};
    element_t n5 = {5, NULL, NULL};
    element_t n10 = {10, &n3, &n5};
    
    element_t n7 = {7, NULL, NULL};
    element_t n4 = {4, NULL, NULL};
    element_t n21 = {21, &n7, NULL};
    element_t n8 = {8, &n21, &n4};
    
    element_t root = {10, &n10, &n8}; // Root node with key 10

    int k = 1; // As given in the example
    tree_similar_pairs(&root, k);

    return 0;
}
