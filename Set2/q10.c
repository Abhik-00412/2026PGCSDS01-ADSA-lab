//Bucket sort
#include <stdio.h>

void insertionSort(float a[], int n) {
    int i, j;
    float key;

    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

void bucketSort(float a[], int n) {
    float bucket[10][100];
    int count[10] = {0};
    int i, j, k = 0, index;

    for (i = 0; i < n; i++) {
        index = (int)(a[i] * 10);

        if (index == 10)
            index = 9;

        bucket[index][count[index]++] = a[i];
    }

    for (i = 0; i < 10; i++)
        insertionSort(bucket[i], count[i]);

    for (i = 0; i < 10; i++)
        for (j = 0; j < count[i]; j++)
            a[k++] = bucket[i][j];
}

int main() {
    float a[100];
    int n, i;

    scanf("%d", &n);

    for (i = 0; i < n; i++)
        scanf("%f", &a[i]);

    bucketSort(a, n);

    for (i = 0; i < n; i++)
        printf("%.2f ", a[i]);

    return 0;
}