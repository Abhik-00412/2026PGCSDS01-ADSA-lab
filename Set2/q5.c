//quick sort
#include <stdio.h>

void quickSort(int a[], int low, int high) {
    int i = low, j = high, pivot, temp;

    if (low >= high)
        return;

    pivot = a[(low + high) / 2];

    while (i <= j) {
        while (a[i] < pivot)
            i++;

        while (a[j] > pivot)
            j--;

        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (low < j)
        quickSort(a, low, j);

    if (i < high)
        quickSort(a, i, high);
}

int main() {
    int a[100], n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    quickSort(a, 0, n - 1);

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}