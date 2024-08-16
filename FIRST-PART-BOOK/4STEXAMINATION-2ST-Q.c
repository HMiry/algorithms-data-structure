
// As to why the code doesn't use a current or temp pointer for traversal or manipulation of the linked list,
//  it's likely because the specific operation in the string_split function does not require it.
//   The function is constructing the linked list by prepending new nodes to the beginning of the list (top), 
//   which negates the need for a current pointer to traverse or modify the list.
//    The top pointer is sufficient to keep track of the start of the list, and the p pointer is used to create and set up new nodes. 
//    The nodes are inserted directly at the head of the list each time,
//  so there's no need to traverse the list; hence, a current or temp pointer isn't necessary in this particular context.


        
#ifndef _IMPL2
#define _IMPL2

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node {
    char *wstr;
    struct node *next;
} node_t;

node_t *string_split(char *);

#endif


//#include "impl2.h"
/*
 * If not 0 use strcpy to copy a substring into a new list node.
 * Otherwise copy char by char
 */
#define USE_STRNCPY 1
node_t *string_split(char *str) {
    node_t *top = NULL, *p;
    int startPos, endPos;

    top = NULL;
    startPos = endPos = 0;
    while (endPos<strlen(str)) {
        while (endPos<strlen(str) && str[endPos]!='.') {
            endPos++;
        }
        // Allocate a new node
        p = malloc(1 * sizeof(node_t));
        if (p == NULL) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        p->wstr = malloc((endPos-startPos+1) * sizeof(char));
        strncpy(p->wstr, &str[startPos], (endPos-startPos));
        endPos++;
        startPos = endPos;
        // Insert element onto the list
        p->next =top;
        top = p;
    }
    return top;
}






//commented code 


// Define the structure of a node for a linked list that stores strings.
typedef struct node {
    char *wstr;   // Pointer to a string, to store a part of the split string.
    struct node *next; // Pointer to the next node in the list.
} node_t;

// Prototype declaration for string_split function.
node_t *string_split(char *);

// Function to split a string into a linked list of substrings divided at each period ('.').
node_t *string_split(char *str) {
    // Pointers to the top (start) of the list and a temporary node.
    node_t *top = NULL, *p;
    int startPos, endPos; // Positions used to find the substrings.

    // Initialize the list as empty and positions at the start of the string.
    top = NULL;
    startPos = endPos = 0;
    // Iterate over the string until the end is reached.
    while (endPos < strlen(str)) {
        // Find the next period in the string to determine the end of the current substring.
        while (endPos < strlen(str) && str[endPos] != '.') {
            endPos++;
        }

        // Allocate memory for a new node to store the substring.
        p = malloc(1 * sizeof(node_t));
        if (p == NULL) { // Check for successful memory allocation.
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        // Allocate memory for the substring within the node, including space for the null terminator.
        p->wstr = malloc((endPos - startPos + 1) * sizeof(char));

        // Use either strncpy or manual copying depending on the USE_STRNCPY directive.
        // Copy the substring using strncpy, which is safer and avoids buffer overflow.
        strncpy(p->wstr, &str[startPos], (endPos - startPos));
        // Manually add the null terminator after the copied substring.
        p->wstr[endPos - startPos] = '\0';
        endPos++;
        startPos = endPos;

        // Insert the new node at the beginning of the linked list.
        p->next = top;
        top = p;
    }

    // Return the pointer to the top of the linked list containing the substrings.
    return top;
}
