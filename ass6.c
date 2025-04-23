#include <stdio.h>

// Function to implement First Fit memory allocation strategy
void firstFit(int blocks[], int m, int processes[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (meaning not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Try to allocate each process
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= processes[i]) {
                allocation[i] = j;          // Allocate block j to process i
                blocks[j] -= processes[i];  // Reduce block size
                break;                      // Move to next process
            }
        }
    }

    // Print allocation result
    printf("First Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

// Function to implement Best Fit memory allocation strategy
void bestFit(int blocks[], int m, int processes[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (meaning not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Try to allocate each process to the best (smallest sufficient) block
    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= processes[i]) {
                if (bestIndex == -1 || blocks[j] < blocks[bestIndex]) {
                    bestIndex = j; // Select the better (smaller) block
                }
            }
        }

        // If a block was found, allocate it
        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blocks[bestIndex] -= processes[i];
        }
    }

    // Print allocation result
    printf("Best Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

// Function to implement Worst Fit memory allocation strategy
void worstFit(int blocks[], int m, int processes[], int n) {
    int allocation[n];

    // Initialize all allocations to -1 (meaning not allocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Try to allocate each process to the worst (largest sufficient) block
    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blocks[j] >= processes[i]) {
                if (worstIndex == -1 || blocks[j] > blocks[worstIndex]) {
                    worstIndex = j; // Select the bigger block
                }
            }
        }

        // If a block was found, allocate it
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blocks[worstIndex] -= processes[i];
        }
    }

    // Print allocation result
    printf("Worst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }
}

int main() {
    int m, n;

    // Input number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blocks[m];

    // Input size of each memory block
    printf("Enter the size of each memory block: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blocks[i]);
    }

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processes[n];

    // Input size of each process
    printf("Enter the size of each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i]);
    }

    // Copy original blocks for each strategy
    int blocks1[m], blocks2[m], blocks3[m];
    for (int i = 0; i < m; i++) {
        blocks1[i] = blocks[i];
        blocks2[i] = blocks[i];
        blocks3[i] = blocks[i];
    }

    printf("\n");
    firstFit(blocks1, m, processes, n);  // Run First Fit
    printf("\n");
    bestFit(blocks2, m, processes, n);   // Run Best Fit
    printf("\n");
    worstFit(blocks3, m, processes, n);  // Run Worst Fit

    return 0;
}
