#ifndef _IMPL2_H
#define _IMPL2_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node_t;

void list_insert(node_t **, node_t **, int, int);
void list_write(node_t *, node_t *, int);

#endif

void list_insert(node_t **left, node_t **right, int key, int leftRight) {
    node_t *p;
    p = malloc(1 * sizeof(node_t));
    if (p == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    p->key = key;
    if (leftRight == 0) {// head insertion
        p->right = *left;
        p->left = NULL;
        if (*left != NULL) {
            (*left)->left = p;
        }
        *left = p;
        if (*right == NULL) {
            *right = *left;
        }
    } else {//tail insertion 
        p->left = *right;
        p->right = NULL;
        if (*right != NULL) {
            (*right)->right = p;
        }
        *right = p;
        if (*left == NULL) {
            *left = *right;
        }
    }
}

void list_write(node_t *left, node_t *right, int leftRight) {
    node_t *p;
    if (leftRight == 0) {
        fprintf(stdout, "Left2Right: ");
        p = left;
        while (p != NULL) {
            fprintf(stdout, "%d ", p->key);
            p = p->right;
        }
        fprintf(stdout, "\n");
    } else {
        fprintf(stdout, "Right2Left: ");
        p = right;
        while (p != NULL) {
            fprintf(stdout, "%d ", p->key);
            p = p->left;
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}
//same code with comments 


#ifndef _IMPL2_H
#define _IMPL2_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Node element with left and right pointers
typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node_t;

void list_insert(node_t **, node_t **, int, int);
void list_write(node_t *, node_t *, int);

#endif


// Inserts a new node with the given key to the left or right side of a doubly-linked list.
void list_insert(node_t **head, node_t **tail, int key, int leftRight) {
    node_t *p;  // Declare a pointer to node_t that will point to the new node.

    // Allocate memory for the new node and check if the allocation was successful.
    p = malloc(1 * sizeof(node_t));
    if (p == NULL) {
        // If memory allocation fails, print an error message and exit the program.
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    p->key = key;  // Set the node's key to the provided value.

    // If leftRight is 0, insert the node on the left side.
    if (leftRight == 0) {
        p->right = *head;  // Set the new node's right pointer to the current leftmost node.
        p->left = NULL;  // The new node's left pointer should be NULL, as it will be the new leftmost node.

        // If the list isn't empty, set the current leftmost node's left pointer to the new node.
        if (*head != NULL) {
            (*head)->left = p;
        }
        *head = p;  // Update the leftmost pointer to point to the new node.

        // If the right pointer is NULL, it means the list was empty. Now both left and right should point to the new node.
        if (*tail == NULL) {
            *tail = *head;
        }
    } else {
        // If leftRight is not 0, insert the node on the right side.
        p->left = *tail;  // Set the new node's left pointer to the current rightmost node.
        p->right = NULL;  // The new node's right pointer should be NULL, as it will be the new rightmost node.

        // If the list isn't empty, set the current rightmost node's right pointer to the new node.
        if (*tail != NULL) {
            (*tail)->right = p;
        }
        *tail = p;  // Update the rightmost pointer to point to the new node.

        // If the left pointer is NULL, it means the list was empty. Now both left and right should point to the new node.
        if (*head == NULL) {
            *head = *tail;
        }
    }

    // The function returns no value as it's specified to return void.
}

// Prints the keys of all nodes in the list from left to right or right to left based on the leftRight parameter.
void list_write(node_t *left, node_t *right, int leftRight) {
    node_t *p;  // Declare a pointer to node_t for iteration.

    // If leftRight is 0, print the list from left to right.
    if (leftRight == 0) {
        fprintf(stdout, "Left2Right: ");  // Print a header for clarity.
        p = left;  // Start with the leftmost node.
        // Iterate through the list from left to right.
        while (p != NULL) {
            fprintf(stdout, "%d ", p->key);  // Print the current node's key.
            p = p->right;  // Move to the next node to the right.
        }
        fprintf(stdout, "\n");  // Print a newline after all nodes have been printed.
    } else {
        // If leftRight is not 0, print the list from right to left.
        fprintf(stdout, "Right2Left: ");  // Print a header for clarity.
        p = right;  // Start with the rightmost node.
        // Iterate through the list from right to left.
        while (p != NULL) {
            fprintf(stdout, "%d ", p->key);  // Print the current node's key.
            p = p->left;  // Move to the next node to the left.
        }
        fprintf(stdout, "\n");  // Print a newline after all nodes have been printed.
    }

    // Print an additional newline for formatting purposes.
    fprintf(stdout, "\n");
    // The function returns no value as it's specified to return void.
}




    if (*left==NULL){
    p = *left;
    }
        
        if (*left != NULL) {
            (*left)->left = p;
        }
        *left = p;