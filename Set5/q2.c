//Prims Algorithm
#include <stdio.h>
#define V 5
#define INF 99999

int minKey(int key[], int mst[]) {
    int min = INF, index = -1;

    for (int i = 0; i < V; i++) {
        if (!mst[i] && key[i] < min) {
            min = key[i];
            index = i;
        }
    }
    return index;
}

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    int mst[V];

    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mst[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mst);
        mst[u] = 1;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mst[v] &&
                graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edge\tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
}

int main() {
    int graph[V][V] = {
        {0,2,0,6,0},
        {2,0,3,8,5},
        {0,3,0,0,7},
        {6,8,0,0,9},
        {0,5,7,9,0}
    };

    primMST(graph);
    return 0;
}