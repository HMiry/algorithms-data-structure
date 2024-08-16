typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createTreeNode(int data) {
    TreeNode* newNode = malloc(sizeof(TreeNode));
    if (newNode) {
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    return newNode;
}

TreeNode* insertBST(TreeNode* root, int data) {
    // If the root is NULL, create a new node and return it
    if (root == NULL) {
        return createTreeNode(data);
    }

    // If the data to be inserted is less than the root's data, insert it in the left subtree
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    }
    // If the data to be inserted is greater than the root's data, insert it in the right subtree
    else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    // If the data is equal to the root's data, we don't insert duplicates

    return root;
}

TreeNode* searchBST(TreeNode* root, int data) {
    // If the root is NULL or the root's data matches the search data
    if (root == NULL || root->data == data) {
        return root;
    }

    // If the data to be searched is less than the root's data, search in the left subtree
    if (data < root->data) {
        return searchBST(root->left, data);
    }
    // If the data to be searched is greater than the root's data, search in the right subtree
    return searchBST(root->right, data);
}

------------------------------------------------------------------------------
typedef struct {
    int *items;
    int size;
    int capacity;
} List;

List* createList(int capacity) {
    List *list = malloc(sizeof(List));
    if (list) {
        list->items = malloc(sizeof(int) * capacity);
        list->size = 0;
        list->capacity = capacity;
    }
    return list;
}



typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

ListNode* createListNode(int data) {
    ListNode* newNode = malloc(sizeof(ListNode));
    if (newNode) {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}



typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

Matrix* createMatrix(int rows, int cols) {
    Matrix* matrix = malloc(sizeof(Matrix));
    if (matrix) {
        matrix->rows = rows;
        matrix->cols = cols;
        matrix->data = malloc(sizeof(int*) * rows);
        for (int i = 0; i < rows; i++) {
            matrix->data[i] = malloc(sizeof(int) * cols);
        }
    }
    return matrix;
}


typedef struct MatrixNode {
    int row, col, value;
    struct MatrixNode *right, *down;
} MatrixNode;

typedef struct {
    MatrixNode **rowHeaders, **colHeaders;
    int rows, cols;
} LinkedListMatrix;
