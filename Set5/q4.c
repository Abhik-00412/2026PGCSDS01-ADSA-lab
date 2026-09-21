//DFS for graphs
#include <stdio.h>

#define V 6

int graph[V][V];
int color[V];
int discover[V], finish[V];
int timer = 0;

void dfsVisit(int u) {
    color[u] = 1;
    discover[u] = ++timer;

    printf("Visit %d\n", u);

    for (int v = 0; v < V; v++) {

        if (!graph[u][v])
            continue;

        if (color[v] == 0) {
            printf("Tree Edge: %d -> %d\n", u, v);
            dfsVisit(v);
        }

        else if (color[v] == 1) {
            printf("Back Edge: %d -> %d\n", u, v);
        }

        else {

            if (discover[u] < discover[v])
                printf("Forward Edge: %d -> %d\n", u, v);

            else
                printf("Cross Edge: %d -> %d\n", u, v);
        }
    }

    color[u] = 2;
    finish[u] = ++timer;
}

void DFS() {
    for (int i = 0; i < V; i++)
        color[i] = 0;

    for (int i = 0; i < V; i++) {
        if (!color[i])
            dfsVisit(i);
    }
}

int main() {

    graph[0][1] = 1;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[2][3] = 1;
    graph[3][4] = 1;
    graph[4][1] = 1;
    graph[2][5] = 1;

    DFS();

    return 0;
}