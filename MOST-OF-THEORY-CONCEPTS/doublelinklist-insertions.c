typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node_t;
void head_insert(node_t **head, node_t **tail, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = *head;
    new_node->prev = NULL;

    if (*head != NULL) {
        (*head)->prev = new_node;
    }
    *head = new_node;

    if (*tail == NULL) { // List was empty
        *tail = new_node;
    }
}
void middle_insert(node_t **head, int value, int position) {
    if (position <= 0) {
        head_insert(head, value);
        return;
    }

    node_t *current = *head;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = current->next;
    new_node->prev = current;

    if (current->next != NULL) {
        current->next->prev = new_node;
    }
    current->next = new_node;
}
void tail_insert(node_t **head, node_t **tail, int value) {
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node) {
        perror("Failed to allocate new node");
        exit(EXIT_FAILURE);
    }
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = *tail;

    if (*tail != NULL) {
        (*tail)->next = new_node;
    }
    *tail = new_node;

    if (*head == NULL) { // List was empty
        *head = new_node;
    }
}
