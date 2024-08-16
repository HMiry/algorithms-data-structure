// Check if _IMPL2 is not defined to avoid multiple inclusion issues.
#ifndef _IMPL2
#define _IMPL2

// Include standard libraries for memory allocation and input/output functions.
#include <stdlib.h>
#include <stdio.h>

// Define a new struct for a node in a binary tree.
typedef struct node_s {
    struct node_s *lc, *rs, *p; // Pointers to left child (lc) and right sibling (rs), parent
    int nc;                 // Integer to store the number of children.
    char key;               // Character to store the node's key.
    node_t;                 // Typedef to simplify the struct declaration.
} node_t;

// Prototype for the function tree_complete.
int tree_complete(node_t *, node_t *);

#endif /* _IMPL2 */

// The implementation file for the binary tree functions.

// Include the header file where the struct and function prototype are declared.
#include "impl2.h"

// Function to mark the completion of a node in a binary tree.
// It returns an integer value.
int tree_complete(node_t *node, node_t *parent) {
    // If the current node is NULL, return 0.
    if (node == NULL) {
        return 0;
    }

    // Set the current node's parent pointer to the passed-in parent node.
    node->p = parent;
    // Recursively call tree_complete for the left child of the current node.
    node->nc = tree_complete(node->lc, node);
    
    // Return 1 plus the recursive call to tree_complete for the right sibling of the current node.
    return (1 + tree_complete(node->rs, parent));
}
