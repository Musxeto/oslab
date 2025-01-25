#include <stdio.h>

// Structure to store process details
typedef struct 
{
    int process_id;    // Process ID
    int burst_time;    // Burst time of the process
    int turnaround_time; // Turnaround time of the process
} Process;

void sort_by_burst_time(Process processes[], int n) 
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sjf_scheduling(Process processes[], int n) 
{
    int total_turnaround_time = 0;

    // Calculate turnaround times and total turnaround time
    int elapsed_time = 0;
    for (int i = 0; i < n; i++) {
        elapsed_time += processes[i].burst_time;
        processes[i].turnaround_time = elapsed_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Display results
    printf("\nExecution Order:\n");
    for (int i = 0; i < n; i++) 
    {
        printf("P%d ", processes[i].process_id);
    }

    printf("\n\nProcess Details:\n");
    printf("Process ID | Burst Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("    P%d     |     %d     |       %d\n",
               processes[i].process_id,
               processes[i].burst_time,
               processes[i].turnaround_time);
    }

    // Calculate and display average turnaround time
    double avg_turnaround_time = (double)total_turnaround_time / n;
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() 
{
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input burst times for each process
    printf("Enter burst times for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        processes[i].process_id = i + 1;
        printf("Burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Sort processes by burst time
    sort_by_burst_time(processes, n);

    // Perform SJF scheduling
    sjf_scheduling(processes, n);

    return 0;
}

