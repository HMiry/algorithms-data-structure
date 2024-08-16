#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node **children;
    int child_count;
} node_t;

// Function to create a new node
node_t* create_node(int key) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->key = key;
    new_node->child_count = 0;
    new_node->children = NULL;
    return new_node;
}

// Helper function to recursively visit nodes at a given level
static void levelByLevel_visit_r(node_t *root, int level, int target_level) {
    if (root == NULL) {
        return;
    }
    if (level == target_level) {
        printf("%d ", root->key);
        return;
    }
    for (int i = 0; i < root->child_count; ++i) {
        levelByLevel_visit_r(root->children[i], level + 1, target_level);
    }
}

// Function to visit nodes level by level
void levelByLevel_visit(node_t *root, int l1, int l2) {
    for (int i = l1; i <= l2; ++i) {
        printf("Level %d: ", i);
        levelByLevel_visit_r(root, 0, i);
        printf("\n");
    }
}

int main() {
    // Example usage:
    // Construct the tree as per your specific structure
    // ...
    
    // Perform the level by level visit starting from level l1 to l2
    levelByLevel_visit(root, 0, /* maximum level of your tree */);

    // Clean up the memory used by the tree...
    // (Add logic to free the nodes)

    return 0;
}
