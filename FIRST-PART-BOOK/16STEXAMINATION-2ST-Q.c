#ifndef _IMPL2
#define _IMPL2

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX 30+1

typedef struct list1_s list1_t;
typedef struct list2_s list2_t;

struct list1_s {
    char farmer[MAX];
    list2_t *product;
    list1_t *next;
};

struct list2_s {
    char product[MAX];
    list1_t *farmer;
    list2_t *next;
};



#endif

// Function prototypes for the static functions in this file.
static list2_t *search(list2_t *, char *);
static list1_t *list1_push(list1_t *, char *);
static list2_t *list2_push(list2_t *, char *);



// The main function being implemented in this file.
void list_of_list_invert(list1_t *head1, list2_t *head2) {
    list1_t *l1; // Pointer to iterate through the first list of type list1_t.
    list2_t *l2, *new; // Pointers for the second list of type list2_t, 'new' is used for new nodes.

    // Iterate through the first list.
    for (l1=head1; l1!=NULL; l1=l1->next) {
        // For each element in the first list, iterate through the second list.
        for (l2=l1->product; l2!=NULL; l2=l2->next) {
            // Search for a product in the second list.
            new = search(head2, l2->product);
            if (new == NULL) {
                // If the product is not found, insert a new product node into the second list.
                new = list2_push(head2, l2->product);// l2 contatins all products so if we didnt find it we add it the one that we found from farmers
            }
            // Update the head of the second list to the new node.
            head2 = new;

            // Insert a new farmer node into the first list.
            new->farmer = list1_push(new->farmer, l1->farmer);
        }
    }

    return; // End of the function, return to the caller.
}
/*
 * Search a product into main list of head2
 */
static list2_t *search(list2_t **head2, char *product) {
    list2_t *l2;

    for (l2=*head2; l2!=NULL; l2=l2->next) {
        if (strcmp(l2->product, product)==0) {
            return l2;
        }
    }
    return NULL;
}

/*
 * Push new farmer into secondary list of head2
 */
static list1_t *list1_push(list1_t **head, char *farmer) {
    list1_t *node;
    
    node = (list1_t *) malloc(sizeof(list1_t));
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->farmer, farmer);
    node->product = NULL;
    node->next = *head;
    *head = node;
    return node;
}
/*
 * Push new product into main list of head2
 */
static list2_t *list2_push(list2_t **head2, char *product) {
    list2_t *node;

    node = (list2_t *) malloc(sizeof(list2_t));
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(node->product, product);
    node->farmer = NULL;
    node->next = *head2;
    *head2=node;
    return node;
}
