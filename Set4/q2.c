//AVL Tree
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

/* Get height */
int height(AVLNode *root) {
    if (root == NULL)
        return 0;

    return root->height;
}

/* Maximum */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Create node */
AVLNode* createNode(int data) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));

    node->data = data;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/* Right Rotation */
AVLNode* rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

/* Left Rotation */
AVLNode* leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/* Balance factor */
int getBalance(AVLNode *root) {
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

/* insertItem */
AVLNode* insertItem(AVLNode *root, int data) {

    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insertItem(root->left, data);

    else if (data > root->data)
        root->right = insertItem(root->right, data);

    else
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    /* LL */
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    /* RR */
    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    /* LR */
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL */
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* Search */
AVLNode* searchItem(AVLNode *root, int data) {

    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return searchItem(root->left, data);

    return searchItem(root->right, data);
}

/* Find minimum */
AVLNode* minValueNode(AVLNode *root) {
    AVLNode *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

/* deleteItem */
AVLNode* deleteItem(AVLNode *root, int data) {

    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteItem(root->left, data);

    else if (data > root->data)
        root->right = deleteItem(root->right, data);

    else {

        if (root->left == NULL || root->right == NULL) {

            AVLNode *temp =
                root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }

            free(temp);
        }
        else {

            AVLNode *temp = minValueNode(root->right);

            root->data = temp->data;

            root->right =
                deleteItem(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(height(root->left),
                           height(root->right));

    int balance = getBalance(root);

    /* LL */
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    /* LR */
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RR */
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    /* RL */
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* deleteTree */
void deleteTree(AVLNode *root) {

    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

/* Display */
void inorder(AVLNode *root) {

    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {

    AVLNode *root = NULL;

    root = insertItem(root, 30);
    root = insertItem(root, 20);
    root = insertItem(root, 10);
    root = insertItem(root, 25);
    root = insertItem(root, 40);
    root = insertItem(root, 50);

    printf("AVL Tree: ");
    inorder(root);

    printf("\n");

    if (searchItem(root, 25))
        printf("25 found\n");
    else
        printf("25 not found\n");

    root = deleteItem(root, 20);

    printf("After deletion: ");
    inorder(root);

    deleteTree(root);

    return 0;
}