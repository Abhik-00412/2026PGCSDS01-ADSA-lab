//Smallest and Largest cycle in graph
#include <stdio.h>

#define V 6

int graph[V][V];
int visited[V];

int smallest = 99999;
int largest = -1;

void dfs(int start, int current, int depth, int parent) {

    visited[current] = 1;

    for (int next = 0; next < V; next++) {

        if (!graph[current][next])
            continue;

        if (!visited[next]) {
            dfs(start, next, depth + 1, current);
        }

        else if (next == start && next != parent && depth >= 2) {

            int cycleLength = depth + 1;

            if (cycleLength < smallest)
                smallest = cycleLength;

            if (cycleLength > largest)
                largest = cycleLength;
        }
    }

    visited[current] = 0;
}

void findCycles() {

    for (int i = 0; i < V; i++) {
        dfs(i, i, 0, -1);
    }

    if (largest == -1) {
        printf("No cycle found.\n");
    } else {
        printf("Smallest Cycle Length = %d\n", smallest);
        printf("Largest Cycle Length = %d\n", largest);
    }
}

int main() {

    graph[0][1] = graph[1][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][0] = graph[0][2] = 1;

    graph[2][3] = graph[3][2] = 1;
    graph[3][4] = graph[4][3] = 1;
    graph[4][5] = graph[5][4] = 1;
    graph[5][2] = graph[2][5] = 1;

    findCycles();

    return 0;
}