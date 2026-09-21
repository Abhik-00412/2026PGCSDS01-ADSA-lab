//Kruskals algorithm
#include <stdio.h>
#include <stdlib.h>

#define V 4
#define E 5

struct Edge {
    int src, dest, weight;
};

int parent[V];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int a, int b) {
    parent[find(a)] = find(b);
}

int compare(const void *a, const void *b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void kruskal(struct Edge edges[]) {

    qsort(edges, E, sizeof(struct Edge), compare);

    for (int i = 0; i < V; i++)
        parent[i] = i;

    printf("Edges in MST:\n");

    for (int i = 0, count = 0; count < V - 1 && i < E; i++) {

        int x = find(edges[i].src);
        int y = find(edges[i].dest);

        if (x != y) {
            printf("%d -- %d == %d\n",
                   edges[i].src,
                   edges[i].dest,
                   edges[i].weight);

            unionSet(x, y);
            count++;
        }
    }
}

int main() {

    struct Edge edges[E] = {
        {0,1,10},
        {0,2,6},
        {0,3,5},
        {1,3,15},
        {2,3,4}
    };

    kruskal(edges);

    return 0;
}