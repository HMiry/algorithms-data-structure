#ifndef _IMPL2_H
#define _IMPL2_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define EMPTY 0
#define FULL 1

#define NS 4
#define NB 5

typedef struct list_s {
    int val;
    struct list_s *next;
} list_t;

#endif


// #include "impl2.h"
static list_t *enqueue(list_t *, list_t *);

void split(
    list_t **head, int threshold, list_t **head1, list_t **head2
) {
    list_t *p, *tmp, *pTail1, *pTail2;

    pTail1 = NULL;
    pTail2 = NULL;
    p = *head;
    while (p != NULL) {
        // Pop
        tmp = p;
        p = p->next;
        // Enqueue
        if (tmp->val < threshold) {
            pTail1 = enqueue(pTail1, tmp);
        } else {
            pTail2 = enqueue(pTail2, tmp);
        }
    }

    *head = NULL;

    // From circular to linear lists
    if (pTail1->next != NULL) {
        *head1 = pTail1->next;
        pTail1->next = NULL;
    }
    if (pTail2->next != NULL) {
        *head2 = pTail2->next;
        pTail2->next = NULL;
    }

    return;
}

// Circular List Implementation
list_t *enqueue(list_t *pTail, list_t *p) {
    if (pTail == NULL) {
        pTail = p;
        pTail->next=p;
    } else {
        p->next = pTail->next;
        pTail->next = p;
        pTail = p;
    }

    return (pTail);
}
//or 
list_t *enqueue(list_t *pTail, list_t *p) {
    if (pTail == NULL) {
        p->next = p; // Make the list circular by pointing the node to itself
    } else {
        p->next = pTail->next;
        pTail->next = p;
    }
    return p; // Return the new tail
}





//commented version

// Prevent duplicate inclusion of this header file
#ifndef _IMPL2_H
#define _IMPL2_H

// Include standard input/output library for file and console I/O
#include <stdio.h>
// Include string library for string handling functions
#include <string.h>
// Include standard library for general purposes like dynamic memory allocation
#include <stdlib.h>

// Define macro constants for readability
#define SIZE 10
#define EMPTY 0
#define FULL 1
#define NS 4
#define NB 5

// Define a structure for a list node
typedef struct list_s {
    int val;             // Value of the node
    struct list_s *next; // Pointer to the next node in the list
} list_t;

// End of the macro guard
#endif


// Function prototype declaration for enqueue
static list_t *enqueue(list_t *, list_t *);

// Function to split a linked list based on a threshold value
void split(
    list_t **head,     // Pointer to the head pointer of the list to split
    int threshold,     // The threshold value to split the list
    list_t **head1,    // Pointer to the head pointer of the first resulting list
    list_t **head2     // Pointer to the head pointer of the second resulting list
) {
    list_t *p, *tmp, *pTail1, *pTail2;

    // Initialize the tail pointers for the new lists as NULL
    pTail1 = NULL;
    pTail2 = NULL;
    // Start from the head of the original list
    p = *head;
    // Iterate over the original list
    while (p != NULL) {
        // Pop the current node from the original list
        tmp = p;
        p = p->next;
        // Enqueue the current node to the appropriate list based on its value
        if (tmp->val < threshold) {
            // If value is less than threshold, add to the first list
            pTail1 = enqueue(&pTail1, tmp);
        } else {
            // If value is not less than threshold, add to the second list
            pTail2 = enqueue(&pTail2, tmp);
        }
    }

    // Set the original list's head to NULL as it is now empty
    *head = NULL;

    // Convert the circular lists to linear lists by setting the tail's next to NULL
    if (pTail1 != NULL && pTail1->next != NULL) {
        *head1 = pTail1->next;
        pTail1->next = NULL;
    }
    if (pTail2 != NULL && pTail2->next != NULL) {
        *head2 = pTail2->next;
        pTail2->next = NULL;
    }

    // End of the split function
    return;
}

// Function to enqueue (add) a node to a circular linked list
list_t *enqueue(list_t *pTail, list_t *p) {
    // If the list is empty, initialize it with the new node
    if (pTail == NULL) {
        pTail = p;
    } else {
        // Link the new node into the circular list
        p->next = pTail->next;
        pTail->next = p;
    }
    // Move the tail pointer to the new node
    pTail = p;

    // Return the new tail of the list
    return (pTail);
}
