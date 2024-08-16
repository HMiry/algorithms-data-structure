#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MY VERSION IS SIMPLER I THINK :)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *char_erase_ver1(char *str, int *pos) {
    char *s;
    int i, j, k, flag;
    
    s = (char *) malloc((strlen(str) + 1) * sizeof(char));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    k=0;
    // For each character in position i of str 
    for (i = 0; i < strlen(str); i++) {
        flag = 0; // Assume the character is not in pos initially
        // Visit pos entirely to find index i
        for (j = 0; pos[j] != (-1); j++) {
            if (pos[j] == i) {
                flag = 1; // Found the character at position i in pos, set flag to erase
                break; 
            }
        }
        // If flag is 0, the character is not in pos; copy str[i] into s
        if (flag == 0) {
            s[k] = str[i];
            k++;
        }
    }
    s[k] = '\0';
    
    return s;
}














/* Version 1: Quadratic Cost */
char *char_erase_ver1(char *str, int *pos) {
    char *s;
    int i, j, k;
    
    s = (char *) malloc((strlen(str) + 1) * sizeof(char));
    if (s==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // For each character in position i of str
    for (i=k=0; i<strlen(str); i++) {
        // Visit pos entirely to find index i
        for (j=0; pos[j]!=(-1) && pos[j]!=i; j++);
        // And if it is not in pos copy str[i] into s
        if (pos[j]==(-1)) {
            s[k] = str[i];
            k++;
        }
    }
    s[k] = '\0';
    
    return s;
}



//commented version 

// Includes standard input/output, standard library, and string manipulation libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Version 1: Quadratic Cost */
// Function declaration: takes a string and an array of positions (integers).
char *char_erase_ver1(char *str, int *pos) {
    // Variable declaration:
    // s: pointer to the resulting string after erasure
    // i: loop counter for the outer loop, representing the current index in str
    // j: loop counter for the inner loop, representing the current index in pos
    // k: index for constructing the new string without the characters to be erased
    char *s;
    int i, j, k;
    
    // Memory allocation for the new string s, with the same length as str plus one for the null terminator.
    s = (char *) malloc((strlen(str) + 1) * sizeof(char));
    // If malloc fails to allocate memory, print an error and exit.
    if (s==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    // The outer loop starts here, iterating over each character in str.
    for (i=k=0; i<strlen(str); i++) {
        // The inner loop starts here, iterating over the pos array.
        // It looks for the current index i in the pos array to determine if it should be erased.
        for (j=0; pos[j]!=(-1) && pos[j]!=i; j++);
        // If the end of pos array is reached without finding i, it means the current character should not be erased.
        // The condition pos[j]==(-1) is true when the end of the array is reached.
        if (pos[j]==(-1)) {
            // The character at str[i] is copied into the new string s at the position k.
            s[k] = str[i];
            // Increment the index k for the new string s.
            k++;
        }
    }
    // Append the null terminator to the end of the new string s to properly terminate it.
    s[k] = '\0';
    
    // Return the pointer to the new string.
    return s;
}
