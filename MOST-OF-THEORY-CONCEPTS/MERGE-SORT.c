#include <stdio.h>
#include <stdlib.h>
//A is the original array and c: The ending index of the left half (so, c + 1 is the start of the right half)
void merge(int *A, int *B, int l, int c, int r) {
    int i = l, j = c+1, k = l;

    // Merge the two halves into auxiliary array B
    //i is i n the left and j is in the right 
    for (i=l, j=c+1, k=l; i<=c && j<=r;) {
        if (A[i] <= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }

    // Copy the remaining elements of the left half, if there are any
    while (i <= c) {
        B[k++] = A[i++];
    }

    // Copy the remaining elements of the right half, if there are any
    while (j <= r) {
        B[k++] = A[j++];
    }

    // Copy back the merged elements from array B to array A
    for (i = l; i <= r; i++) {
        A[i] = B[i];
    }
}

void merge_sort_r(int *A, int *B, int l, int r) {
    int c;
    if (r <= l) {
        return;
    }
    c = (l + r) / 2;

    // Sort the left half
    merge_sort_r(A, B, l, c);

    // Sort the right half
    merge_sort_r(A, B, c+1, r);

    // Merge the two halves
    merge(A, B, l, c, r);
}

void merge_sort(int *A, int N) {
    int l = 0, r = N-1;
    int *B = (int *)malloc(N * sizeof(int));
    if (B == NULL) {
        perror("malloc");
        return;
    }

    merge_sort_r(A, B, l, r);

    // It's important to free the auxiliary array B after the sort is complete
    free(B);
}

int main() {
    int A[] = {5, 3, 8, 4, 2};
    int N = sizeof(A) / sizeof(A[0]);

    merge_sort(A, N);

    // Print the sorted array
    for (int i = 0; i < N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    return 0;
}
