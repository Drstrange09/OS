#include <stdio.h>

int main() {
    int n, m;

    // Input the number of processes and resource types
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resource types: ");
    scanf("%d", &m);

    // Declare matrices and arrays
    int allocation[n][m];   // Allocation matrix: currently allocated resources for each process
    int max[n][m];          // Maximum demand matrix: max resources each process may need
    int available[m];       // Available array: available instances of each resource type
    int need[n][m];         // Need matrix: remaining resource needs of each process (max - allocation)
    int finish[n];          // Finish array: to track whether a process has completed
    int safeSequence[n];    // Safe sequence array: stores the order of process execution
    int count = 0;          // Counter to track how many processes have been safely executed

    // Input the allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input the maximum demand matrix and calculate the need matrix
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

    // Banker's Algorithm: determine if the system is in a safe state
    while (count < n) {
        int found = 0;  // Flag to track if any process could be safely executed in this iteration

        // Loop through each process to find a safe one
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {  // If the process is not finished
                int j;

                // Check if all resource needs of the process can be satisfied with current available resources
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        break;  // Need cannot be satisfied, break inner loop
                    }
                }

                // If all needs of the process are less than or equal to available
                if (j == m) {
                    // Add the process’s allocated resources back to the available pool
                    for (int k = 0; k < m; k++) {
                        available[k] += allocation[i][k];
                    }

                    // Add process to the safe sequence
                    safeSequence[count++] = i;
                    finish[i] = 1;  // Mark this process as finished
                    found = 1;      // At least one process was safely executed
                }
            }
        }

        // If no process could be safely executed, system is in an unsafe state
        if (!found) {
            printf("System is in an unsafe state. Deadlock may occur.\n");
            return 0;
        }
    }

    // If all processes could finish safely, print the safe sequence
    printf("System is in a safe state. Safe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return 0;
}
