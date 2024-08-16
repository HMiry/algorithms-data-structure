#include <stdio.h>
#include <stdlib.h>

#define N 5 // Maximum number of children a node can have

typedef struct Node {
    int data;
    struct Node* children[N]; // Array of pointers to children
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    for (int i = 0; i < N; i++) {
        newNode->children[i] = NULL; // Initialize all children to NULL
    }
    return newNode;
}

// Function to insert a new node in the n-ary tree
Node* insert(Node* root, int data) {
    // Base case: Tree is empty
    if (root == NULL) return createNode(data);

    // Look for the first node with an available child slot
    for (int i = 0; i < N; i++) {
        if (root->children[i] == NULL) {
            root->children[i] = createNode(data);
            return root;
        } else {
            // Try inserting in this subtree
            Node* child = insert(root->children[i], data);
            if (child != NULL) return root;
        }
    }
    // If the root node and its subtrees are full, return NULL
    return NULL;
}

// Function for pre-order traversal of the n-ary tree
void preOrderTraversal(Node* root) {
    if (root == NULL) return;

    printf("%d ", root->data); // Visit operation

    for (int i = 0; i < N; i++) {
        preOrderTraversal(root->children[i]); // Visit children
    }
}

int main() {
    Node* root = NULL;

    // Example of inserting nodes
    root = insert(root, 1); // Root node
    insert(root, 2);        // Insert additional nodes
    insert(root, 3);
    insert(root, 4);
    insert(root, 5);
    insert(root, 6);        // This will be inserted into the first available child's subtree

    printf("Pre-order traversal of the n-ary tree: \n");
    preOrderTraversal(root);
    printf("\n");

    return 0;
}
