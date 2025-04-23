#include <stdbool.h>  // For using boolean data types
#include <stdint.h>   // For fixed-width integer types like INT32_MAX
#include <stdio.h>    // For standard input/output functions
#include <stdlib.h>   // For dynamic memory allocation and abs function

// Global variables
int n;                     // Number of disk requests
int *requests;             // Array to hold disk requests
int initial_head_pos;      // Starting position of the disk head
int size;                  // Size of the disk

// Function to take input from user
void input() {
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    
    // Allocate memory dynamically to hold disk requests
    printf("Enter the requests: ");
    requests = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head_pos);

    printf("Enter the size: ");
    scanf("%d", &size);
}

// Function to sort an array in ascending order (used in SCAN and CSCAN)
void sort(int *arr, int arr_size) {
    for (int i = 0; i < arr_size; ++i) {
        for (int j = i+1; j < arr_size; ++j) {
            if (arr[j] < arr[i]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// Function to find the index of the first element greater than x
int find(int *arr, int arr_size, int x) {
    for (int i = 0; i < arr_size; ++i) {
        if (arr[i] > x) {
            return i;
        }
    }
    return -1;
}

// FIFO (First-In-First-Out) Disk Scheduling
void fifo() {
    int movement = 0;
    int curr = initial_head_pos;
    printf("\nFIFO:\n");
    printf("%d ", curr);
    for (int i = 0; i < n; ++i) {
        movement += abs(curr - requests[i]);  // Calculate movement
        curr = requests[i];
        printf("%d ", curr);
    }
    printf("\nTotal Head Movement: %d\n", movement);
}

// SSTF (Shortest Seek Time First) Disk Scheduling
void sstf() {
    int movement = 0;
    int curr = initial_head_pos;
    printf("\nSSTF:\n");
    printf("%d ", curr);

    // Boolean array to mark which requests have been visited
    bool *vis = calloc(n, sizeof(bool));
    for (int i = 0; i < n; ++i) {
        int min_dist = INT32_MAX;
        int min_idx = -1;

        // Find the unvisited request with the shortest distance
        for (int j = 0; j < n; ++j) {
            if (vis[j]) continue;
            int dist = abs(curr - requests[j]);
            if (dist < min_dist) {
                min_dist = dist;
                min_idx = j;
            }
        }

        if (min_idx == -1) break;  // No more requests

        movement += min_dist;
        curr = requests[min_idx];
        vis[min_idx] = true;  // Mark as visited
        printf("%d ", curr);
    }
    free(vis);  // Free memory

    printf("\nTotal Head Movement: %d\n", movement);
}

// SCAN (Elevator Algorithm) Disk Scheduling
void scan() {
    int movement = 0;
    int curr = initial_head_pos;
    printf("\nSCAN:\n");
    int idx = find(requests, n, curr);
    printf("%d ", curr);

    // Move towards the end of the disk
    for (int i = idx; i < n; ++i) {
        movement += abs(curr - requests[i]);
        curr = requests[i];
        printf("%d ", curr);
    }

    // Move to the end of the disk
    movement += abs(curr - (size - 1));
    curr = size - 1;
    printf("%d ", curr);

    // Move back to service remaining requests on the left
    for (int i = idx - 1; i >= 0; --i) {
        movement += abs(curr - requests[i]);
        curr = requests[i];
        printf("%d ", curr);
    }
    printf("\nTotal Head Movement: %d\n", movement);
}

// CSCAN (Circular SCAN) Disk Scheduling
void cscan() {
    int movement = 0;
    int curr = initial_head_pos;
    printf("\nCSCAN:\n");
    int idx = find(requests, n, curr);
    printf("%d ", curr);

    // Move towards the end of the disk
    for (int i = idx; i < n; ++i) {
        movement += abs(curr - requests[i]);
        curr = requests[i];
        printf("%d ", curr);
    }

    // Jump to the beginning of the disk
    movement += abs(curr - (size - 1));
    curr = size - 1;
    printf("%d ", curr);
    movement += (size - 1);  // Move from end to beginning (circular)
    curr = 0;
    printf("%d ", curr);

    // Service the remaining requests at the beginning
    for (int i = 0; i < idx; ++i) {
        movement += abs(curr - requests[i]);
        curr = requests[i];
        printf("%d ", curr);
    }
    printf("\nTotal Head Movement: %d\n", movement);
}

// Main function
int main() {
    input();            // Take user inputs
    fifo();             // Apply FIFO algorithm
    sort(requests, n);  // Sort for SCAN and CSCAN
    sstf();             // Apply SSTF algorithm
    scan();             // Apply SCAN algorithm
    cscan();            // Apply CSCAN algorithm

    free(requests);     // Free allocated memory
    return 0;
}
