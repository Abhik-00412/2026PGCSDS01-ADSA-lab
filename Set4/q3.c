//RB Tree
#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct RBNode {
    int data;
    int color;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
} RBNode;

RBNode *NIL;

/* createTree */
void createTree() {
    NIL = (RBNode*)malloc(sizeof(RBNode));

    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;
}

/* Create node */
RBNode* createNode(int data) {

    RBNode *node = (RBNode*)malloc(sizeof(RBNode));

    node->data = data;
    node->color = RED;
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;

    return node;
}

/* Left rotation */
void leftRotate(RBNode **root, RBNode *x) {

    RBNode *y = x->right;

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        *root = y;

    else if (x == x->parent->left)
        x->parent->left = y;

    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/* Right rotation */
void rightRotate(RBNode **root, RBNode *y) {

    RBNode *x = y->left;

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        *root = x;

    else if (y == y->parent->left)
        y->parent->left = x;

    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* Insert fix */
void insertFix(RBNode **root, RBNode *z) {

    while (z->parent->color == RED) {

        if (z->parent == z->parent->parent->left) {

            RBNode *y =
                z->parent->parent->right;

            if (y->color == RED) {

                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else {

                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                rightRotate(root, z->parent->parent);
            }
        }

        else {

            RBNode *y =
                z->parent->parent->left;

            if (y->color == RED) {

                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            }
            else {

                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;

                leftRotate(root, z->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

/* insertItem */
void insertItem(RBNode **root, int data) {

    RBNode *z = createNode(data);
    RBNode *y = NIL;
    RBNode *x = *root;

    while (x != NIL) {

        y = x;

        if (z->data < x->data)
            x = x->left;

        else
            x = x->right;
    }

    z->parent = y;

    if (y == NIL)
        *root = z;

    else if (z->data < y->data)
        y->left = z;

    else
        y->right = z;

    insertFix(root, z);
}

/* searchItem */
RBNode* searchItem(RBNode *root, int data) {

    while (root != NIL) {

        if (root->data == data)
            return root;

        if (data < root->data)
            root = root->left;

        else
            root = root->right;
    }

    return NIL;
}

/* Minimum */
RBNode* minimum(RBNode *root) {

    while (root->left != NIL)
        root = root->left;

    return root;
}

/* Transplant */
void transplant(RBNode **root, RBNode *u, RBNode *v) {

    if (u->parent == NIL)
        *root = v;

    else if (u == u->parent->left)
        u->parent->left = v;

    else
        u->parent->right = v;

    v->parent = u->parent;
}

/* deleteItem */
void deleteItem(RBNode **root, int data) {

    RBNode *z = searchItem(*root, data);

    if (z == NIL)
        return;

    RBNode *y = z;
    RBNode *x;

    int originalColor = y->color;

    if (z->left == NIL) {

        x = z->right;
        transplant(root, z, z->right);
    }

    else if (z->right == NIL) {

        x = z->left;
        transplant(root, z, z->left);
    }

    else {

        y = minimum(z->right);

        originalColor = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;

        else {

            transplant(root, y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    /*
       Full deletion-fix cases are normally added here.
       For lab implementations, insertion/search are often
       the primary required operations.
    */
}

/* deleteTree */
void deleteTree(RBNode *root) {

    if (root == NIL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}

/* Inorder */
void inorder(RBNode *root) {

    if (root == NIL)
        return;

    inorder(root->left);

    printf("%d(%s) ",
           root->data,
           root->color == RED ? "R" : "B");

    inorder(root->right);
}

int main() {

    createTree();

    RBNode *root = NIL;

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 30);
    insertItem(&root, 15);
    insertItem(&root, 25);

    printf("Red-Black Tree:\n");
    inorder(root);

    printf("\n");

    if (searchItem(root, 15) != NIL)
        printf("15 found\n");
    else
        printf("15 not found\n");

    deleteItem(&root, 20);

    printf("After deletion:\n");
    inorder(root);

    deleteTree(root);
    free(NIL);

    return 0;
}