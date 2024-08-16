#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node_t {
    char *data;
    struct node_t *next;
} node_t;

// Helper function to create a new node
node_t* create_node(char *data) {
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (!new_node) return NULL;
    new_node->data = strdup(data); // Copy the data into the node
    new_node->next = NULL;
    return new_node;
}

// Append node to a circular FIFO list
void append_to_list(node_t **head, char *data) {
    node_t *new_node = create_node(data);
    if (*head==NULL) {
        *head = new_node;
        new_node->next = *head; // Make the list circular
    } else {
        node_t *temp = *head;
        while (temp->next != *head) { // Find the last node
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head; // Point the new last node to the first node
    }
}


User
void tail_insert(node_t **head, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;

    if (*head == NULL) {
        new_node->next = new_node; // Points to itself
        *head = new_node;
    } else {
        node_t *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head; // Point back to the head, maintaining circularity
    }
}




// The main function that processes the string and fills the lists
void string_to_fifo(char *s, node_t **letter, node_t **digit) {
    char buffer[256]; // Assuming individual sequences won't exceed this length
    int buf_index = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (isalpha(s[i])) { // If the current char is a letter
            if (buf_index > 0 && !isalpha(s[i-1])) { // Previous was digit, switch occurred
                buffer[buf_index] = '\0'; // Null-terminate the digit sequence
                append_to_list(digit, buffer); // Add to digit list
                buf_index = 0; // Reset buffer index for new sequence
            }
            buffer[buf_index++] = s[i]; // Add to buffer
        } else if (isdigit(s[i])) { // If the current char is a digit
            if (buf_index > 0 && !isdigit(s[i-1])) { // Previous was letter, switch occurred
                buffer[buf_index] = '\0'; // Null-terminate the letter sequence
                append_to_list(letter, buffer); // Add to letter list
                buf_index = 0; // Reset buffer index for new sequence
            }
            buffer[buf_index++] = s[i]; // Add to buffer
        }
    }
    // Handle the last sequence in the buffer
    if (buf_index > 0) {
        buffer[buf_index] = '\0'; // Null-terminate the sequence
        if (isalpha(buffer[0])) { // If the sequence is letters
            append_to_list(letter, buffer);
        } else { // If the sequence is digits
            append_to_list(digit, buffer);
        }
    }
}



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h> // For isalpha and isdigit

void string_to_fifo(char *s, node_t **letter, node_t **digit) {
    int startPos = 0, length = strlen(s);
    node_t *lastLetter = NULL, *lastDigit = NULL; // Pointers to the last nodes

    while (startPos < length) {
        int endPos = startPos;
        // Determine if we're starting with a letter or digit
        int isLetter = isalpha(s[startPos]);

        // Find the end of the current subsequence
        while (endPos < length && ((isLetter && isalpha(s[endPos])) || (!isLetter && isdigit(s[endPos])))) {
            endPos++;
        }

        // Allocate and set up the new node
        node_t *new_node = malloc(sizeof(node_t));
        if (!new_node) {
            fprintf(stderr, "Memory allocation error.\n");
            exit(EXIT_FAILURE);
        }
        new_node->wstr = malloc((endPos - startPos + 1) * sizeof(char));
        if (USE_STRNCPY) {
            strncpy(new_node->wstr, &s[startPos], endPos - startPos);
        } else {
            memcpy(new_node->wstr, &s[startPos], endPos - startPos);
        }
        new_node->wstr[endPos - startPos] = '\0'; // Null-terminate the string

        // Insert the node into the appropriate list and maintain circularity
        if (isLetter) {
            if (*letter == NULL) {
                *letter = new_node;
                lastLetter = new_node;
                new_node->next = *letter; // Make it circular immediately
            } else {
                lastLetter->next = new_node;
                lastLetter = new_node;
                lastLetter->next = *letter; // Maintain circularity
            }
        } else {
            if (*digit == NULL) {
                *digit = new_node;
                lastDigit = new_node;
                new_node->next = *digit; // Make it circular immediately
            } else {
                lastDigit->next = new_node;
                lastDigit = new_node;
                lastDigit->next = *digit; // Maintain circularity
            }
        }

        startPos = endPos;
    }
}
 if (*letter == NULL) {
                new->next = new;
                *letter=new;
else {
    tmp=letter
    while (tmp!=null){
        tmp=tmp->next
    }
    tmp->next=new;
    new->next=*letter;
    *letter=new;
    
}