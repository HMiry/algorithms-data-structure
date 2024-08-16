#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Definition of the binary tree node
typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node_t;

int tree_isomorphism (node_t *t1, node_t *t2) {
    if (t1==NULL && t2==NULL){
        return (1);
    }
    if (t1==NULL && t2!=NULL){
        return (0);
    }
    if (t1!=NULL && t2==NULL){
        return (0);
    }
    if (t1->key!=t2->key){
        return (0);
    }
    if (tree_isomorphism(t1->left, t2->left) == 0) {
        return (0);
    }
    if (tree_isomorphism(t1->right, t2->right) == 0) {
        return (0);
    }
    return (1);
}


// Function to check if tree2 is a subtree of tree1
int subtree(node_t *tree1, node_t *tree2) {
    // If tree2 is NULL, it is a subtree of tree1
    if (tree2 == NULL) return 1;

    // If tree1 is NULL, then tree2 can't be a subtree of it
    if (tree1 == NULL) return 0;

    // If the trees are identical at this node, return true
    if (tree_isomorphism(tree1, tree2)) return 1;

    // Otherwise, check if tree2 is a subtree of the left or right subtree of tree1
    return subtree(tree1->left, tree2) || subtree(tree1->right, tree2);
}
