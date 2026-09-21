//Graph coloring using backtracking
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int color[MAX];
int n, m;

int isSafe(int v, int c) {
    int i;

    for (i = 0; i < n; i++) {
        if (graph[v][i] && color[i] == c)
            return 0;
    }

    return 1;
}

int graphColoring(int v) {
    int c;

    if (v == n)
        return 1;

    for (c = 1; c <= m; c++) {

        if (isSafe(v, c)) {
            color[v] = c;

            if (graphColoring(v + 1))
                return 1;

            color[v] = 0;
        }
    }

    return 0;
}

int main() {
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter number of colors: ");
    scanf("%d", &m);

    for (i = 0; i < n; i++)
        color[i] = 0;

    if (graphColoring(0)) {
        printf("\nGraph can be colored using %d colors.\n", m);

        for (i = 0; i < n; i++)
            printf("Vertex %d -> Color %d\n", i + 1, color[i]);
    }
    else {
        printf("\nGraph cannot be colored using %d colors.\n", m);
    }

    return 0;
}