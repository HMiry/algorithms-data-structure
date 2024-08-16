#include <stdio.h>
#include <stdlib.h>


const int max_depth = 100; // ro use above function 


// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}


// Recursive helper function to find the maximum depth of the tree
int find_max_depth(node_t *root) {
    if (root == NULL) {
        return 0;
    }
    int max_depth = 0;
    for (int i = 0; i < root->child_count; ++i) {
        int depth = find_max_depth(root->children[i]);
        if (depth > max_depth) {
            max_depth = depth;
        }
    }
    return max_depth + 1; // Add 1 for the current node
}


int count_nodes(node_t *root) { // for counting the nodes 
    if (root == NULL) {
        return 0;
    }
    int count = 1; // Counting the root itself
    for (int i = 0; i < root->child_count; ++i) {
        count += count_nodes(root->children[i]); // Add the count of child nodes
    }
    return count;
}


// Recursive helper function to collect keys at a given level
void collect_keys_at_level(node_t *root, int current_level, int target_level, int keys[], int *index) {
    if (root == NULL) {
        return;
    }
    if (current_level == target_level) {
        keys[(*index)++] = root->key;
    } else if (current_level < target_level) {
        for (int i = 0; i < root->child_count; ++i) {
            collect_keys_at_level(root->children[i], current_level + 1, target_level, keys, index);
        }
    }
}


// Function to display the keys of the tree in the specified order
void display(node_t *root) {
    int max_depth = find_max_depth(root); // Find the maximum depth of the tree or use function above  
    int *keys = malloc(1000 * sizeof(int)); // Adjust the size according to your needs or use function above  
    if (!keys) {
        perror("Failed to allocate memory for keys");
        return;
    }

    for (int level = 0; level < max_depth; ++level) {
        int index = 0; // Reset index for each level
        collect_keys_at_level(root, 0, level, keys, &index);

        qsort(keys, index, sizeof(int), compare); // index (the number of elements in the keys array), sizeof(int) (the size of each element), and compare (the comparison function),

        // Print sorted keys for this level
        for (int i = 0; i < index; i++) {
            printf("%d ", keys[i]);
        }
    }

    free(keys); // Free the allocated memory for keys
    printf("\n"); // Print a newline at the end
}













typedef struct node {
    int key;
    int child_count;
    struct node **children;
} node_t;

// Function to create a new node
node_t* create_node(int key) {
    node_t *new_node = malloc(sizeof(node_t));
    new_node->key = key;
    new_node->child_count = 0;
    new_node->children = NULL;
    return new_node;
}

// Comparator function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Recursive helper function to collect keys at a given level
void collect_keys_at_level(node_t *root, int current_level, int target_level, int keys[], int *index) {
    if (root == NULL) {
        return;
    }
    if (current_level == target_level) {
        keys[(*index)++] = root->key;
    } else if (current_level < target_level) {
        for (int i = 0; i < root->child_count; ++i) {
            collect_keys_at_level(root->children[i], current_level + 1, target_level, keys, index);
        }
    }
}

// Function to display the keys of the tree in the specified order
void display(node_t *root) {
    int level = 0;
    // Assuming a max of 1000 keys per level, which should be adapted to your needs
    int *keys = malloc(1000 * sizeof(int)); 
    if (!keys) {
        perror("Failed to allocate memory for keys");
        return;
    }

    while (1) {
        int index = 0; // Reset index for each level
        collect_keys_at_level(root, 0, level, keys, &index);

        if (index == 0) {
            // No keys found at the current level, so we're done
            break;
        }

        qsort(keys, index, sizeof(int), compare); // Sort the keys at this level

        // Print sorted keys for this level
        for (int i = 0; i < index; i++) {
            printf("%d ", keys[i]);
        }
        level++; // Move to the next level
    }
    
    free(keys); // Free the allocated memory for keys
}
