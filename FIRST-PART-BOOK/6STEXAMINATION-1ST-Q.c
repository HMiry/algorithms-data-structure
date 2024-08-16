// void sequence_invert(int *v1, int n, int *v2) {
//     int i, f, j;

//     for (i=0, f=1; i<n; i++) {
//         if (v1[i] < v1[f-1]) { // End of sequence
//             for (j=0; j<(f-i); j++) { // Copy it in reverse order into v2
//                 v2[i+j] = v1[f-j-1];
//             }
//             i = f;
//         }
//     }

//     // Deal with last sub-sequence
//     for (j=0; j<(f-i); j++) {
//         v2[i+j] = v1[f-j-1];
//     }

//     return;
// }


//commented version


void sequence_invert(int *v1, int n, int *v2) {
    // Declare loop counters and indices.
    int i, f, j;
    f = 0;
    // Initialize 'i' for the current position and 'f' for finding the end of the sub-sequence.
    for (i = 1; i < n; i++) {
        // Check if the current element is less than the previous one, indicating the end of a sub-sequence.
        if (v1[i] < v1[i-1]) {
            // Reverse the sub-sequence by copying it into v2 in reverse order.
            for (j = 0; j < (i-f); j++) {
                v2[f+j] = v1[i-j-1];
            }
            // Move to the next sub-sequence to process.
            f = i;
        }
    }

    // After the main loop, handle the last sub-sequence if it wasn't processed within the loop.
    // Note: This logic may be incorrect since 'f' is not being updated within the loop.
    for (j = 0; j < (f-i); j++) {
        v2[i+j] = v1[f-j-1];
    }

    // End the function. Since the function is of void type, no value is returned.
    return;
}
int main(){
        int v1[] = {1, 2, 3, 4, 5, 0, 12, 13, 14, 2};
    int n = sizeof(v1) / sizeof(v1[0]);

    // Array to store the inverted sequence
    int v2[n];

    // Call the function
    sequence_invert(v1, n, v2);

    // Print the inverted sequence
    printf("Inverted sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", v2[i]);
    }
    printf("\n");

    return 0;
}



void sequence_invert(int *v1, int n, int *v2) {
    // Declare loop counters and indices.
    int i, f, j;
    i=1;
    // Initialize 'i' for the current position and 'f' for finding the end of the sub-sequence.
    for ( f = i; i < n; i++) {
        // Check if the current element is less than the previous one, indicating the end of a sub-sequence.
        if (v1[i-1] < v1[i]) {
            // Reverse the sub-sequence by copying it into v2 in reverse order.
            for (j = 0; j < i; j++) {
                v2[j+f] = v1[i-j];
            }
            // Move to the next sub-sequence to process.
            j = i;
        }
    }
