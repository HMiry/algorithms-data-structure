#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming the 'struct element' is defined as follows:
typedef struct element {
    char* word;
    struct element* next;
} element;

// Function to concatenate all strings from the list into a single string
char* visit_and_insert(element *p) {
    // First, determine the total length required for the concatenated string
    size_t total_length = 0;
    element *current = p;
    while (current != NULL) {
        total_length += strlen(current->word) + 1; // +1 for the space or null terminator
        current = current->next;
    }
    
    if (total_length == 0) { // If the list is empty, return an empty string
        return strdup("");
    }

    // Allocate memory for the concatenated string
    char *concatenated = malloc(total_length * sizeof(char));
    if (!concatenated) {
        perror("Failed to allocate memory for concatenated string");
        exit(EXIT_FAILURE);
    }

    // Copy words from the list into the concatenated string
    concatenated[0] = '\0'; // Start with an empty string
    current = p;
    while (current != NULL) {
        strcat(concatenated, current->word);
        if (current->next) {
            strcat(concatenated, " "); // Add a space between words
        }
        current = current->next;
    }

    return concatenated;
}

// Function to free the memory used by the concatenated string
void free_concatenated_string(char *s) {
    free(s);
}

int main() {
    // Example usage:
    element e1 = {"This", NULL};
    element e2 = {"is", NULL};
    element e3 = {"a", NULL};
    element e4 = {"list", NULL};
    element e5 = {"of", NULL};
    element e6 = {"strings", NULL};

    // Linking the elements
    e1.next = &e2;
    e2.next = &e3;
    e3.next = &e4;
    e4.next = &e5;
    e5.next = &e6;

    char *result = visit_and_insert(&e1);
    printf("Concatenated string: %s\n", result);
    
    // Free the allocated memory
    free_concatenated_string(result);

    return 0;
}
