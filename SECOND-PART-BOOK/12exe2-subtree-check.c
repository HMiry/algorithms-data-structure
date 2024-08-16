#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} node_t;
int are_identical(node_t *r1, node_t *r2) {
    // If both trees are empty, they are identical
    if (r1 == NULL && r2 == NULL) return 1;

    // If one tree is empty and the other is not, they are not identical
    if (r1 == NULL || r2 == NULL) return 0;

    // If the values of the current nodes are different, the trees are not identical
    if (r1->value != r2->value) return 0;

    // Recursively check the left and right subtrees
    return are_identical(r1->left, r2->left) && are_identical(r1->right, r2->right);
}
int is_subtree(node_t *r1, node_t *r2) {
    // If r1 is NULL, then it is a subtree of r2
    if (r1 == NULL) return 1;

    // If r2 is NULL, then r1 can't be a subtree of r2
    if (r2 == NULL) return 0;

    // If the two trees are identical, return 1
    if (are_identical(r1, r2)) return 1;

    // Check if r1 is a subtree of the left or right subtree of r2
    return is_subtree(r1, r2->left) || is_subtree(r1, r2->right);
}






#include <stdio.h>
#include <stdbool.h>

// Define the binary tree node structure
typedef struct node {
    int value;
    struct node *left;
    struct node *right;
} node_t;

// Helper function to check if two subtrees are identical
bool are_identical(node_t *r1, node_t *r2) {
    // Both empty
    if (r1 == NULL && r2 == NULL) return true;

    // One is empty, one is not
    if (r1 == NULL || r2 == NULL) return false;

    // Check if the data of both roots is the same and data of left and right
    // subtrees are also the same
    return (r1->value == r2->value) && 
           are_identical(r1->left, r2->left) && 
           are_identical(r1->right, r2->right);
}

// Helper function to check if r1 is a subtree of r2
bool is_subtree(node_t *r1, node_t *r2) {
    // BASE CASE
    if (r1 == NULL) return true;

    if (r2 == NULL) return false;

    // Check if the tree rooted at r2 contains the tree rooted at r1
    if (are_identical(r1, r2)) return true;

    // Check the subtrees recursively
    return is_subtree(r1, r2->left) || is_subtree(r1, r2->right);
}

// Function to check if r1 is a subtree of r2
int subtree_check(node_t *r1, node_t *r2) {
    return is_subtree(r1, r2) ? 1 : 0;
}

// Example usage
int main() {
    node_t n1 = {25, NULL, NULL};
    node_t n2 = {15, NULL, NULL};
    node_t n3 = {10, &n1, &n2}; // This is r1

    node_t n4 = {12, NULL, NULL};
    node_t n5 = {30, NULL, NULL};
    node_t n6 = {25, &n4, &n5};
    node_t n7 = {15, NULL, NULL};
    node_t n8 = {10, &n6, &n7}; // This is r2

    int result = subtree_check(&n3, &n8);
    printf("Is r1 a subtree of r2? %s\n", result ? "Yes" : "No");

    return 0;
}


