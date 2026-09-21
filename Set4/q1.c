#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void preorder(Node *root) {
    if (root == NULL)
        return;

    Node *stack[100];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        Node *temp = stack[top--];

        printf("%d ", temp->data);

        if (temp->right != NULL)
            stack[++top] = temp->right;

        if (temp->left != NULL)
            stack[++top] = temp->left;
    }
}

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

int main() {
    Node *root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Preorder Traversal: ");
    preorder(root);

    return 0;
}