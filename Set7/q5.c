//Topo sort
#include <stdio.h>

#define MAX 100

int graph[MAX][MAX];
int visited[MAX];
int stack[MAX];
int top = -1;
int n;

void DFS(int v) {
    int i;

    visited[v] = 1;

    for (i = 0; i < n; i++) {

        if (graph[v][i] && !visited[i])
            DFS(i);
    }

    stack[++top] = v;
}

void topologicalSort() {
    int i;

    for (i = 0; i < n; i++)
        visited[i] = 0;

    top = -1;

    for (i = 0; i < n; i++) {
        if (!visited[i])
            DFS(i);
    }

    printf("\nTopological Order:\n");

    while (top >= 0)
        printf("%d ", stack[top--]);

    printf("\n");
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

    topologicalSort();

    return 0;
}