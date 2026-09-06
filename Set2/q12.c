//Address calculation sort
#include <stdio.h>

int main() {
    int a[100], table[1000];
    int n, i, j, address, max = 1000;

    for (i = 0; i < max; i++)
        table[i] = -1;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        address = a[i] % max;

        while (table[address] != -1)
            address = (address + 1) % max;

        table[address] = a[i];
    }

    for (i = 0; i < max; i++) {
        if (table[i] != -1)
            printf("%d ", table[i]);
    }

    return 0;
}