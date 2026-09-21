//TSP
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

int cost[MAX][MAX];
int visited[MAX];

int tspNearestNeighbor(int n, int start) {
    int current = start;
    int totalCost = 0;
    int count, next, minCost;

    for (count = 0; count < n; count++)
        visited[count] = 0;

    visited[start] = 1;

    for (count = 1; count < n; count++) {

        minCost = 1000000;
        next = -1;

        for (int j = 0; j < n; j++) {

            if (!visited[j] &&
                cost[current][j] < minCost) {

                minCost = cost[current][j];
                next = j;
            }
        }

        if (next != -1) {
            totalCost += minCost;
            visited[next] = 1;
            current = next;
        }
    }

    /* Return to starting city */
    totalCost += cost[current][start];

    return totalCost;
}

void generateGraph(int n) {
    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {

            if (i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = rand() % 100 + 1;
        }
    }
}

int main() {
    int sizes[] = {10, 20, 40, 60, 100};
    int numberOfSizes = 5;

    int i, n, result;
    clock_t start, end;
    double timeTaken;

    srand(time(NULL));

    printf("TSP Running Time\n");
    printf("-------------------------------\n");
    printf("Nodes\tTime (seconds)\n");
    printf("-------------------------------\n");

    for (i = 0; i < numberOfSizes; i++) {

        n = sizes[i];

        generateGraph(n);

        start = clock();

        result = tspNearestNeighbor(n, 0);

        end = clock();

        timeTaken =
            ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("%d\t%f\n", n, timeTaken);
    }

    return 0;
}