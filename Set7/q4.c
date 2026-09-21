//scc
#include <stdio.h>

#define MAX 100

/* ---------- DIRECTED GRAPH FOR SCC ---------- */

int dg[MAX][MAX];
int n;

int disc[MAX], low[MAX], stack[MAX];
int onStack[MAX];
int top = -1;
int timer = 0;

void SCCUtil(int u) {
    int v;

    disc[u] = low[u] = ++timer;

    stack[++top] = u;
    onStack[u] = 1;

    for (v = 0; v < n; v++) {

        if (dg[u][v]) {

            if (disc[v] == 0) {
                SCCUtil(v);

                if (low[v] < low[u])
                    low[u] = low[v];
            }
            else if (onStack[v]) {
                if (disc[v] < low[u])
                    low[u] = disc[v];
            }
        }
    }

    if (low[u] == disc[u]) {

        printf("{ ");

        do {
            v = stack[top--];
            onStack[v] = 0;
            printf("%d ", v);
        } while (v != u);

        printf("}\n");
    }
}

void findSCC() {
    int i;

    for (i = 0; i < n; i++) {
        disc[i] = 0;
        low[i] = 0;
        onStack[i] = 0;
    }

    top = -1;
    timer = 0;

    printf("\nStrongly Connected Components:\n");

    for (i = 0; i < n; i++) {
        if (disc[i] == 0)
            SCCUtil(i);
    }
}


/* ---------- UNDIRECTED GRAPH ---------- */

int ug[MAX][MAX];

int dfsTime[MAX];
int lowTime[MAX];
int parent[MAX];
int visited[MAX];

int articulation[MAX];

void APBridgeUtil(int u) {
    int v;
    int children = 0;

    visited[u] = 1;
    dfsTime[u] = lowTime[u] = ++timer;

    for (v = 0; v < n; v++) {

        if (!ug[u][v])
            continue;

        if (!visited[v]) {

            children++;
            parent[v] = u;

            APBridgeUtil(v);

            if (lowTime[v] < lowTime[u])
                lowTime[u] = lowTime[v];

            /* Articulation point */

            if (parent[u] == -1 && children > 1)
                articulation[u] = 1;

            if (parent[u] != -1 &&
                lowTime[v] >= dfsTime[u])
                articulation[u] = 1;

            /* Bridge */

            if (lowTime[v] > dfsTime[u])
                printf("Bridge: %d - %d\n", u, v);
        }

        else if (v != parent[u]) {

            if (dfsTime[v] < lowTime[u])
                lowTime[u] = dfsTime[v];
        }
    }
}

void findAPBridges() {
    int i;

    timer = 0;

    for (i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        articulation[i] = 0;
    }

    printf("\nBridges:\n");

    for (i = 0; i < n; i++) {
        if (!visited[i])
            APBridgeUtil(i);
    }

    printf("\nArticulation Points:\n");

    for (i = 0; i < n; i++) {
        if (articulation[i])
            printf("%d ", i);
    }

    printf("\n");
}


/* ---------- BICONNECTED COMPONENTS ---------- */

typedef struct {
    int u, v;
} Edge;

Edge edgeStack[MAX * MAX];
int edgeTop = -1;

int disc2[MAX], low2[MAX];
int time2 = 0;

void printBCC(int u, int v) {
    Edge e;

    printf("{ ");

    while (edgeTop >= 0) {

        e = edgeStack[edgeTop--];

        printf("(%d,%d) ", e.u, e.v);

        if (e.u == u && e.v == v)
            break;
    }

    printf("}\n");
}

void BCCUtil(int u) {
    int v;
    int children = 0;

    disc2[u] = low2[u] = ++time2;

    for (v = 0; v < n; v++) {

        if (!ug[u][v])
            continue;

        if (disc2[v] == 0) {

            children++;

            edgeStack[++edgeTop].u = u;
            edgeStack[edgeTop].v = v;

            BCCUtil(v);

            if (low2[v] < low2[u])
                low2[u] = low2[v];

            if (low2[v] >= disc2[u])
                printBCC(u, v);
        }

        else if (disc2[v] < disc2[u]) {

            edgeStack[++edgeTop].u = u;
            edgeStack[edgeTop].v = v;

            if (disc2[v] < low2[u])
                low2[u] = disc2[v];
        }
    }
}

void findBCC() {
    int i;

    for (i = 0; i < n; i++)
        disc2[i] = 0;

    edgeTop = -1;
    time2 = 0;

    printf("\nBiconnected Components:\n");

    for (i = 0; i < n; i++) {
        if (disc2[i] == 0)
            BCCUtil(i);
    }
}


/* ---------- MAIN ---------- */

int main() {
    int i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("\nEnter directed graph adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &dg[i][j]);

    findSCC();

    printf("\nEnter undirected graph adjacency matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &ug[i][j]);

    findAPBridges();
    findBCC();

    return 0;
}