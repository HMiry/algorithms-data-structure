
#include <stdio.h>
#include <stdlib.h>

void frame_sum_ver3(int **mat, int n, int **vet) {
    int frame, r, c, *v;

    // Dynamically allocate memory for an array to store the sums of the matrix frames
    v = (int *)malloc(((n / 2) + 1) * sizeof(int));
    if (v == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the allocated memory to zero for all elements
    for (frame = 0; frame <= n / 2; frame++) {
        v[frame] = 0;
    }

    // Loop through each frame
    for (frame = 0; frame <= n / 2; frame++) {
        // Loop through each row within the current frame
        for (r = frame; r < n - frame; r++) {
            // Loop through each column within the current frame
            for (c = frame; c < n - frame; c++) {
                // Check if the element is on the border of the current frame
                if (r == frame || r == n - frame - 1 || c == frame || c == n - frame - 1) {
                    v[frame] += mat[r][c];
                }
            }
        }
    }

    // Assign the address of the allocated memory to the output parameter
    *vet = v;
}

int main() {
    int n = 5; // Size of the matrix
    // Example matrix initialization
    int **mat = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        mat[i] = (int *)malloc(n * sizeof(int));
        // Example initialization of matrix values
        for (int j = 0; j < n; j++) {
            mat[i][j] = i * n + j + 1; // Just an example value
        }
    }

    int *frame_sums = NULL;
    frame_sum_ver3(mat, n, &frame_sums);

    // Print the sums of each frame
    for (int i = 0; i <= n / 2; i++) {
        printf("Sum of frame %d: %d\n", i, frame_sums[i]);
    }

    // Clean up
    free(frame_sums);
    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);

    return 0;
}



//
// version 4
void frame_sum_ver4(int **mat, int n, int **vet) {
    int i, r, c, *v;


    // Dynamically allocate memory for an array that will store the sums of the matrix frame
    // The size of the array is (n/2 + 1), to account for the middle row in case of an odd n
    v = malloc(((int)(n/2) + 1) * sizeof(int));
    // If malloc fails to allocate memory, print an error message and exit
    if (v==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the allocated memory to zero for all elements
    for (i=0; i<((int)(n/2)); i++) {
        v[i] = 0;
    }

    // Loop through each element in the matrix
    for (r=0; r<n; r++) {
        for (c=0; c<n; c++) {
            // Determine the "depth" of the element in the matrix, which is the minimum distance
            // to the edge of the matrix
            if (r>c) {
                i = r;
            } else {
                i = c;
            }

            // Add the matrix element value to the corresponding "depth" element in v
            v[i] = v[i] + mat[r][c];
        }
    }

    // Assign the address of the allocated memory to xvet, which is the output parameter
    *vet = v;

    // There is no return statement needed as the function returns void
    // However, it modifies the contents of xvet to point to the sum array
    return;
}

