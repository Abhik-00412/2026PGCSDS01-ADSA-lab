//Clique
#include <stdio.h>

#define MAX 50

int graph[MAX][MAX];
int n, e, m;
int selected[MAX];

/* Check whether vertex v can be added */
int isSafe(int v, int pos) {
    int i;

    for (i = 0; i < pos; i++) {
        if (!graph[v][selected[i]])
            return 0;
    }

    return 1;
}

/* Backtracking function */
int findClique(int pos, int start) {
    int v;

    /* Clique of required size found */
    if (pos == m)
        return 1;

    for (v = start; v < n; v++) {

        if (isSafe(v, pos)) {

            selected[pos] = v;

            if (findClique(pos + 1, v + 1))
                return 1;
        }
    }

    return 0;
}

int main() {
    int i, j;

    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    printf("Enter size of clique (m): ");
    scanf("%d", &m);

    if (m > n) {
        printf("Clique size cannot be greater than n.\n");
        return 0;
    }

    /* Initialize graph */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v):\n", e);

    for (i = 0; i < e; i++) {
        int u, v;

        scanf("%d %d", &u, &v);

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    if (findClique(0, 0)) {

        printf("\nClique of size %d exists.\n", m);

        printf("Clique vertices: ");

        for (i = 0; i < m; i++)
            printf("%d ", selected[i]);

        printf("\n");
    }
    else {
        printf("\nClique of size %d does not exist.\n", m);
    }

    return 0;
}