// to find the longest path which values are also increasing 
#include <stdio.h>
#include <stdlib.h>

// Define the structure for the tree node
typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

// Function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Recursive helper function to find the longest strictly increasing path
void longestPathHelper(node *root, int lastVal, int len, int *maxLen) {
    if (root == NULL) {
        *maxLen = max(*maxLen, len);
        return;
    }
    
    if (root->key > lastVal) {//which we assign last val a small value so always true 
        longestPathHelper(root->left, root->key, len + 1, maxLen);
        longestPathHelper(root->right, root->key, len + 1, maxLen);
    } else {
        // If the current node is not greater than the last value, reset the sequence length
        longestPathHelper(root->left, root->key, 1, maxLen);
        longestPathHelper(root->right, root->key, 1, maxLen);
    }
}

// Function to start the recursive process and print the result
void longestPath(node *root) {
    int maxLen = 0;
    longestPathHelper(root, INT_MIN, 0, &maxLen);
    printf("Length of the longest path: %d", maxLen);
}

// Example usage (Not part of the required function)
// int main() {
//     node *root = ... // Build the tree as per the given structure
//     longestPath(root);
//     return 0;
// }
