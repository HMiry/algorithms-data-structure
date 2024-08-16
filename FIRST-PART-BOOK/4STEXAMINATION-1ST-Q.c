


#include <string.h>


//second version
int string_search(char *str, int *start, int *length) {
    int i, j;
    int str_length = strlen(str); // To avoid multiple calls to strlen in the loop

    *start = 0;
    *length = 0;
    for (i = 0; i < str_length - 1; ) {
        // Visit sub-string starting at position i
        for (j = i + 1; j < str_length && str[j] == str[i]; j++) {
            // The loop condition itself ensures the sequence of identical characters
        }
        // Update best sub-string found
        if ((j-i) > (*length)) {
            *length = j-i;
            *start = i;
            i = j;
        }else {
                i=i+1;
            }
        
    }
    return 0;
}




int string_search (char *str, int *start, int *length) {
    int i, j;

    *start = *length = i = 0;
    // Visit string str
    while (i<strlen(str)-1) {
        j = i + 1;
        // Visit sub-string starting at position i
        while (j<strlen(str) && str[j]==str[i]) {
            j++;
        }
        // Update best sub-string found
        if ((j-i) > (*length)) {
            *length = j-i;
            *start = i;
            i = j;
        }else {
                i=i+1;
            }
        
    }    
    return 0;
}

//commented version 


#include <string.h>

int string_search (char *str, int *start, int *length) {
    int i, j;

    // Initialize start and length of the longest substring, and the iterator i
    *start = *length = i = 0;

    // Outer loop: iterate through the string
    while (i < strlen(str) - 1) { // Ensuring we don't go past the second-to-last character
        j = i + 1; // Start of the inner substring

        // Inner loop: iterate through the substring where all characters are same as str[i]
        while (j < strlen(str) && str[j] == str[i]) {
            // Continue as long as we haven't reached the end of the string and the characters are the same
            j++;
        }

        // Check if the current substring is longer than the longest found so far
        if ((j - i) > (*length)) {
            // Update the longest substring information
            *length = j - i; // Length of the current substring
            *start = i; // Starting index of the current substring
             i = j;
        }
        
    }
    
    return 0; // Return 0 to indicate successful execution
    
}

