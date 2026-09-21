//B Tree
#include <stdio.h>
#include <stdlib.h>

#define T 3

typedef struct BTreeNode {
    int keys[2*T-1];
    struct BTreeNode *child[2*T];

    int n;
    int leaf;
} BTreeNode;

/* Create node */
BTreeNode* createNode(int leaf) {

    BTreeNode *node =
        (BTreeNode*)malloc(sizeof(BTreeNode));

    node->leaf = leaf;
    node->n = 0;

    return node;
}

/* createTree */
BTreeNode* createTree() {
    return createNode(1);
}

/* Search */
BTreeNode* searchItem(BTreeNode *root, int key) {

    int i = 0;

    while (i < root->n && key > root->keys[i])
        i++;

    if (i < root->n && key == root->keys[i])
        return root;

    if (root->leaf)
        return NULL;

    return searchItem(root->child[i], key);
}

/* Split child */
void splitChild(BTreeNode *parent,
                int i,
                BTreeNode *full) {

    BTreeNode *newNode =
        createNode(full->leaf);

    newNode->n = T - 1;

    for (int j = 0; j < T-1; j++)
        newNode->keys[j] = full->keys[j+T];

    if (!full->leaf) {

        for (int j = 0; j < T; j++)
            newNode->child[j] =
                full->child[j+T];
    }

    full->n = T - 1;

    for (int j = parent->n; j >= i+1; j--)
        parent->child[j+1] = parent->child[j];

    parent->child[i+1] = newNode;

    for (int j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    parent->keys[i] = full->keys[T-1];

    parent->n++;
}

/* Insert into non-full node */
void insertNonFull(BTreeNode *node, int key) {

    int i = node->n - 1;

    if (node->leaf) {

        while (i >= 0 && key < node->keys[i]) {

            node->keys[i+1] =
                node->keys[i];

            i--;
        }

        node->keys[i+1] = key;
        node->n++;
    }

    else {

        while (i >= 0 && key < node->keys[i])
            i--;

        i++;

        if (node->child[i]->n == 2*T-1) {

            splitChild(node, i, node->child[i]);

            if (key > node->keys[i])
                i++;
        }

        insertNonFull(node->child[i], key);
    }
}

/* insertItem */
void insertItem(BTreeNode **root, int key) {

    BTreeNode *r = *root;

    if (r->n == 2*T-1) {

        BTreeNode *s =
            createNode(0);

        *root = s;

        s->child[0] = r;

        splitChild(s, 0, r);

        int i = 0;

        if (key > s->keys[0])
            i++;

        insertNonFull(s->child[i], key);
    }

    else {
        insertNonFull(r, key);
    }
}

/* Simple deletion */
void deleteItem(BTreeNode *root, int key) {

    if (root == NULL)
        return;

    int i = 0;

    while (i < root->n && key > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == key) {

        if (root->leaf) {

            for (int j = i; j < root->n-1; j++)
                root->keys[j] = root->keys[j+1];

            root->n--;
        }

        return;
    }

    if (!root->leaf)
        deleteItem(root->child[i], key);
}

/* deleteTree */
void deleteTree(BTreeNode *root) {

    if (root == NULL)
        return;

    if (!root->leaf) {

        for (int i = 0; i <= root->n; i++)
            deleteTree(root->child[i]);
    }

    free(root);
}

/* Display */
void traverse(BTreeNode *root) {

    if (root == NULL)
        return;

    int i;

    for (i = 0; i < root->n; i++) {

        if (!root->leaf)
            traverse(root->child[i]);

        printf("%d ", root->keys[i]);
    }

    if (!root->leaf)
        traverse(root->child[i]);
}

int main() {

    BTreeNode *root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 5);
    insertItem(&root, 6);
    insertItem(&root, 12);
    insertItem(&root, 30);
    insertItem(&root, 7);
    insertItem(&root, 17);

    printf("B Tree: ");
    traverse(root);

    printf("\n");

    if (searchItem(root, 12))
        printf("12 found\n");
    else
        printf("12 not found\n");

    deleteItem(root, 12);

    printf("After deletion: ");
    traverse(root);

    deleteTree(root);

    return 0;
}