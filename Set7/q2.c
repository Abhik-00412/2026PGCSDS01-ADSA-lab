//Job sequencing
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

void sortJobs(Job jobs[], int n) {
    int i, j;
    Job temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (jobs[j].profit < jobs[j + 1].profit) {
                temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}

void jobSequencing(Job jobs[], int n) {
    int i, j;
    int maxDeadline = 0;
    int totalProfit = 0;

    for (i = 0; i < n; i++) {
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;
    }

    char slot[maxDeadline + 1];

    for (i = 0; i <= maxDeadline; i++)
        slot[i] = '-';

    sortJobs(jobs, n);

    for (i = 0; i < n; i++) {
        for (j = jobs[i].deadline; j >= 1; j--) {
            if (slot[j] == '-') {
                slot[j] = jobs[i].id;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("\nJob sequence:\n");

    for (i = 1; i <= maxDeadline; i++) {
        if (slot[i] != '-')
            printf("Slot %d : Job %c\n", i, slot[i]);
    }

    printf("\nMaximum Profit = %d\n", totalProfit);
}

int main() {
    int n, i;
    Job jobs[100];

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter Job ID, Deadline and Profit for job %d: ", i + 1);
        scanf(" %c %d %d",
              &jobs[i].id,
              &jobs[i].deadline,
              &jobs[i].profit);
    }

    jobSequencing(jobs, n);

    return 0;
}