//Merge sort without recursion
#include <stdio.h>

typedef struct {
    int low;
    int high;
} Range;

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
    int a[100], n, i;
    Range stack[100];
    int top = -1;
    Range r;
    int mid;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    stack[++top].low = 0;
    stack[top].high = n - 1;

    while (top >= 0) {
        r = stack[top--];

        if (r.low < r.high) {
            mid = (r.low + r.high) / 2;

            stack[++top].low = mid + 1;
            stack[top].high = r.high;

            stack[++top].low = r.low;
            stack[top].high = mid;
        }
    }

    for (int size = 1; size < n; size *= 2) {
        for (int low = 0; low < n - size; low += 2 * size) {
            int mid = low + size - 1;
            int high = low + 2 * size - 1;

            if (high >= n)
                high = n - 1;

            merge(a, low, mid, high);
        }
    }

    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}