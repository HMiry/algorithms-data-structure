
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    int num_children;
    struct node **children;
} node_t;

// Recursive helper function to find the level with the maximum number of nodes
int find_level_with_max_nodes(node_t *root, int level, int* max_node_count, int* level_with_max_nodes) {
    if (root == NULL) return 0;

    // Initialize the number of nodes at the current level to include the current node
    int node_rep_curr = 1; // Start counting with the current node
    
    // Recursively visit children to count the number of nodes at this level
    for (int i = 0; i < root->num_children; ++i) {
        node_rep_curr += find_level_with_max_nodes(root->children[i], level + 1, max_node_count, level_with_max_nodes);
    }

    // Update the maximum node count and the corresponding level if this level has more nodes
    if (node_rep_curr > *max_node_count) {
        *max_node_count = node_rep_curr;
        *level_with_max_nodes = level;
    }

    return node_rep_curr; // Return the count of nodes in the subtree rooted at this node
}

void print_level_with_max_nodes(node_t *root) {
    int max_node_count = 0;
    int level_with_max_nodes = 0;

    find_level_with_max_nodes(root, 0, &max_node_count, &level_with_max_nodes);

    printf("Level with the maximum number of nodes: %d (Node count: %d)\n", level_with_max_nodes, max_node_count);
}
