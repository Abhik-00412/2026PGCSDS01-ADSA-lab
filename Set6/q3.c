//0-1 Knapsack using Dynamic Programming
#include <stdio.h>

#define MAX 100

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int n, W;
    int weight[MAX], value[MAX];
    int dp[MAX + 1][MAX + 1];

    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        scanf("%d", &weight[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &value[i]);

    scanf("%d", &W);

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weight[i - 1] <= w)
                dp[i][w] = max(value[i - 1] + dp[i - 1][w - weight[i - 1]],
                               dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    printf("%d\n", dp[n][W]);

    return 0;
}