//     Implementation 1: Uses a linked list for elements within each row, but rows are stored in an array.
//     Implementation 2: Uses a linked list for both the rows themselves and the elements within each row.

// This structural difference affects how the insertions are handled in each implementation. In the first
// , you access a row directly from an array and then traverse its linked list of elements. In the second, 
// you traverse a linked list of rows, and for each row, traverse its linked list of elements.



#ifndef _IMPL2
#define _IMPL2

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Element Type
struct node_t {
    int col;
    float val;
    struct node_t *next;
};

// Row Type
struct list_t {
    int r; //change to ne
    struct node_t *ep;
    struct list_t *next;
};

// Matrix (wrapper) Type
struct mat {
    int mr;
    int mc;
    struct list_t *rows;
};

#endif


// static void visitRow(struct rt *, float, int, struct rt *);
// static struct rt *create(float, int, struct rt *);

void mat_insert (struct mat *mat, int r, int c, float value) {
    struct list_t *rpl;
    rpl = mat->rows;

    // Corner case: The matrix is empty
    // OR a new row must be inserted before the first one
    if (rpl==NULL || r<rpl->r) {
        mat->rows = create(value, r, c, rpl);
        return;
    }

    // Corner case: The correct row is the first one
    // Visit it
    if (rpl->next == r) {
        visitRow(rpl, value, c);
        return;
    }

    // Look-for the right row using two pointers
    while (rpl->next!=NULL && rpl->next->r <r) {
        rpl = rpl->next;
    }

    // If the current row *rpl->rp is empty ... create a new row
    if (rpl->next == NULL) {
        rpl->next = create(value, r, c, rpl->next);
        return;
    }

    // Otherwise ...
    if (rpl->next->r == r) {
        // If *rpl->rp is the correct row, visit it
        visitRow(rpl->next, value, c);
    } else {
        // If *rpl->rp goes after, insert a new row
        rpl->next = create(value, r, c, rpl->next);
    }

    return;
}
/*
 * Create a new matrix row with a single element
 */
static struct list_t *create (
    float value, int r, int c, struct list_t *rp
) {
    struct list_t *rp;
    struct node_t *ep;

    rp = (struct list_t *) malloc(sizeof(struct list_t));
    ep = (struct node_t *) malloc(sizeof(struct node_t));
    if (rp==NULL || ep==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    rp->r = r;
    rp->next = rp;
    rp->ep = ep;
    ep->col = c;
    ep->val = value;
    ep->next = NULL;

    return (rp);
}
/*
 * Visit a horizontal list (a matrix row)
 */
static void visitRow(struct list_t *rp, float value, int c) {
    struct node_t *ep1, *ep2;

    ep1 = rp->ep;
    if (ep1==NULL || c < ep1->col) {
        ep2 = (struct node_t *) malloc(sizeof(struct node_t));
        if (ep2==NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        ep2->col = c;
        ep2->val = value;
        ep2->next = rp->ep;
        rp->ep = ep2;
        return;
    }

    if (ep1->col == c) {
        ep1->val = value;
        return;
    }

    while (ep1->next!=NULL && ep1->next->col<c) {
        ep1 = ep1->next;
    }

    if (ep1->next == NULL) {
        ep2 = (struct node_t *) malloc(sizeof(struct node_t));
        if (ep2==NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        ep2->col = c;
        ep2->val = value;
        ep2->next = NULL;
        ep1->next = ep2;
    } else if (ep1->next->col > c) {//or else alone 
        ep2 = (struct node_t *) malloc(sizeof(struct node_t));
        if (ep2==NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        ep2->col = c;
        ep2->val = value;
        ep2->next = ep1->next;
        ep1->next = ep2;
    
    // } else {
    //     ep1->ep->val = value;
    }
    return;
}

//commented version 




#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Element Type
struct node_t {
    int col;              // Column index of the element
    float val;            // Value of the element
    struct node_t *next;  // Pointer to the next node (element) in the same row
};

// Row Type
struct list_t {
    int r;                // Row index
    struct node_t *ep;    // Pointer to the first node (element) in this row
    struct list_t *next;  // Pointer to the next row in the matrix
};

// Matrix (wrapper) Type
struct mat {
    int mr;               // Total number of rows in the matrix
    int mc;               // Total number of columns in the matrix
    struct list_t *rows;  // Pointer to the first row in the matrix
};





// Function to insert a value into the matrix at a specified row and column
void mat_insert(struct mat *m, int r, int c, float value) {
    struct list_t *rpl;   // Pointer to traverse the rows
    rpl = m->rows;        // Start from the first row

    // Check if the matrix is empty or if the new row should be inserted before the first row
    if (rpl == NULL || r < rpl->r) {
        m->rows = create(value, r, c, rpl); // Create a new row at the beginning
        return;
    }

    // Check if the target row is the first row like if we have that first row up there we didnt have first row
    if (rpl->next == r) {
        visitRow(rpl, value, c); // Insert the value in the first row
        return;
    }

    // Traverse the linked list of rows to find the correct position for the new row
    while (rpl->next != NULL && rpl->next->r < r) {
        rpl = rpl->next; // Move to the next row
    }

    // Check if we have reached the end of the list or need to insert a new row
    if (rpl->next == NULL) {
        rpl->next = create(value, r, c, rpl->next); // Create a new row at the end
        return;
    }

    // Insert in the existing row or create a new row in the middle
    if (rpl->next->r == r) {
        visitRow(rpl->next, value, c); // Insert the value in the existing row
    } else {
        rpl->next = create(value, r, c, rpl->next); // Create a new row in the middle
    }

    return;
}

// Function to create a new row in the matrix
static struct list_t *create(float value, int r, int c, struct list_t *rp) {
    struct list_t *newRow; // Pointer for the new row
    struct node_t *newElement; // Pointer for the new element

    // Allocate memory for the new row and the new element
    newRow = (struct list_t *)malloc(sizeof(struct list_t));
    newElement = (struct node_t *)malloc(sizeof(struct node_t));
    if (newRow == NULL || newElement == NULL) {
        fprintf(stderr, "Memory allocation error.\n"); // Error handling for memory allocation
        exit(EXIT_FAILURE);
    }

    // Initialize the new row and the new element
    newRow->r = r;
    newRow->next = rp;
    newRow->ep = newElement;
    newElement->col = c;
    newElement->val = value;
    newElement->next = NULL;

    return newRow; // Return the new row
}

// Function to insert a value in a specific row
static void visitRow(struct list_t *rp, float value, int c) {
    struct node_t *current, *newNode;

    current = rp->ep; // Start from the first element in the row

    // Check if the row is empty or if the new element should be inserted at the beginning
    if (current == NULL || c < current->col) {
        newNode = (struct node_t *)malloc(sizeof(struct node_t)); // Allocate memory for the new element
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation error.\n"); // Error handling for memory allocation
            exit(EXIT_FAILURE);
        }
        // Initialize the new element and insert it at the beginning
        newNode->col = c;
        newNode->val = value;
        newNode->next = rp->ep;
        rp->ep = newNode;
        return;
    }

    // Check if the new element should replace an existing element
    if (current->col == c) {
        current->val = value; // Update the value of the existing element
        return;
    }

    // Traverse the linked list of elements to find the correct position
    while (current->next != NULL && current->next->col < c) {
        current = current->next; // Move to the next element
    }

    // Insert the new element at the correct position
    newNode = (struct node_t *)malloc(sizeof(struct node_t)); // Allocate memory for the new element
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error.\n"); // Error handling for memory allocation
        exit(EXIT_FAILURE);
    }
    // Initialize the new element
    newNode->col = c;
    newNode->val = value;

    // Insert the new element in the middle or at the end
    if (current->next == NULL) {
        newNode->next = NULL; // Insert at the end
    } else if (current->next->col > c) {
        newNode->next = current->next; // Insert in the middle
    }
    current->next = newNode;

    return;
}
