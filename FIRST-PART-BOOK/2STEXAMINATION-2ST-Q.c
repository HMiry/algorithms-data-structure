#ifndef _IMPL2
#define _IMPL2

#include <stdlib.h>
#include <stdio.h>

typedef struct node_s {
    int col;
    float f;
    struct node_s *next;
} node_t;

typedef struct list_s {
    int ne;
    node_t *next;
} list_t;

typedef struct matr_s {
    int nr;
    int nc;
    list_t *rows;
} matr_t;

#endif

// #include "impl2.h"

static node_t *node_new(float, int, node_t *);

void mat_insert(matr_t *mat, int r, int c, float value) {
    node_t *n, *prev;
    int overwrite = 0;

    // Boundary check: If the specified position is outside the bounds of the matrix, do nothing.
    if (r >= mat->nr || c >= mat->nc) {
        return;
    }

    // If the row is currently empty (no elements), insert the first element.
    if (mat->rows[r].ne == 0) {
        mat->rows[r].next = node_new(value, c, NULL);
    } else {
        // If the row already has elements, find the correct position to insert the new element.
        prev = NULL;
        n = mat->rows[r].next;
        while (n != NULL && n->col < c) {
            prev  = n;
            n = n->next;
        }

        if (n != NULL) {
            // In the middle of the list...
            if (n->col == c) {//it means we have found the right index col
                // Overwrite
                n->f = value; //we assign the value 
                overwrite = 1;
            } else {
                // New node in the middle...
                if (prev != NULL) {//we should add new node 
                    prev->next = node_new(value, c, n);
                } else {
                    mat->rows[r].next = node_new(value, c, n);
                }
            }
        } else {
            // Bottom of the list
            prev->next = node_new(value, c, NULL);
        }
    }

    // If a new element was inserted, increment the counter for non-zero elements in the row.
    if (!overwrite) {
        mat->rows[r].ne++;
    }

    return;
}

static node_t *node_new(float value, int col, node_t *next) {
    node_t *n = malloc(sizeof(node_t));
    if (n == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    n->col = col;
    n->f = value;
    n->next = next;

    return n;
}







// This is the function signature of mat_insert. It takes a pointer to a matr_t structure, which represents a matrix,
// and the row (r), column (c), and value (value) to be inserted into the matrix.
void mat_insert(matr_t *mat, int r, int c, float value) {

    // n will point to the current node in the list as we iterate through it.
    // prev will keep track of the node just before n, so we can insert new nodes in the list if needed.
    node_t *n, *prev;
    // This flag indicates whether we overwrite an existing node's value.
    int overwrite = 0;
    // Check if the indices r and c are within the bounds of the matrix.
    // If not, exit the function as we can't insert a value outside the matrix dimensions.
    if (r >= mat->nr || c >= mat->nc) {
        return;
    }
    // Check if the row we want to insert into currently has no elements (is empty).
    if (mat->rows[r].ne == 0) {
        // Since the row is empty, we simply create a new node with node_new and set it as the first node in the row.
        mat->rows[r].next = node_new(value, c, NULL);
    } else {
        // If the row already has elements, we start with prev as NULL (since we are at the head of the list)
        // and n as the first node in the list.
        prev = NULL;
        n = mat->rows[r].next;
        // We iterate through the list until we find the correct position to insert our new node.
        // This is done by checking if the current node's column index is less than the one we want to insert.
        while (n != NULL && n->col < c) {
            prev = n;
            n = n->next;
        }
        // After finding the position, we check if we are not at the end of the list (n != NULL).
        if (n != NULL) {
            // If the current node's column index is the same as the one we want to insert,
            // we just overwrite the current node's value.
            if (n->col == c) {
                n->f = value;
                overwrite = 1;
            } else {
                // If we're inserting a new node, we check if we are not at the beginning of the list (prev != NULL).
                // If we are not, we insert the new node between prev and n.
                if (prev != NULL) {
                    prev->next = node_new(value, c, n);
                } else {
                    // If we are at the beginning of the list (prev is NULL), we insert the new node before the first node.
                    mat->rows[r].next = node_new(value, c, n);
                }
            }
        } else {
            // If we reached the end of the list (n == NULL), we simply insert the new node at the end of the list.
            prev->next = node_new(value, c, NULL);
        }
    }
    // If we inserted a new node (didn't overwrite an existing one), we increment the number of elements in the row.
    if (!overwrite) {
        mat->rows[r].ne++;
    }
    // Finally, we return from the function.
    return;
}
// The node_new function is a helper function to create a new node.
// It allocates memory for a new node, sets its values, and returns a pointer to the new node.
static node_t *node_new(float value, int col, node_t *next) {
    node_t *n = malloc(sizeof(node_t));
    if (n == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    n->col = col;
    n->f = value;
    n->next = next;

    return n;
}
