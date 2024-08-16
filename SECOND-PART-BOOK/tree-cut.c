#include <stdio.h>
#include <stdlib.h>

typedef struct element {
    int key;
    struct element *left;
    struct element *right;
} element;

// Helper function to compute the sum of all nodes in the tree
int tree_sum(element *root) {
    if (root == NULL) return 0;
    return root->key + tree_sum(root->left) + tree_sum(root->right);
}
// Global variables to keep track of the minimum difference and the element to cut
int min_diff = INT_MAX;
element *to_cut = NULL;

// Helper function to find the minimum difference cut recursively
int find_min_cut(element *root, int total_sum) {
    if (root == NULL) return 0;

    int sum_left = find_min_cut(root->left, total_sum);
    int sum_right = find_min_cut(root->right, total_sum);
    int sum_current = root->key + sum_left + sum_right;

    // Check the difference if we cut here
    int diff = abs((total_sum - sum_current) - sum_current);
    if (diff < min_diff) {
        min_diff = diff;
        to_cut = root; // This node would be the parent of the cut edge
    }

    return sum_current;
}

// Function to cut the tree such that the difference of the sums of t1 and t2 is minimal
void tree_cut(element *root) {
    int total_sum = tree_sum(root); // Compute the total sum of the tree
    find_min_cut(root, total_sum);  // Find the minimum cut

    // Printing the result (this could also be returned or handled in another way)
    if (to_cut != NULL) {
        printf("Cut the edge leading to node with key: %d\n", to_cut->key);
        printf("The minimum difference between the two trees will be: %d\n", min_diff);
    } else {
        printf("No cut needed\n");
    }
}
