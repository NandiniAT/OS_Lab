#include <stdio.h>

int main() {
    int n, m;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    int available[m];
    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    int maximum[n][m];
    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }
    int allocation[n][m];
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }
    printf(" Process   Allocation   Max   Need          \n");

    // Print the table data
    for (int i = 0; i < n; i++) {
        printf("| P%d      | ", i + 1);
        for (int j = 0; j < m; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("| ");
        for (int j = 0; j < m; j++) {
            printf("%d ", maximum[i][j]);
        }
        printf("| ");
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("|\n");
    }

    int work[m];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    int finish[n];
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    int safeSequence[n];
    int count = 0;
    int safe = 1;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }

                if (j == m) {
                    for (j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    safeSequence[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            safe = 0;
            break;
        }
    }
    if (safe) {
        printf("The system is in a safe state.\n");
        printf("Safety sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSequence[i] + 1);
        }
        printf("\n");
    } else {
        printf("The system is in an unsafe state and might lead to deadlock.\n");
    }
    return 0;
}
