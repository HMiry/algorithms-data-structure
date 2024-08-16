typedef struct node {
    int value;
    struct node *next;
} node_t;
void head_insert(node_t **head, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;

    if (*head == NULL) {
        new_node->next = new_node; // Points to itself, making the list circular
        *head = new_node;
    } else {
        node_t *temp = *head;
        while (temp->next != *head) { // Find the last node
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->next = *head;
        *head = new_node; // Update the head
    }
}
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
void middle_insert(node_t **head, int value, int position) {
    if (position <= 0 || *head == NULL) {
        head_insert(head, value); // For circular list, head insertion handles circularity
        return;
    }

    node_t *current = *head;
    for (int i = 0; current->next != *head && i < position - 1; i++) {
        current = current->next;
    }

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = current->next;
    current->next = new_node;
}
