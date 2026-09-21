//Check if graph is bipartite
#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int color[MAX];
int queue[MAX];

int n, e;

/* BFS to check bipartiteness */
int isBipartite() {
    int i, j;
    int front, rear;
    int u, v;

    /* -1 means not colored */
    for (i = 0; i < n; i++)
        color[i] = -1;

    /* Check every component */
    for (i = 0; i < n; i++) {

        if (color[i] != -1)
            continue;

        front = 0;
        rear = 0;

        queue[rear++] = i;
        color[i] = 0;

        while (front < rear) {

            u = queue[front++];

            for (v = 0; v < n; v++) {

                if (graph[u][v]) {

                    /* Uncolored vertex */
                    if (color[v] == -1) {

                        color[v] = 1 - color[u];
                        queue[rear++] = v;
                    }

                    /* Same color on adjacent vertices */
                    else if (color[v] == color[u]) {
                        return 0;
                    }
                }
            }
        }
    }

    return 1;
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

    if (isBipartite()) {

        printf("\nGraph is Bipartite.\n");

        printf("\nSet 1: ");
        for (i = 0; i < n; i++) {
            if (color[i] == 0)
                printf("%d ", i);
        }

        printf("\nSet 2: ");
        for (i = 0; i < n; i++) {
            if (color[i] == 1)
                printf("%d ", i);
        }

        printf("\n");
    }
    else {
        printf("\nGraph is NOT Bipartite.\n");
    }

    return 0;
}