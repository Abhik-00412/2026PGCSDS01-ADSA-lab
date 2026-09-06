//Counting sort
#include <stdio.h>

int main() {
    int a[100], count[1000] = {0};
    int n, i, j, max = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > max)
            max = a[i];
    }

    for (i = 0; i < n; i++)
        count[a[i]]++;

    for (i = 0; i <= max; i++) {
        for (j = 0; j < count[i]; j++)
            printf("%d ", i);
    }

    return 0;
}