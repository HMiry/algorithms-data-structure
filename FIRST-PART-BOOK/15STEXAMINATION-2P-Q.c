#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// this question wants us to see the list of shops and then in each node of the list find the min price of the according tree 
//the tree is consist of product name price.
typedef struct tree_s {
    char *name;           // Product name
    float price;          // Product price
    struct tree_s *left;  // Left subtree
    struct tree_s *right; // Right subtree
} tree_t;

typedef struct list_s {
    char *shop;           // Shop name
    tree_t *products;     // BST of products
    struct list_s *next;  // Next shop in the list
} list_t;

// Helper function to find the product with the minimum and maximum price in the BST
void find_min_max(tree_t *root, tree_t **min, tree_t **max) {
    if (root == NULL) return;
    
    // Traverse left subtree for minimum
    if (*min == NULL || root->price < (*min)->price) {
        *min = root;
    }
    find_min_max(root->left, min, max);
    
    // Traverse right subtree for maximum
    if (*max == NULL || root->price > (*max)->price) {
        *max = root;
    }
    find_min_max(root->right, min, max);
}

// Main function to visit the list and BST
void list_and_tree_visit(list_t *head) {
    list_t *current_shop = head;
    tree_t *min_product, *max_product;

    while (current_shop != NULL) {
        min_product = max_product = NULL;

        // Find the min and max priced products for the current shop
        find_min_max(current_shop->products, &min_product, &max_product);

        // Print the shop name
        printf("Shop: %s\n", current_shop->shop);

        // If min and max products are found, print their details
        if (min_product != NULL && max_product != NULL) {
            printf("Cheapest product: %s at $%.2f\n", min_product->name, min_product->price);
            printf("Most expensive product: %s at $%.2f\n\n", max_product->name, max_product->price);
        }

        // Move to the next shop in the list
        current_shop = current_shop->next;
    }
}
