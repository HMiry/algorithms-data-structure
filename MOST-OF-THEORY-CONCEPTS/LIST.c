#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list2_t {
    int value;
    int count;
    struct list2_t* next;
} list2_t;

typedef struct list1_t {
    char* name;
    list2_t* secondaryList;
    struct list1_t* next;
} list1_t;

list2_t* find_or_insert_secondary(list2_t** head, int value) {
    list2_t* current = *head;
    while (current) {
        if (current->value == value) {
            current->count++;
            return current;
        }
        current = current->next;
    }
    list2_t* new_node = malloc(sizeof(list2_t));
    new_node->value = value;
    new_node->count = 1;
    new_node->next = *head;
    *head = new_node;
    return new_node;
}

list1_t* find_or_insert_main(list1_t** head, char* name, int value) {
    list1_t* current = *head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            find_or_insert_secondary(&(current->secondaryList), value);
            return current;
        }
        current = current->next;
    }
    list1_t* new_node = malloc(sizeof(list1_t));
    new_node->name = strdup(name);
    new_node->secondaryList = NULL;
    new_node->next = *head;
    *head = new_node;
    find_or_insert_secondary(&(new_node->secondaryList), value);
    return new_node;
}

list1_t* insert_from_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    list1_t* head = NULL;
    char name_buffer[101];
    int value;
    while (fscanf(file, "%100s %d", name_buffer, &value) == 2) {
        find_or_insert_main(&head, name_buffer, value);
    }

    fclose(file);
    return head;
}

void free_secondary_list(list2_t* head) {
    while (head) {
        list2_t* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_main_list(list1_t* head) {
    while (head) {
        list1_t* temp = head;
        head = head->next;
        free(temp->name);
        free_secondary_list(temp->secondaryList);
        free(temp);
    }
}

int main() {
    list1_t* list = insert_from_file("data.txt");

    // ... use the list as needed ...

    free_main_list(list); // Free all allocated memory
    return 0;
}
