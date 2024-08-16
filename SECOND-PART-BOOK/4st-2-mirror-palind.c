#include <stdbool.h>
#include <string.h>

bool is_palindrome(const char *str) {
    int left = 0;
    int right = strlen(str) - 1;

    while (left < right) {
        if (str[left] != str[right]) {
            return false;
        }
        left++;
        right--;
    }

    return true;
}
#include <stdio.h>
#include <stdlib.h>

// Assuming the key is stored as a string in the node
struct node {
    char *key;
    struct node *left;
    struct node *right;
};

void mirror(struct node *root) {
    if (root == NULL) {
        return;
    }

    // First, mirror the subtrees
    mirror(root->left);
    mirror(root->right);

    // If the key is a palindrome, swap the left and right subtrees
    if (is_palindrome(root->key)) {
        struct node *temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
}

// ... Other parts of the code, such as constructing the tree, would go here.

int main() {
    // Example usage:
    struct node *root; // Assume the tree is created and root is initialized

    // Call the mirror function
    mirror(root);

    // Continue with the rest of your program...

    return 0;
}
