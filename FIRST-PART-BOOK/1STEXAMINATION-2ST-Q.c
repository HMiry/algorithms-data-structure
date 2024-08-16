#ifndef _LIST
#define _LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list_s list_t;
struct list_s {
    char *surname;
    char *name;
    struct list_s *next;
};

int list_insert_in_order(list_t **, char *, char *);

#endif

/* File list.c */

#include <stdlib.h>
#include <string.h>
// #include <"list.h">

int list_insert_in_order(list_t **headp, char *surname, char *name) {
    list_t *head, *ptr, *node;
    
    head = *headp;//USING LOCAL HEADER NOT THE MAIN ONE WHICH IS THE HEADP
    
    /* Initial search */ 
    for (node=head; node!=NULL; node=node->next) {
        if (strcmp(surname, node->surname)==0 && strcmp(name, node->name)==0) {
            return 0;
        }
    }
    

/* Allocate new node and copy fields */
    node = (list_t *) malloc(sizeof(list_t));
    if (node==NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }

    node->surname = strdup(surname);
    node->name = strdup(name);
    //surname is the new node and the head->surname is the current node 
    /* Insertion ahead */ //strcmp<0 menas surname would come before head->surname in a dictionary.
    if (head==NULL || strcmp(surname, head->surname)<0 ||
        (strcmp(surname, head->surname)==0 && strcmp(name, head->name)<0)) {
        node->next = head;
        *headp = node;
        return 1;
    }

    /* Insertion in the middle (or at the end) */
    ptr = head;
    while (ptr->next!=NULL && (strcmp(surname, ptr->next->surname)>0 ||
        (strcmp(surname, ptr->next->surname)==0 && strcmp(name, ptr->next->name)>0))) {
        ptr = ptr->next;
    }

    node->next = ptr->next;
    ptr->next = node;

    return 1;
}





