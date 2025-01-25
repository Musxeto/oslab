#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool is_completed;
} Process;

void sort_by_arrival_and_priority(Process processes[], int n, int current_time) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time &&
                 processes[j].priority < processes[j + 1].priority)) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

int find_highest_priority_process(Process processes[], int n, int current_time) {
    int highest_priority_index = -1;
    int highest_priority = -1;

    for (int i = 0; i < n; i++) {
        if (!processes[i].is_completed && processes[i].arrival_time <= current_time) {
            if (processes[i].priority > highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }
    }
    return highest_priority_index;
}

void calculate_metrics(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void priority_based_round_robin(Process processes[], int n, int time_quantum) {
    int time = 0;
    int completed = 0;
    bool is_response_time_recorded[MAX_PROCESSES] = {false};

    printf("\nExecution Order:\n");

    while (completed < n) {
        int current_process_index = find_highest_priority_process(processes, n, time);

        if (current_process_index == -1) {
            time++; // No process is ready, advance time
            continue;
        }

        Process *current_process = &processes[current_process_index];

        // Record response time if it's the first time executing
        if (!is_response_time_recorded[current_process_index]) {
            current_process->response_time = time - current_process->arrival_time;
            is_response_time_recorded[current_process_index] = true;
        }

        // Execute for time quantum or until the process is finished
        int execution_time = (current_process->remaining_time > time_quantum) ? time_quantum : current_process->remaining_time;
        printf("P%d ", current_process->process_id);
        current_process->remaining_time -= execution_time;
        time += execution_time;

        // If the process finishes
        if (current_process->remaining_time == 0) {
            current_process->is_completed = true;
            current_process->completion_time = time;
            completed++;
        }
    }

    printf("\n");
    calculate_metrics(processes, n);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[MAX_PROCESSES];

    // Input process details
    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process P%d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Process P%d Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Process P%d Priority: ", i + 1);
        scanf("%d", &processes[i].priority);

        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = false;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Sort processes initially by arrival time and priority
    sort_by_arrival_and_priority(processes, n, 0);

    // Execute the scheduling
    priority_based_round_robin(processes, n, time_quantum);

    // Print process details
    printf("\nProcess Details:\n");
    printf("Process ID | Arrival Time | Burst Time | Priority | Completion Time | TAT | Waiting Time \n");
    for (int i = 0; i < n; i++) {
        printf("    P%d     |      %d       |     %d     |    %d    |       %d        |  %d  |      %d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }

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

