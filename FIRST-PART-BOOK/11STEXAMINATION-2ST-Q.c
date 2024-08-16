#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 1000

int phrase_split(char v[], char **wm) {
    char **mat;
    int r, i, j, n, pos;

    // Count number of sub-strings
    r = 1;
    for (i = 0; i < strlen(v); i++) {
        if (v[i] == ' ') {
            r++;
        }
    }

    // Allocate main array of pointers
    mat = malloc(r * sizeof(char *));
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    pos = 0;
    // For each sub-string
    for (n = 0; n < r; n++) {
        // Define sub-string limit
        for (i = pos; i < strlen(v); i++) {
            if (v[i] == ' ') {
                break;
            }
        }

        // Allocate row
        mat[n] = malloc((i - pos + 1) * sizeof(char));
        if (mat[n] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }

        // Copy chars from v to mat
        for (j = 0, i = pos; i < strlen(v); j++, i++) {
            if (v[i] == ' ') {
                break;
            }
            mat[n][j] = v[i];
        }
        mat[n][j] = '\0';
        pos = i + 1;
    }

    *wm = mat;

    return r;
}



//COMMENTED VERSION 


// Define the function 'phrase_split' that splits a string into words by spaces
int phrase_split(char v[], char **wm) {
    // Declaration of pointers and variables used in the function
    char **mat; // Pointer to pointer for dynamically allocated array of word pointers
    int r, i, j, n, pos; // Variables for counting, indexing, and tracking positions

    // Initialize word count to 1 assuming at least one word is present
    r = 1;
    // Loop through the string to count the number of spaces (and thus words)
    for (i = 0; i < strlen(v); i++) {
        if (v[i] == ' ') {
            r++;
        }
    }

    // Dynamically allocate memory for an array of pointers to the words
    mat = malloc(r * sizeof(char *));
    // Check if memory allocation failed
    if (mat == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the position to the start of the string
    pos = 0;
    // Loop to extract each word from the string
    for (n = 0; n < r; n++) {
        // Find the end of the current word delimited by a space
        for (i = pos; i < strlen(v); i++) {
            if (v[i] == ' ') {
                break;
            }
        }

        // Allocate memory for the current word including space for the null terminator
        mat[n] = malloc((i - pos + 1) * sizeof(char));
        // Check if memory allocation failed
        if (mat[n] == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }

        // Copy the word from the string into the newly allocated memory
        for (j = 0, i = pos; i < strlen(v); j++, i++) {
            if (v[i] == ' ') {
                break;
            }
            mat[n][j] = v[i];
        }
        // Null-terminate the current word
        mat[n][j] = '\0';
        // Move the position to the start of the next word
        pos = i + 1;
    }

    // Assign the array of word pointers to the output parameter
    *wm = mat;

    // Return the number of words found
    return r;
}



