#include <stdio.h>
#include <stdlib.h>

void mul(int *v1, int *v2, int n, int **rpv) {
    int *tmp;
    int i, j;
    int carry;

    // Allocate result array
    tmp = (int *) malloc((2 * n) * sizeof(int));
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize it
    for (i = 0; i < 2*n; i++) {
        tmp[i] = 0;
    }

    // For each digit of v1 ...
    for (i = 0; i < n; i++) {
        carry = 0;

        // ... and for each digit of v2 ...
        for (j = 0; j < n; j++) {
            // Compute product
            tmp[i + j] += v1[i] * v2[j] + carry;
            // Get most significant digit (carry)
            carry = tmp[i + j] / 10;
            // Get least significant digit
            tmp[i + j] = tmp[i + j] % 10;
        }
    tmp[i + n - 1] += carry;

    // Set output parameter
    *rpv = tmp;

    return;
}
