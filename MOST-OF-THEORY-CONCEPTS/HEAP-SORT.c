#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)
#define PARENT(i) ((int)(i-1)/2)

typedef struct {
    int key;    // This is the key based on which the heap is constructed
    // ... other data fields
} node;

typedef struct heap_s {
    node *A;
    int heapsize;
} heap_t;



void heapify(heap_t *heap, int root) {
    int l, r, largest;
    l = LEFT(root);
    r = RIGHT(root);
    if ((l < heap->heapsize) &&
        (item_greater(heap->A[l], heap->A[root])))
        largest = l;
    else
        largest = root;
    if ((r < heap->heapsize) &&
        (item_greater(heap->A[r], heap->A[largest])))
        largest = r;
    if (largest != root) {
        swap(heap, root, largest);
        heapify(heap, largest);
    }
    return;
}
void heapbuild(heap_t *heap) {
    int i;
    for (i = (heap->heapsize)/2 - 1; i >= 0; i--) {
        heapify(heap, i);
    }
    return;
}
void heapsort(heap_t *heap) {
    int i, tmp;

    heapbuild(heap);

    tmp = heap->heapsize;
    for (i = heap->heapsize - 1; i > 0; i--) {
        swap(heap, 0, i);
        heap->heapsize--;
        heapify(heap, 0);
    }

    heap->heapsize = tmp;

    return;
}
