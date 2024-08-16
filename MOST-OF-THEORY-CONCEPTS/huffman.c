// PQ *pq;
// pq = pq_init (maxN, item_compare);
// for (i=0; i<maxN; i++) {
//     printf ("Enter letter & frequency: ");
//     scanf ("%s %d", &letter, &freq);
//     tmp = item_new (letter, freq);
//     pq_insert (pq, tmp);
// }
// while (pq_size(pq) > 1) {
//     l = pq_extract_max (pq);
//     r = pq_extract_max (pq);
//     tmp = item_new ('!', l->freq + r->freq);
//     tmp->left = l;
//     tmp->right = r;
//     pq_insert (pq, tmp);
// }
// root = pq_extract_max (pq);
// pq_display (root, code, 0);









// #include <stdio.h>
// #include <stdlib.h>

// // Assuming Item is defined somewhere in the data-item library with fields 'char letter', 'int freq', 'Item *left', and 'Item *right'.
// // Assuming pq_t is a type that represents a priority queue.

// pq_t *pq_init(int maxN, int (*item_compare)(const void *, const void *));
// Item *item_new(char letter, int freq);
// void pq_insert(pq_t *pq, Item *item);
// int pq_size(const pq_t *pq);
// Item *pq_extract_max(pq_t *pq);
// void pq_display(const Item *root, char *code, int depth);

// int main() {
//     int maxN = 100; // Maximum number of nodes in Huffman tree, for example
//     char letter;
//     int freq;
//     Item *tmp, *l, *r, *root;
//     char code[256]; // Assuming a maximum code length of 256

//     // Initialize the priority queue with the maximum size and comparison function
//     pq_t *pq = pq_init(maxN, item_compare);

//     // Read maxN pairs of letter and frequency from the user
//     for (int i = 0; i < maxN; i++) {
//         printf("Enter letter & frequency: ");
//         scanf(" %c %d", &letter, &freq); // Space before %c to skip whitespace
//         tmp = item_new(letter, freq);
//         pq_insert(pq, tmp);
//     }

//     // Main loop to build the Huffman tree
//     while (pq_size(pq) > 1) {
//         l = pq_extract_max(pq);
//         r = pq_extract_max(pq);
//         tmp = item_new('!', l->freq + r->freq);
//         tmp->left = l;
//         tmp->right = r;
//         pq_insert(pq, tmp);
//     }

//     // Extract the remaining item from pq, which is the root of the Huffman tree
//     root = pq_extract_max(pq);

//     // Display the Huffman codes starting from the root
//     pq_display(root, code, 0);

//     // Depending on the implementation, you may need to free the memory for the priority queue and the Huffman tree

//     return 0;
// }

// // Definitions for item_compare, pq_init, item_new, pq_insert, pq_size, pq_extract_max, and pq_display
// // need to be provided by the data-item library or implemented separately.







#include <stdio.h>
#include <stdlib.h>

#define MAXN 256 // Maximum number of distinct characters for the Huffman tree
#define PARENT(i) ((int)(i-1)/2)
// Structure for a node in the Huffman tree
typedef struct Item {
    char letter;       // Character represented by this node
    int freq;          // Frequency of the character
    struct Item *left; // Left child in the Huffman tree
    struct Item *right;// Right child in the Huffman tree
} Item;

// Structure for the priority queue used to build the Huffman tree
typedef struct pq_s {
    Item *A[MAXN]; // Array of pointers to items, organized as a heap
    int size;         // Current number of elements in the priority queue
} pq_t;

// Function to create a new node (Item) for the Huffman tree
Item *item_new(char letter, int freq) {
    Item *node = (Item *)malloc(sizeof(Item)); // Allocate memory for the new node
    node->letter = letter; // Set the character for this node
    node->freq = freq;     // Set the frequency for this node
    node->left = node->right = NULL; // Initially, the node has no children
    return node; // Return the pointer to the new node
}

// Function to initialize the priority queue
pq_t *pq_init() {
    pq_t *pq = (pq_t *)malloc(sizeof(pq_t)); // Allocate memory for the priority queue
    pq->size = 0; // Set the initial size of the priority queue to zero
    return pq; // Return the pointer to the priority queue
}

// Function to maintain the min-heap property of the priority queue
void pq_heapify(pq_t *pq, int i) {
    int smallest = i; // Start with the current index as the smallest
    int left = 2 * i + 1; // Calculate the index of the left child
    int right = 2 * i + 2; // Calculate the index of the right child

    // Compare the current item with its left child
    if (left < pq->size && pq->A[left]->freq < pq->A[smallest]->freq)
        smallest = left;

    // Compare the smallest item with its right child
    if (right < pq->size && pq->A[right]->freq < pq->A[smallest]->freq)
        smallest = right;

    // If the smallest item is not the current item, swap them
    if (smallest != i) {
        Item *temp = pq->A[i];
        pq->A[i] = pq->A[smallest];
        pq->A[smallest] = temp;
        pq_heapify(pq, smallest); // Recursively heapify the affected sub-tree
    }
}

// Function to insert a new item into the priority queue
void pq_insert(pq_t *pq, Item *item) {
    int i = pq->size++; // Insert the new item at the next available index
    // Bubble up the new item to maintain the heap property
    while (i && item->freq < pq->A[PARENT(i)]->freq) {
        pq->A[i] = pq->A[PARENT(i)];
        i = PARENT(i);
    }
    pq->A[i] = item; // Place the new item in its correct position
}

// Function to extract the item with the smallest frequency from the priority queue
Item *pq_extract_min(pq_t *pq) {
    if (pq->size <= 0) return NULL; // Return NULL if the queue is empty
    Item *min = pq->A[0]; // The smallest item is at the root of the heap
    pq->A[0] = pq->A[--pq->size]; // Replace the root with the last item
    pq_heapify(pq, 0); // Restore the heap property
    return min; // Return the smallest item
}

// Function to get the current size of the priority queue
int pq_size(const pq_t *pq) {
    return pq->size; // Return the size field of the priority queue
}

// Function to display Huffman codes for each letter
void huffman_display(Item *root, char *code, int depth) {
    // Base case: If the current node is NULL, do nothing and return
    if (!root) return;

    // Check if the current node is a leaf node (contains a letter)
    if (root->letter != '\0') {
        // Terminate the code string at the current depth to print the code for this letter
        code[depth] = '\0';
        // Print the letter, its frequency, and its Huffman code
        printf("Letter: %c, Freq: %d, Code: %s\n", root->letter, root->freq, code);
    } else {
        // If the current node is not a leaf, append '0' to the code and recurse on the left child
        code[depth] = '0';
        huffman_display(root->left, code, depth + 1);

        // After exploring left, replace '0' with '1' and recurse on the right child
        code[depth] = '1';
        huffman_display(root->right, code, depth + 1);
    }
    // Note: The function uses depth-first search to traverse the Huffman tree
}
