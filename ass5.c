#include <stdio.h>

int main() {
    int n, m;

    // Input the number of processes and resource types
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    // Declare matrices and arrays
    int allocation[n][m];   // Allocation matrix
    int max[n][m];          // Maximum demand matrix
    int available[m];       // Available resources array
    int need[n][m];         // Need matrix (max - allocation)
    int finish[n];          // To track if a process is finished
    int safeSequence[n];    // To store the safe sequence
    int count = 0;          // Counter for number of processes in the safe sequence

    // Input the allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input the maximum matrix and calculate the need matrix
    printf("Enter the maximum matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];  // Need = Max - Allocation
        }
    }

    // Input the available resources
    printf("Enter the available resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Initialize all processes as not finished
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Banker's Algorithm: Check for a safe sequence
    while (count < n) {
        int found = 0;

        // Iterate through all processes
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {  // If process is not yet finished
                int j;

                // Check if resources can be allocated to process i
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        break;  // Cannot allocate, move to next process
                    }
                }

                // If all needs of process i can be satisfied
                if (j == m) {
                    // Add allocated resources of this process back to available
                    for (int k = 0; k < m; k++) {
                        available[k] += allocation[i][k];
                    }

                    // Add process to safe sequence
                    safeSequence[count++] = i;
                    finish[i] = 1;  // Mark process as finished
                    found = 1;      // Set found flag
                }
            }
        }

        // If no process was able to execute in this iteration, deadlock may occur
        if (!found) {
            printf("System is in an unsafe state. Deadlock may occur.\n");
            return 0;
        }
    }

    // If system is in safe state, print the safe sequence
    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
