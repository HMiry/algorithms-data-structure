#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//exmple of the wanted question this
// procedure is the version 2 of the professor
// a = [1, 14, 9]
// b = [2, 25, 6]
// c = [3, 7, 28]
// d = [1, 2, 3, 6, 7, 9, 14, 25, 28]

//na-b-c is for keeping track of the lenght of the arrays a,b,c
int *merge3_ver2(int *a, int *b, int *c, int na, int nb, int nc) {
    int *d;
    int *m[3], len[3];
    int i, j, min1, n;

    // Assign array pointers to the array of pointers m
    m[0] = a;
    m[1] = b;
    m[2] = c;

    // Initialize lengths of the arrays
    len[0] = na;
    len[1] = nb;
    len[2] = nc;

    // Calculate the total length of the new array
    n = na + nb + nc;
    // Allocate memory for the merged array
    d = (int *)malloc(n * sizeof(int));
    if (d == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Merge process
    for (i = 0; i < n; i++) {
        min1 = -1; // Start with min1 as -1 indicating no minimum found yet

        // Find the smallest number among the three arrays
        for (j = 0; j < 3; j++) {
            // Check if there are elements left in the j-th array and if the current element is smaller than the current minimum
            if (len[j] > 0 && (min1 == -1 || m[j][0] < m[min1][0])) {//m[j][0] means reffering to the first[0] element of a or b or c regarding the value of j 
                min1 = j; // Update the index of the array with the smallest element
            }
        }

        // Add the smallest number to the merged array
        d[i] = m[min1][0];
        m[min1]++;      // Move pointer of the array from which the element was taken
        len[min1]--;    // Decrement the length of the array from which the element was taken
    }

    return d; // Return the merged array
}
// this part is just to check your programm
int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int b[] = {2, 3, 4, 5, 6, 7, 8, 9};
    int c[] = {3, 4, 5, 6, 7, 8, 9};
    int *d;
    d = merge(a, b, c, 9, 8, 7);
    for (int i = 0; i < 24; i++) {
        printf("%d\n", d[i]);
    }
    free(d); // Free the allocated memory
    return EXIT_SUCCESS;
}
