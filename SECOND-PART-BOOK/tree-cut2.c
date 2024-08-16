#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
    int key;
    struct node *left;
    struct node *right;
};

// Helper function to calculate the total sum of the tree
int calculate_total_sum(struct node *root) {
    if (root == NULL) return 0;
    return root->key + calculate_total_sum(root->left) + calculate_total_sum(root->right);
}

// Recursive function to find the edge to cut
int find_edge_to_cut(struct node *root, int total_sum, int *min_diff, struct node **edge_to_cut) {
    if (root == NULL) return 0;

    int sum_left = find_edge_to_cut(root->left, total_sum, min_diff, edge_to_cut);
    int sum_right = find_edge_to_cut(root->right, total_sum, min_diff, edge_to_cut);
    int subtree_sum = root->key + sum_left + sum_right;

    int diff = abs(total_sum - 2 * subtree_sum);
    if (diff < *min_diff) {
        *min_diff = diff;
        *edge_to_cut = root;
    }

    return subtree_sum;
}

// Main function to be called to find the edge to cut
void tree_cut(struct node *root) {
    int total_sum = calculate_total_sum(root);
    int min_diff = INT_MAX;
    struct node *edge_to_cut = NULL;

    find_edge_to_cut(root, total_sum, &min_diff, &edge_to_cut);

    printf("Cut the edge at node with key %d to get the minimum difference %d\n", 
           edge_to_cut->key, min_diff);
}

// Definition of the struct element as mentioned in the question
typedef struct node element;

int main() {
    // Construct the tree as per the example in the question
    element *root = malloc(sizeof(element));
    // ... (Other nodes are constructed and connected here)
    // For brevity, let's assume the tree is constructed and root is properly initialized

    // Call the tree_cut function
    tree_cut(root);

    // Remember to free the memory allocated for the tree
    // ... (Code to free the tree)

    return 0;
}
