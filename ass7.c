#include <stdio.h> 
#define MAX_FRAMES 10 
#define MAX_PAGES 100 

// Function to implement FCFS (First Come First Serve) Page Replacement 
void fcfs(int pages[], int n, int frames) { 
    int queue[MAX_FRAMES], front = 0, rear = 0, count = 0, page_faults = 0; 
    printf("FCFS Page Replacement:\n"); 

    for (int i = 0; i < n; i++) { 
        int found = 0;

        // Check if the current page is already in the queue (i.e., in memory)
        for (int j = 0; j < count; j++) { 
            if (queue[j] == pages[i]) { 
                found = 1; 
                break; 
            } 
        }

        // If page is not found, it's a page fault
        if (!found) { 
            if (count < frames) { 
                // If there's still space in the frame queue, insert at rear
                queue[rear++] = pages[i]; 
                count++; 
            } else { 
                // If queue is full, replace the oldest page (from front)
                queue[front] = pages[i]; 
                front = (front + 1) % frames; // Move front circularly
            } 
            page_faults++; 
        }

        // Print the current state of frames
        printf("Step %d: ", i + 1); 
        for (int j = 0; j < count; j++) { 
            printf("%d ", queue[j]); 
        } 
        printf("\n"); 
    } 
    printf("Total Page Faults: %d\n", page_faults); 
} 

// Function to implement LRU (Least Recently Used) Page Replacement 
void lru(int pages[], int n, int frames) { 
    int frame[MAX_FRAMES], time[MAX_FRAMES], page_faults = 0, count = 0; 
    printf("LRU Page Replacement:\n"); 

    for (int i = 0; i < n; i++) { 
        int found = 0;

        // Check if the page is already in memory
        for (int j = 0; j < count; j++) { 
            if (frame[j] == pages[i]) { 
                found = 1; 
                time[j] = i; // Update usage time
                break; 
            } 
        }

        // If page is not found, it's a page fault
        if (!found) { 
            if (count < frames) { 
                // Add page if there is space
                frame[count] = pages[i]; 
                time[count] = i; // Record the time of use
                count++; 
            } else { 
                // Replace the least recently used page
                int least = 0; 
                for (int j = 1; j < frames; j++) { 
                    if (time[j] < time[least]) 
                        least = j; 
                } 
                frame[least] = pages[i]; 
                time[least] = i; // Update usage time
            } 
            page_faults++; 
        }

        // Print current frame state
        printf("Step %d: ", i + 1); 
        for (int j = 0; j < count; j++) { 
            printf("%d ", frame[j]); 
        } 
        printf("\n"); 
    } 
    printf("Total Page Faults: %d\n", page_faults); 
} 

// Function to implement Optimal Page Replacement 
void optimal(int pages[], int n, int frames) { 
    int frame[MAX_FRAMES], count = 0, page_faults = 0; 
    printf("Optimal Page Replacement:\n"); 

    for (int i = 0; i < n; i++) { 
        int found = 0;

        // Check if the current page is already in memory
        for (int j = 0; j < count; j++) { 
            if (frame[j] == pages[i]) { 
                found = 1; 
                break; 
            } 
        }

        // If page is not found, it's a page fault
        if (!found) { 
            if (count < frames) { 
                // Add page if there's space
                frame[count++] = pages[i]; 
            } else { 
                // Find the page that won't be used for the longest time
                int farthest = -1, index = -1; 
                for (int j = 0; j < frames; j++) { 
                    int k; 
                    for (k = i + 1; k < n; k++) { 
                        if (frame[j] == pages[k]) { 
                            if (k > farthest) { 
                                farthest = k; 
                                index = j; 
                            } 
                            break; 
                        } 
                    }
                    // If the page is not found in future, replace it
                    if (k == n) { 
                        index = j; 
                        break; 
                    } 
                }
                frame[index] = pages[i]; 
            } 
            page_faults++; 
        }

        // Print current frame state
        printf("Step %d: ", i + 1); 
        for (int j = 0; j < count; j++) { 
            printf("%d ", frame[j]); 
        } 
        printf("\n"); 
    } 
    printf("Total Page Faults: %d\n", page_faults); 
} 

int main() { 
    int choice, n, frames; 
    int pages[MAX_PAGES]; 

    // User input for number of pages
    printf("Enter the number of pages: "); 
    scanf("%d", &n); 

    // Input the page reference string
    printf("Enter the page reference sequence: "); 
    for (int i = 0; i < n; i++) { 
        scanf("%d", &pages[i]); 
    } 

    // Input number of frames (memory slots)
    printf("Enter the number of frames: "); 
    scanf("%d", &frames); 

    // Menu to choose the replacement algorithm
    printf("\nChoose a Page Replacement Algorithm:\n"); 
    printf("1. First Come First Serve (FCFS)\n"); 
    printf("2. Least Recently Used (LRU)\n"); 
    printf("3. Optimal Page Replacement\n"); 
    printf("Enter your choice: "); 
    scanf("%d", &choice); 

    // Execute selected algorithm
    switch (choice) { 
        case 1: 
            fcfs(pages, n, frames); 
            break; 
        case 2: 
            lru(pages, n, frames); 
            break; 
        case 3: 
            optimal(pages, n, frames); 
            break; 
        default: 
            printf("Invalid choice!\n"); 
    }

    return 0; 
}
