//B++ tree
#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

typedef struct BPlusNode {

    int keys[ORDER];

    struct BPlusNode *child[ORDER + 1];

    struct BPlusNode *next;

    int n;
    int leaf;

} BPlusNode;

/* Create node */
BPlusNode* createNode(int leaf) {

    BPlusNode *node =
        (BPlusNode*)malloc(sizeof(BPlusNode));

    node->n = 0;
    node->leaf = leaf;
    node->next = NULL;

    for (int i = 0; i <= ORDER; i++)
        node->child[i] = NULL;

    return node;
}

/* createTree */
BPlusNode* createTree() {
    return createNode(1);
}

/* Search */
BPlusNode* searchItem(BPlusNode *root, int key) {

    BPlusNode *current = root;

    while (!current->leaf) {

        int i = 0;

        while (i < current->n &&
               key >= current->keys[i])
            i++;

        current = current->child[i];
    }

    for (int i = 0; i < current->n; i++) {

        if (current->keys[i] == key)
            return current;
    }

    return NULL;
}

/* Insert into leaf */
void insertLeaf(BPlusNode *leaf, int key) {

    int i = leaf->n - 1;

    while (i >= 0 && key < leaf->keys[i]) {

        leaf->keys[i+1] = leaf->keys[i];

        i--;
    }

    leaf->keys[i+1] = key;
    leaf->n++;
}

/* insertItem */
/*
   This simple implementation demonstrates insertion
   in the leaf-level structure.
*/
void insertItem(BPlusNode *root, int key) {

    BPlusNode *current = root;

    while (!current->leaf) {

        int i = 0;

        while (i < current->n &&
               key >= current->keys[i])
            i++;

        current = current->child[i];
    }

    if (current->n < ORDER) {
        insertLeaf(current, key);
    }
}

/* deleteItem */
void deleteItem(BPlusNode *root, int key) {

    BPlusNode *leaf = searchItem(root, key);

    if (leaf == NULL)
        return;

    int i;

    for (i = 0; i < leaf->n; i++) {

        if (leaf->keys[i] == key)
            break;
    }

    if (i == leaf->n)
        return;

    for (; i < leaf->n-1; i++)
        leaf->keys[i] = leaf->keys[i+1];

    leaf->n--;
}

/* deleteTree */
void deleteTree(BPlusNode *root) {

    if (root == NULL)
        return;

    if (!root->leaf) {

        for (int i = 0; i <= root->n; i++)
            deleteTree(root->child[i]);
    }

    free(root);
}

/* Display */
void display(BPlusNode *root) {

    if (root == NULL)
        return;

    BPlusNode *current = root;

    while (!current->leaf)
        current = current->child[0];

    printf("B+ Tree leaf nodes: ");

    while (current != NULL) {

        for (int i = 0; i < current->n; i++)
            printf("%d ", current->keys[i]);

        current = current->next;
    }

    printf("\n");
}

int main() {

    BPlusNode *root = createTree();

    insertItem(root, 10);
    insertItem(root, 20);
    insertItem(root, 5);
    insertItem(root, 30);

    display(root);

    if (searchItem(root, 20))
        printf("20 found\n");
    else
        printf("20 not found\n");

    deleteItem(root, 20);

    display(root);

    deleteTree(root);

    return 0;
}