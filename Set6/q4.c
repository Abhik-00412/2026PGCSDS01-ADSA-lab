//0-1 Knapsack using Backtracking   
#include <stdio.h>

#define MAX 100

int n, W;
int weight[MAX], value[MAX];
int maxProfit = 0;

void knapsack(int i, int currentWeight, int currentProfit) {
    if (i == n) {
        if (currentProfit > maxProfit)
            maxProfit = currentProfit;
        return;
    }

    if (currentWeight + weight[i] <= W)
        knapsack(i + 1,
                 currentWeight + weight[i],
                 currentProfit + value[i]);

    knapsack(i + 1, currentWeight, currentProfit);
}

int main() {
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &value[i]);

    scanf("%d", &W);

    knapsack(0, 0, 0);

    printf("%d\n", maxProfit);

    return 0;
}