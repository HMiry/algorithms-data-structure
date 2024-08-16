

list_t *enqueue(list_t *pTail, list_t *p) {
    if (pTail == NULL) {
        p->next = p; // Make the list circular by pointing the node to itself
    } else {
        p->next = pTail->next;
        pTail->next = p;
    }
    return p; // Return the new tail
}



//just a comparison


// Circular List Implementation
list_t *enqueue(list_t *pTail, list_t *p) {
    if (pTail == NULL) {
        pTail = p;
        pTail->next=p;
    } else {
        p->next = pTail->next;
        pTail->next = p;
        pTail = p;
    }

    return (pTail);
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
