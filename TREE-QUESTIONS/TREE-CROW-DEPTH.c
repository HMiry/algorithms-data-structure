#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node **children;
    int child_count;
} node_t;


int count_depth(node_t *root) {
    if (root == NULL) {
        return -1; // Base case: if the tree is empty, its depth is -1
    }
    int max_depth = -1; // Initialize max depth among children as -1
    for (int i = 0; i < root->child_count; i++) {
        int child_depth = count_depth(root->children[i]);
        if (child_depth > max_depth) {
            max_depth = child_depth;
        }
    }
    return 1 + max_depth;
}

// Helper function to count nodes at each depth
void count_nodes_at_depth(node_t *root, int depth, int *counts, int *max_count, int *crowded_depth) {
    if (root == NULL) {
        return;
    }
    // Increment the count for this depth
    counts[depth]++;
    // Check if this depth is now the most crowded
    if (counts[depth] > *max_count) {
        *max_count = counts[depth];
        *crowded_depth = depth;
    }
    // Recur for each child
    for (int i = 0; i < root->child_count; ++i) {
        count_nodes_at_depth(root->children[i], depth + 1, counts, max_count, crowded_depth);
    }
}

// Helper function to print keys at a specific depth
void print_keys_at_depth(node_t *root, int depth, int target_depth) {
    if (root == NULL) {
        return;
    }
    if (depth == target_depth) {
        printf("%d ", root->key);
    } else {
        for (int i = 0; i < root->child_count; ++i) {
            print_keys_at_depth(root->children[i], depth + 1, target_depth);
        }
    }
}

// Function to display the crowded depth and print keys at that depth
int display_crowded_depth(node_t *root) {
    int depth = 0;
    int max_depth = count_depth(root); // Assuming a max depth of 10 for simplicity
    int counts[max_depth];
    int max_count = 0;
    int crowded_depth = 0;

    // Initialize counts array
    for (int i = 0; i < max_depth; ++i) {
        counts[i] = 0;
    }

    // Find out the number of nodes at each depth
    count_nodes_at_depth(root, depth, counts, &max_count, &crowded_depth);

    // Print keys at the crowded depth
    printf("Crowded depth is %d with %d nodes: ", crowded_depth, max_count);
    print_keys_at_depth(root, depth, crowded_depth);
    printf("\n");

    return crowded_depth;
}





// binary tree 






#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 1000  // Define a maximum depth if you know the limit, otherwise you would need to use dynamic memory allocation

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node_t;

// Helper function to count the number of nodes at each depth
void count_nodes_at_depth(node_t *root, int depth, int depth_counts[], int *max_count_depth) {
    if (root == NULL) {
        return;
    }
    
    // Increment the count of nodes at the current depth
    depth_counts[depth]++;
    
    // Update the depth which has the max count of nodes
    if (depth_counts[depth] > depth_counts[*max_count_depth]) {
        *max_count_depth = depth;
    }
    
    // Recursively count nodes in the left and right subtrees
    count_nodes_at_depth(root->left, depth + 1, depth_counts, max_count_depth);
    count_nodes_at_depth(root->right, depth + 1, depth_counts, max_count_depth);
}



// Function to find the depth with the maximum number of nodes and print all nodes at that depth
int display_crowded_depth(node_t *root) {
    int depth_counts[MAX_DEPTH] = {0};  // Array to keep track of node counts at each depth
    int max_count_depth = 0;  // Depth with the maximum number of nodes

    count_nodes_at_depth(root, 0, depth_counts, &max_count_depth);

    printf("Depth with the maximum number of nodes is: %d\n", max_count_depth);


    return max_count_depth;
}





//nth array 



#include <stdio.h>
#include <stdlib.h>

#define MAX_DEPTH 1000  // Define a maximum depth if you know the limit, otherwise you would need to use dynamic memory allocation

typedef struct node {
    int key;
    int child_count;      // Number of children
    struct node **children; // Pointer to an array of pointers to children
} node_t;

// Helper function to count the number of nodes at each depth for an n-ary tree
void count_nodes_at_depth(node_t *root, int depth, int depth_counts[], int *max_count_depth) {
    if (root == NULL) {
        return;
    }

    // Increment the count of nodes at the current depth
    depth_counts[depth]++;

    // Update the depth which has the max count of nodes
    if (depth_counts[depth] > depth_counts[*max_count_depth]) {
        *max_count_depth = depth;
    }

    // Recursively count nodes for each child
    for (int i = 0; i < root->child_count; ++i) {
        count_nodes_at_depth(root->children[i], depth + 1, depth_counts, max_count_depth);
    }
}

// Function to find the depth with the maximum number of nodes for an n-ary tree
int display_crowded_depth(node_t *root) {
    int depth_counts[MAX_DEPTH] = {0};  // Array to keep track of node counts at each depth
    int max_count_depth = 0;  // Depth with the maximum number of nodes

    count_nodes_at_depth(root, 0, depth_counts, &max_count_depth);

    // Print the depth with the maximum number of nodes
    printf("Depth with the maximum number of nodes is: %d\n", max_count_depth);

    return max_count_depth;
}
