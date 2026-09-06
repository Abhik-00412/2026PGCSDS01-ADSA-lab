//Radix exchange sort
#include <stdio.h>

void radixExchange(int a[], int left, int right, int bit) {
    int i, j, temp;

    if (left >= right || bit < 0)
        return;

    i = left;
    j = right;

    while (i <= j) {
        while (i <= j && !(a[i] & (1 << bit)))
            i++;

        while (i <= j && (a[j] & (1 << bit)))
            j--;

        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    radixExchange(a, left, j, bit - 1);
    radixExchange(a, i, right, bit - 1);
}

int main() {
    int a[100], n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    radixExchange(a, 0, n - 1, 30);

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}