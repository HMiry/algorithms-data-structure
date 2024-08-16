#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// The partition function is not shown in the image but it is essential for quicksort.
// It selects a pivot element and partitions the array such that elements less than
// the pivot are on the left of the pivot and elements greater are on the right.
int partition(int *A, int l, int r) {
    int pivot = A[r]; // Choosing the last element as the pivot
    int i = l - 1;
    int j = r;

    while (1) {
        // Move i to the right as long as elements are less than the pivot
        do {
            i++;
        } while (A[i] < pivot);

        // Move j to the left as long as elements are greater than the pivot
        do {
            j--;
        } while (j >= l && A[j] > pivot);

        // If the indices have met or crossed, exit the loop
        if (i >= j) {
            break;
        }

        // Swap the elements at i and j
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }

    // Place the pivot in the correct position by swapping
    int temp = A[i];
    A[i] = A[r];
    A[r] = temp;

    // Return the position of the pivot
    return i;
}

// The recursive quick sort function
void quick_sort_r(int *A, int l, int r) {
    if (l < r) {  // Termination condition
        int c = partition(A, l, r);  // Division
        quick_sort_r(A, l, c - 1);   // Recursive call for the left partition
        quick_sort_r(A, c + 1, r);   // Recursive call for the right partition
    }
}

// The initial quick sort function that sets the boundaries
void quick_sort(int *A, int N) {
    int l = 0;
    int r = N - 1;
    quick_sort_r(A, l, r);  // Recursive call
}

int main() {
    int A[] = {10, 7, 8, 9, 1, 5};
    int N = sizeof(A)/sizeof(A[0]);
    quick_sort(A, N);
    printf("Sorted array: \n");
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
    return 0;
}




Let's consider an array [4, 3, 7, 1, 5] and see how the partitioning works.

    Initial Setup:
        Array: [4, 3, 7, 1, 5]
        Pivot: 5 (last element)
        i = l - 1 = -1, j = l = 0

    First Iteration (j = 0):
        A[j] = 4, which is less than the pivot.
        Increment i (i = 0) and swap A[i] and A[j] (but they are the same here).
        Array after swap: [4, 3, 7, 1, 5]

    Second Iteration (j = 1):
        A[j] = 3, less than pivot.
        Increment i (i = 1), swap A[i] and A[j].
        Array after swap: [4, 3, 7, 1, 5]

    Third Iteration (j = 2):
        A[j] = 7, greater than pivot, no swap.

    Fourth Iteration (j = 3):
        A[j] = 1, less than pivot.
        Increment i (i = 2), swap A[i] and A[j].
        Array after swap: [4, 3, 1, 7, 5]

    Final Swap:
        Swap pivot with A[i + 1] (pivot and 7).
        Array after swap: [4, 3, 1, 5, 7]

    Pivot Position:
        Return i + 1 = 3, the new pivot position.