#include "impl2.h" // Include the header file associated with this implementation.
type def struct node_s{
    int key;
    struct node_s *left;
    struct node_s *right;

}node;
// Function prototype for creating a new node.
static struct node *node_new();

// Function to create a mirror of a binary tree.
struct node *tree_mirror(struct node *root) {
    struct node *node;

    // If the root node is NULL, return NULL indicating the subtree is empty.
    if (root==NULL) {
        return NULL;
    }

    // Create a new node using the node_new function.
    node = (node_t *) malloc(1 * sizeof(node_t));
    // If memory allocation fails, print an error message and exit.
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    // Copy the key from the root to the new node.
    node->key = root->key;
    // Recursively call tree_mirror on the left subtree of the root and
    // assign it to the right child of the new node, mirroring the tree.
    node->right = tree_mirror(root->left);
    // Recursively call tree_mirror on the right subtree of the root and
    // assign it to the left child of the new node, mirroring the tree.
    node->left = tree_mirror(root->right);

    // Return the new node which is the root of the mirrored subtree.
    return (node);
}
// i removed the fun and manually allocated hte memory
// // Function to allocate memory for a new node and initialize it.
// static struct node *node_new() {
//     struct node *node;

//     // Allocate memory for a new node.
//     node = (node_t *) malloc(1 * sizeof(node_t));
//     // If memory allocation fails, print an error message and exit.
//     if (node==NULL) {
//         fprintf(stderr, "Memory allocation error.\n");
//         exit(EXIT_FAILURE);
//     }

//     // Return the pointer to the new node.
//     return node;
// }
// //then for the new node i think it is better to write this 
// static node_t *node_new() {
//     node_t *node = (node_t *)malloc(sizeof(node_t));
//     if (node == NULL) {
//         fprintf(stderr, "Memory allocation error.\n");
//         exit(EXIT_FAILURE);
//     }
//     // Initialize default values if necessary. For example:
//     node->key = 0; // Default key value, if you need one.
//     node->left = NULL; // Initially, the node does not have any children.
//     node->right = NULL;
//     return node;
// }
