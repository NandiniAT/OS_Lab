#include <stdio.h>
#define MAX 10
void sjf_preemptive(int n, int at[], int bt[]) {
    int ct[MAX];
    int tat[MAX];
    int wt[MAX];
    int rt[MAX];
    int total_wt = 0;
    int total_tat = 0;
    int completed = 0;
    int current_time = 0;
    int is_completed[MAX] = {0};

    for (int i = 0; i < n; i++) {
        rt[i] = bt[i];
    }

    while (completed < n) {
        int shortest_job = -1;
        int min_bt = 9999;

        for (int i = 0; i < n; i++) {
            if (at[i] <= current_time && rt[i] < min_bt && rt[i] > 0) {
                shortest_job = i;
                min_bt = rt[i];
            }
        }

        if (shortest_job == -1) {
            current_time++;
            continue;
        }

        rt[shortest_job]--;

        if (rt[shortest_job] == 0) {
            completed++;

            ct[shortest_job] = current_time + 1;

            tat[shortest_job] = ct[shortest_job] - at[shortest_job];
            total_tat += tat[shortest_job];

            wt[shortest_job] = tat[shortest_job] - bt[shortest_job];
            if (wt[shortest_job] < 0) wt[shortest_job] = 0;
            total_wt += wt[shortest_job];

            is_completed[shortest_job] = 1;
        }

        current_time++;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage waiting time: %.2f", (float)total_wt / n);
    printf("\nAverage turnaround time: %.2f", (float)total_tat / n);
}

int main() {
    int n, i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n];

    printf("Enter the arrival time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }

    printf("Enter the burst time:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    sjf_preemptive(n, at, bt);

    return 0;
}
