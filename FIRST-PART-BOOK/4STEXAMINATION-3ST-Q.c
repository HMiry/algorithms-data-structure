#ifndef _IMPL3_H
#define _IMPL3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 512
#define N 10

/* structure declaration */
typedef struct node {
    char *fn;             // First name
    char *ln;             // Last name
    int em;               // Examination mark
    struct node *child;
    struct node *sibling;
} node_t;

void visit_tree_r(node_t *);

#endif




void visit_tree_r(node_t *root) {
    if (root == NULL) {
        return;
    }

    fprintf(stdout, "%s %s %d\n", root->fn, root->ln, root->em);
    visit_tree_r(root->child);
    visit_tree_r(root->sibling);

    return;
}




// if we want to visit it in the in order way the code below we use this is not wanted from the question it is written in general for lovers of C :)
void visit_tree_in_order(node_t *root) {
    if (root == NULL) {
        return;
    }

    // 1. Recursively visit the first child subtree (as if it's the "left" subtree).
    if (root->child != NULL) {
        visit_tree_in_order(root->child);
    }

    // 2. Visit the current node.
    fprintf(stdout, "%s %s %d\n", root->fn, root->ln, root->em);

    // 3. Recursively visit the siblings of the first child subtree (as if they are the "right" subtree).
    node_t *sibling = root->child ? root->child->sibling : NULL;
    while (sibling != NULL) {
        visit_tree_in_order(sibling);
        sibling = sibling->sibling;
    }
}

