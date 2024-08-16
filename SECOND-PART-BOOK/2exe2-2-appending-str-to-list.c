#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element {
    char *word;
    struct element *next;
} element;

// Helper function to create a new list element with the given word
element* create_element(const char* word, int length) {
    element* new_elem = (element*)malloc(sizeof(element));
    if (!new_elem) {
        perror("Failed to allocate memory for new list element");
        exit(EXIT_FAILURE);
    }
    new_elem->word = (char*)malloc(sizeof(char) * (length + 1));
    if (!new_elem->word) {
        perror("Failed to allocate memory for word");
        exit(EXIT_FAILURE);
    }
    strncpy(new_elem->word, word, length);
    new_elem->word[length] = '\0'; // Null-terminate the string
    new_elem->next = NULL;
    return new_elem;
}

// Function to parse the string and insert words into a linked list
void parse_and_insert(char *s, element **head) {
    element *tail = NULL;
    char *word_start = s;
    char *word_end;

    while (*word_start) {
        // Skip any leading spaces
        while (*word_start == ' ' && *word_start) {
            word_start++;
        }

        // If we've reached the end of the string, break
        if (*word_start == '\0') {
            break;
        }

        // Find the end of the current word
        word_end = word_start;
        while (*word_end != ' ' && *word_end) {
            word_end++;
        }

        // Create a new list element with the current word
        element *new_elem = create_element(word_start, word_end - word_start);

        // Append the new element to the end of the list
        if (tail) {
            tail->next = new_elem;
        } else {
            *head = new_elem;
        }
        tail = new_elem;

        // Move the start to the next word
        word_start = word_end;
    }
}

// Function to print the list - for demonstration purposes
void print_list(element *list) {
    while (list != NULL) {
        printf("%s -> ", list->word);
        list = list->next;
    }
    printf("NULL\n");
}

// Function to free the memory used by the list
void free_list(element *list) {
    while (list != NULL) {
        element *temp = list;
        list = list->next;
        free(temp->word); // Free the word
        free(temp);       // Free the element
    }
}

int main() {
    char text[] = "This is an array of chars"; // Mutable string for strtok
    element *list = NULL;
    
    parse_and_insert(text, &list);
    print_list(list); // This will print the list of words
    free_list(list); // Free the allocated memory
    
    return 0;
}
