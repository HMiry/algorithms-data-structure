#include <stdio.h>
#include <stdlib.h>



int bin_search(int v[], int l, int r, int k) {
    int c;

    if (l > r) {
        return(-1);  // Element not found
    }

    c = (l + r) / 2;  // Find the middle element

    // Check if the middle element is the key
    if (k < v[c]) {
        return(bin_search(v, l, c - 1, k));  // Search in the left subarray
    } else if (k > v[c]) {
        return(bin_search(v, c + 1, r, k));  // Search in the right subarray
    }

    return c;  // Middle element is the key, return its index
}
