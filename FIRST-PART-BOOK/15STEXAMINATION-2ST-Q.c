// #include "impl2.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct bst_t {
    char *model;         // The car model
    struct bst_t *left;  // Pointer to the left subtree
    struct bst_t *right; // Pointer to the right subtree
    struct list1_t *next;  // Pointer to the list of dealers for this model
} bst_t;

typedef struct list1_t {
    char *dealer;         // The dealer name
    float price;          // The price at which the dealer sells the car model
    struct list1_t *next; // Pointer to the next dealer in the list
} list1_t;

typedef struct list2_t {// which we are going to save in it 
    char *model;          // The car model
    char *dealer;         // The dealer with the minimum price
    float price;          // The minimum price offered for the car model
    struct list2_t *next; // Pointer to the next node in the new list
} list2_t;



static void visit_ver2(bst_t *, list1_t *, list2_t **);
static void queue_put(bst_t *, list1_t *, list2_t **);
static void stack_push(bst_t *, list1_t *, list2_t **);

/* Version 1 */
void bst2list_ver1(bst_t *root, list2_t **l2) {
    if (root == NULL) // Base case for recursion: if the node is null, do nothing.
        return;

    // In-order visit
    bst2list_ver1(root->left, l2);  // Visit the left subtree.
    visit_ver1(root, root->next, l2); // Visit the current node.
    bst2list_ver1(root->right, l2); // Visit the right subtree.

    return;
}


/* From list1_t to a LIFO stack list2_t */
static void visit_ver2(bst_t *bst, list1_t *l1, list2_t **l2) {
    list1_t *p, *min;

    // Initialize the minimum element pointer to NULL
    min = NULL;
    // Iterate through the list l1 to find the minimum priced product
    for (p=l1; p!=NULL; p=p->next) {
        // If it is the first element or found a smaller priced product, update min
        if (min==NULL || p->price<min->price) {
            min = p;
        }
    }
    // Insert the minimum priced product into the stack represented by l2
    stack_push(bst, min, l2);
    return;
}

/* FIFO queue insertion */
static void queue_put(bst_t *bst, list1_t *l1, list2_t **l2) {
    list2_t *node;
    
    // Allocate memory for a new node of type list2_t
    node = (list2_t *) malloc(sizeof(list2_t));
    // If the memory allocation fails, print an error and exit the program
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // Set the model of the new node to the model of the bst node
    node->model = bst->model;
    // Set the dealer of the new node to the dealer of the list1_t node
    node->dealer = l1->dealer;
    // Set the price of the new node to the price of the list1_t node
    node->price = l1->price;
    // If the list l2 is empty, simply point l2 to the new node
    if (*l2 == NULL) {
        node->next = node;// I THINK I SHOULD HAVE BEEN L2 INSTEAD OF NODE LILE node->next=*l2
    } else {
        // If l2 is not empty, insert the new node at the end of the queue
        node->next = (*l2)->next;
        (*l2)->next = node;
    }
    // Update the head of the queue to the new node
    *l2 = node;
    
    return;
}

/* LIFO queue insertion */
static void stack_push(bst_t *bst, list1_t *l1, list2_t **l2) {
    list2_t *node;
    
    // Allocate memory for a new list2_t node
    node = (list2_t *) malloc(sizeof(list2_t));
    // If memory allocation fails, print an error message and exit the program
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    // Copy the model from the bst to the new node
    node->model = bst->model;
    // Copy the dealer from list1_t to the new node
    node->dealer = l1->dealer;
    // Copy the price from list1_t to the new node
    node->price = l1->price;
    // Set the next pointer of the new node to the current head of the stack
    node->next = *l2;
    // Update the head of the stack to be the new node
    *l2 = node;
    // Function returns nothing as it's a void function
    return;
}




// this is for the case of list to tree 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h> // For FLT_MAX

// Assuming the tree_t structure as described in your image
typedef struct tree_t {
    char *name;            // Name of the product
    float price;           // Price of the product
    struct tree_t *left;   // Pointer to left subtree
    struct tree_t *right;  // Pointer to right subtree
} tree_t;

// Assuming the list_t structure as described in your image
typedef struct list_t {
    char *shop_name;       // Name of the shop
    tree_t *products;      // Pointer to a tree of products
    struct list_t *next;   // Pointer to the next shop in the list
} list_t;

// Helper function to find the product with smallest and largest price in the tree
void find_min_max(tree_t *node, float *min_price, char **min_product, float *max_price, char **max_product) {
    if (node == NULL) return;

    // Check current node
    if (node->price < *min_price) {
        *min_price = node->price;
        *min_product = node->name;
    }
    if (node->price > *max_price) {
        *max_price = node->price;
        *max_product = node->name;
    }

    // Recursively check left and right subtrees
    find_min_max(node->left, min_price, min_product, max_price, max_product);
    find_min_max(node->right, min_price, min_product, max_price, max_product);
}

// Function to visit list and tree
void list_and_tree_visit(list_t *head) {
    list_t *current_shop = head;
    while (current_shop != NULL) {
        float min_price = FLT_MAX;
        char *min_product = NULL;
        float max_price = -FLT_MAX;
        char *max_product = NULL;

        // Find the min and max price products for the current shop
        find_min_max(current_shop->products, &min_price, &min_product, &max_price, &max_product);

        // Print details for the current shop
        printf("Shop: %s\n", current_shop->shop_name);
        printf("Cheapest product: %s at %.2f\n", min_product, min_price);
        printf("Most expensive product: %s at %.2f\n\n", max_product, max_price);

        // Move to the next shop in the list
        current_shop = current_shop->next;
    }
}

// You would need to fill in the rest of the program with code to create and populate
// your list and tree structures before calling list_and_tree_visit with the head of your list.

// Example of creating and adding data to the structures would be required here
