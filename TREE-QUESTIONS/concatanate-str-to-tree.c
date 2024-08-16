#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
    struct node_s **children; // Array of pointers to children
    int nc;                    // Number of children
    char *str;                // String of the node
} node_t;

// Helper function to concatenate the strings of the children nodes
char *concatenate_children_strings(node_t *node) {
    if (node == NULL || node->nc == 0) {
        return NULL;
    }

    // Calculate total length needed for the concatenated string
    int total_length = 1; // Start with 1 for the null terminator
    for (int i = 0; i < node->nc; ++i) {
        if (node->children[i]->str != NULL) {
            total_length += strlen(node->children[i]->str);
        }
    }

    // Allocate memory for the concatenated string
    char *concatenated = malloc(total_length * sizeof(char));
    if (concatenated == NULL) {
        perror("Failed to allocate memory for concatenated string");
        exit(EXIT_FAILURE);
    }

    // Start concatenation
    concatenated[0] = '\0'; // Initialize to empty string
    for (int i = 0; i < node->nc; ++i) {
        if (node->children[i]->str != NULL) {
            strcat(concatenated, node->children[i]->str);
        }
    }

    return concatenated;
}

// Function to recursively complete the tree
void tree_complete(node_t *root) {
    // Base case: if the current node is NULL, return
    if (root == NULL) {
        return;
    }

    // Recursively complete the tree for all children
    for (int i = 0; i < root->nc; ++i) {
        tree_complete(root->children[i]);
    }

    // If the node is an internal node, concatenate the children's strings
    if (root->nc > 0) {
        root->str = concatenate_children_strings(root);
    }
    // Note: Leaves will already have their 'str' set, so no action needed for leaves
}






// Helper function to sum the values of the children nodes
int sum_children_numbers(node_t *node) {
    if (node == NULL || node->nc == 0) {
        return 0;
    }

    // Calculate total sum of the children's values
    int total_sum = 0;
    for (int i = 0; i < node->nc; ++i) {
        total_sum += node->children[i]->value;
    }

    return total_sum;
}

// Function to recursively complete the tree
void tree_complete(node_t *root) {
    // Base case: if the current node is NULL, return
    if (root == NULL) {
        return;
    }

    // Recursively complete the tree for all children
    for (int i = 0; i < root->n; ++i) {
        tree_complete(root->children[i]);
    }

    // If the node is an internal node, sum the children's values
    if (root->nc > 0) {
        root->value = sum_children_numbers(root);
    }
    // Note: Leaves will already have their 'value' set, so no action needed for leaves
}
