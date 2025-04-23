#include <stdio.h>          // Standard I/O functions
#include <limits.h>         // For INT_MAX constant

// Structure to hold information about a process
struct Process {
    int id;                 // Process ID
    int arrival_time;      // Arrival time of the process
    int burst_time;        // Burst time (execution time required)
    int priority;          // Priority (not used in this code)
    int completion_time;   // Time when process completes
    int turnaround_time;   // Turnaround time = completion - arrival
    int waiting_time;      // Waiting time = turnaround - burst
    int remaining_time;    // Remaining time (used in Round Robin)
};

// Function to print Gantt Chart without consecutive repeated processes
void printGanttChart(int timeline[], int count) {
    printf("\nGantt Chart:\n|");     // Print header
    int prev = -1;                   // Initialize previous process ID
    for (int i = 0; i < count; i++) {
        if (timeline[i] != prev) {   // Avoid printing repeated consecutive IDs
            printf(" P%d |", timeline[i]); // Print process ID
            prev = timeline[i];      // Update previous process ID
        }
    }
    printf("\n");                    // New line after chart
}

// Function to print process table and average times
void printTable(struct Process p[], int n) {
    int total_waiting = 0, total_turnaround = 0;   // Initialize total values
    printf("\n%-5s %-8s %-8s %-12s %-10s %-12s\n", 
           "ID", "Arrival", "Burst", "Completion", "Waiting", "Turnaround");
    // Print each process details
    for (int i = 0; i < n; i++) {
        printf("%-5d %-8d %-8d %-12d %-10d %-12d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].waiting_time, p[i].turnaround_time);
        total_waiting += p[i].waiting_time;            // Accumulate waiting time
        total_turnaround += p[i].turnaround_time;      // Accumulate turnaround time
    }
    // Print average times
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);
}

// First Come First Serve (FCFS) Scheduling Algorithm
void FCFS(struct Process p[], int n) {
    int time = 0;                    // Initialize current time
    int timeline[100], count = 0;    // For Gantt chart timeline
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time)   // If CPU is idle
            time = p[i].arrival_time;   // Wait until process arrives
        timeline[count++] = p[i].id;    // Record in timeline
        p[i].completion_time = time + p[i].burst_time;   // Calculate completion time
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time; // Turnaround time
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;      // Waiting time
        time = p[i].completion_time;    // Move time forward
    }
    printf("\nFCFS Scheduling:\n");     // Output header
    printTable(p, n);                   // Print process details
    printGanttChart(timeline, count);  // Print Gantt chart
}

// Shortest Job First (SJF) Non-Preemptive Scheduling
void SJF(struct Process p[], int n) {
    int completed = 0;                 // Track number of completed processes
    int time = 0;                      // Current time
    int timeline[100], count = 0;      // Gantt chart timeline
    while (completed < n) {            // Loop until all are completed
        int idx = -1, min_bt = INT_MAX; // Initialize min burst time and index
        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && p[i].completion_time == 0 && p[i].burst_time < min_bt) {
                min_bt = p[i].burst_time;   // Update min burst time
                idx = i;                    // Update index of shortest job
            }
        }
        if (idx == -1) {
            time++;                         // No process available, increment time
        } else {
            timeline[count++] = p[idx].id;  // Add to timeline
            time += p[idx].burst_time;      // Execute the process
            p[idx].completion_time = time;  // Set completion time
            p[idx].turnaround_time = time - p[idx].arrival_time; // Turnaround time
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time; // Waiting time
            completed++;                    // Mark as completed
        }
    }
    printf("\nSJF Scheduling (Non-Preemptive):\n");   // Output header
    printTable(p, n);                                // Print process info
    printGanttChart(timeline, count);                // Print Gantt chart
}

// Round Robin Scheduling
void RoundRobin(struct Process p[], int n, int quantum) {
    int time = 0;                      // Initialize current time
    int remaining = n;                // Number of processes not yet finished
    int timeline[100], count = 0;     // Gantt chart timeline
    for (int i = 0; i < n; i++)
        p[i].remaining_time = p[i].burst_time; // Initialize remaining time

    while (remaining > 0) {           // Continue until all processes complete
        for (int i = 0; i < n; i++) {
            // If process has arrived and not finished
            if (p[i].arrival_time <= time && p[i].remaining_time > 0) {
                // Record in Gantt chart only if new process ID
