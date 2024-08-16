#include <stdio.h>
#include <stdlib.h>
//seeks the longest path in terms of node count, irrespective of the values.
typedef struct node {
    int value;
    struct node *left, *right;
} node_t;


// Calculate the height of the tree
int height(node_t* node, int* diameter) {
    if (node == NULL) return 0;

    int leftHeight = height(node->left, diameter);
    int rightHeight = height(node->right, diameter);

    // Update the diameter if the path through the current node is larger
    int currentDiameter = leftHeight + rightHeight;
    if (currentDiameter > *diameter) {
        *diameter = currentDiameter;
    }

    // Determine the greater height between leftHeight and rightHeight
    int maxHeight = (leftHeight > rightHeight) ? leftHeight : rightHeight;

    // Return the height of the current node
    return 1 + maxHeight;
}

int tree_diameter(node_t* root) {
    int diameter = 0;
    height(root, &diameter);
    return diameter;
}

