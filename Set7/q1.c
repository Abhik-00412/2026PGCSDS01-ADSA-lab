//Coin change
#include <stdio.h>

int main() {
    int coins[] = {2000, 500, 200, 100, 50, 20, 10, 5, 2, 1};
    int n = sizeof(coins) / sizeof(coins[0]);

    int amount, i, count, totalCoins = 0;

    printf("Enter amount: ");
    scanf("%d", &amount);

    printf("\nCoins used:\n");

    for (i = 0; i < n; i++) {
        count = amount / coins[i];

        if (count > 0) {
            printf("%d x %d\n", coins[i], count);
            totalCoins += count;
            amount %= coins[i];
        }
    }

    printf("\nMinimum number of coins = %d\n", totalCoins);

    return 0;
}