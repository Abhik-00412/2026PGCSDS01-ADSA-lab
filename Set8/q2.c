//Hamiltonian Cycle
#include <stdio.h>

#define MAX 50

int graph[MAX][MAX];
int path[MAX];
int visited[MAX];
int n, e;

/* Check whether vertex v can be added */
int isSafe(int v, int pos) {
    int i;

    /* Must be connected to previous vertex */
    if (!graph[path[pos - 1]][v])
        return 0;

    /* Vertex must not already be present */
    if (visited[v])
        return 0;

    return 1;
}

/* Backtracking function */
int hamiltonianCycle(int pos) {
    int v;

    /* All vertices included */
    if (pos == n) {

        /* Check edge from last vertex to first */
        if (graph[path[n - 1]][path[0]])
            return 1;

        return 0;
    }

    for (v = 1; v < n; v++) {

        if (isSafe(v, pos)) {

            path[pos] = v;
            visited[v] = 1;

            if (hamiltonianCycle(pos + 1))
                return 1;

            /* Backtrack */
            visited[v] = 0;
            path[pos] = -1;
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

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        path[i] = -1;
    }

    /* Start from vertex 0 */
    path[0] = 0;
    visited[0] = 1;

    if (hamiltonianCycle(1)) {

        printf("\nHamiltonian Cycle exists.\n");

        for (i = 0; i < n; i++)
            printf("%d -> ", path[i]);

        printf("%d\n", path[0]);
    }
    else {
        printf("\nHamiltonian Cycle does not exist.\n");
    }

    return 0;
}