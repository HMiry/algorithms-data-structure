#include <stdio.h>
#include <stdlib.h> // For abs()

typedef struct tElement {
    int key;
    struct tElement *left, *right;
} tElement;

void check_and_print_similar_pairs(tElement* node, tElement* ancestor, int k) {
    if (node == NULL) {
        return;
    }

    // If ancestor is not NULL, compare node's key with ancestor's key
    if (ancestor != NULL && abs(node->key - ancestor->key) <= k) {
        printf("(%d, %d)\n", ancestor->key, node->key);
    }

    // Recursively check the left and right children
    check_and_print_similar_pairs(node->left, ancestor, k);
    check_and_print_similar_pairs(node->right, ancestor, k);
}

void tree_similar_pairs(tElement* root, int k) {
    if (root == NULL) {
        return;
    }

    // Check the current node with all its descendants
    check_and_print_similar_pairs(root->left, root, k); // Check all left descendants
    check_and_print_similar_pairs(root->right, root, k); // Check all right descendants

    // Recursively find similar pairs for all nodes in the left and right subtrees
    tree_similar_pairs(root->left, k);
    tree_similar_pairs(root->right, k);
}

// You would call this function with the root of your tree and the constant k.
// Example: tree_similar_pairs(root, 3);
