#include <stdio.h>
#include <stdlib.h>

#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) ((int)(i-1)/2)

typedef struct {
    int key;    // This is the key based on which the heap is constructed
    // ... other data fields
} node;

typedef struct pq_s {
    node *A;    // Array of nodes
    int pqsize; // Current size of the priority queue
} pq_t;

// Function to swap two nodes
void swap(node *A, int i, int j) {
    node temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

// Function to maintain the max-heap property
void heapify(pq_t *pq, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;

    if (l < pq->pqsize && pq->A[l].key > pq->A[i].key) {
        largest = l;
    }
    if (r < pq->pqsize && pq->A[r].key > pq->A[largest].key) {
        largest = r;
    }

    if (largest != i) {
        swap(pq->A, i, largest);
        heapify(pq, largest);
    }
}

// Function to insert a new key into the priority queue
void pq_insert(pq_t* pq, int key) {
    int i = pq->pqsize++;
    pq->A = realloc(pq->A, pq->pqsize * sizeof(node)); // Ensure there is enough memory

    // Bubble up the new key to maintain the heap property
    while ((i > 0) && (pq->A[PARENT(i)].key < key)) {
        pq->A[i] = pq->A[PARENT(i)];
        i = PARENT(i);
    }
    pq->A[i].key = key;
}

// Function to extract the maximum key from the priority queue
int pq_extract_max(pq_t* pq) {
    if (pq->pqsize < 1) {
        fprintf(stderr, "Error: Priority queue is empty\n");
        return -1;
    }

    // Swap the last element with the root (max element), and decrease the size
    swap(pq->A, 0, pq->pqsize-1);
    int max_key = pq->A[pq->pqsize-1].key;
    pq->pqsize--;

    // Restore the max-heap property
    heapify(pq, 0);

    return max_key;
}

// Function to initialize the priority queue
pq_t *pq_create() {
    pq_t *pq = malloc(sizeof(pq_t));
    if (!pq) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    pq->A = NULL;
    pq->pqsize = 0;
    return pq;
}

// Function to free the priority queue
void pq_free(pq_t *pq) {
    free(pq->A);
    free(pq);
}

// Example usage
int main() {
    pq_t *pq = pq_create();
    pq_insert(pq, 5);
    pq_insert(pq, 10);
    pq_insert(pq, 3);

    printf("Max key extracted: %d\n", pq_extract_max(pq));
    printf("Max key extracted: %d\n", pq_extract_max(pq));

    pq_free(pq);
    return 0;
}
