#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void sort_by_arrival_time(Process processes[], int n) {
    // Sort processes based on arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void calculate_metrics(Process processes[], int n) {
    // Calculate Completion Time, Turnaround Time, and Waiting Time
    processes[0].completion_time = processes[0].arrival_time + processes[0].burst_time;
    processes[0].turnaround_time = processes[0].completion_time - processes[0].arrival_time;
    processes[0].waiting_time = processes[0].turnaround_time - processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        // Completion time = Completion time of previous process + burst time of current process
        processes[i].completion_time = processes[i - 1].completion_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void display_results(Process processes[], int n) {
    // Print process details
    printf("\nProcess Details:\n");
    printf("Process ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("    P%d     |      %d       |     %d     |       %d        |       %d        |      %d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    // Input process details
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process P%d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Process P%d Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Sort processes by arrival time
    sort_by_arrival_time(processes, n);

    // Calculate metrics (Completion Time, Turnaround Time, Waiting Time)
    calculate_metrics(processes, n);

    // Display results
    display_results(processes, n);

    // Calculate average TAT and WT
    double total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}

