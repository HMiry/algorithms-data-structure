

#include <stdio.h>
#include <stdlib.h>





typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createTreeNode(int data) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

TreeNode* insertBST(TreeNode* root, int data) {
    // If the root is NULL, create a new node and return it
    if (root == NULL) {
        return createTreeNode(data);
    }

    // If the data to be inserted is less than the root's data, insert it in the left subtree
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    }
    // If the data to be inserted is greater than the root's data, insert it in the right subtree
    else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    // If the data is equal to the root's data, we don't insert duplicates

    return root;
}

TreeNode* searchBST(TreeNode* root, int data) {
    // If the root is NULL or the root's data matches the search data
    if (root == NULL || root->data == data) {
        return root;
    }

    // If the data to be searched is less than the root's data, search in the left subtree
    if (data < root->data) {
        return searchBST(root->left, data);
    }
    // If the data to be searched is greater than the root's data, search in the right subtree
    return searchBST(root->right, data);
}