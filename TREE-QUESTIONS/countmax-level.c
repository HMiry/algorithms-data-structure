#include <stdio.h>
#include <stdlib.h>

// Assuming node_t structure similar to what your functions suggest
typedef struct node {
    int val; // Assuming this is the data part
    struct node *left, *right;
} node_t;

// Function prototypes as they seem to be missing
int compare(int a, int b) {
    return (a > b) - (a < b);
}

// New simplified approach to find the level with the maximum number of nodes
void findMaxLevel(node_t *root) {
    int treeHeight = count_depth(root);
    int *levelCounts = calloc(treeHeight + 1, sizeof(int)); // Initialize counts to 0 for all levels

    // Fill in the counts for each level
    countLevel(root, levelCounts, 0); // Start from level 0

    // Find the level with the maximum count
    int maxLevel = 0, maxCount = -1;
    for (int i = 0; i <= treeHeight; i++) {
        if (levelCounts[i] > maxCount) {
            maxCount = levelCounts[i];
            maxLevel = i;
        }
    }

    printf("Level with maximum nodes: %d\n", maxLevel);

    free(levelCounts); // Cleanup
}

// Adjusted countLevel function to increase level depth as it goes deeper
void countLevel(node_t *root, int *level, int h) {
    if (root == NULL) return;

    level[h]++; // Increment count for the current level
    countLevel(root->left, level, h + 1); // Go to the next level down the left
    countLevel(root->right, level, h + 1); // Go to the next level down the right
}

// Assuming height_r function calculates the height correctly
int count_depth(node_t *root) {
    if (root == NULL) {
        return -1;
    }
    int hl = count_depth(root->left);
    int hr = count_depth(root->right);
    return 1+ (hl > hr ? hl : hr);
}

// Main function or usage example would go here
