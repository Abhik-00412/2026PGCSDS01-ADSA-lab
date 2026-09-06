//Merge sort no recursion and no stack
#include <stdio.h>

void merge(int a[], int low, int mid, int high) {
    int temp[100], i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= mid)
        temp[k++] = a[i++];

    while (j <= high)
        temp[k++] = a[j++];

    for (i = low; i <= high; i++)
        a[i] = temp[i];
}

int main() {
    int a[100], n, i, size, low, mid, high;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for (size = 1; size < n; size *= 2) {
        for (low = 0; low < n - size; low += 2 * size) {
            mid = low + size - 1;
            high = low + 2 * size - 1;

            if (high >= n)
                high = n - 1;

            merge(a, low, mid, high);
        }
    }

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}