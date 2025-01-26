#include <stdio.h>
#include <stdbool.h>

typedef struct 
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    bool is_responded; // To track if response time is set
} Process;

void round_robin(Process processes[], int n, int time_quantum) 
{
    int current_time = 0, completed = 0;
    bool executed_in_cycle = false;

    printf("\nExecution Order:\n");

    while (completed < n) 
    {
        executed_in_cycle = false;

        for (int i = 0; i < n; i++) 
        {
            if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) 
            {
                // Response time is set the first time a process is executed
                if (!processes[i].is_responded) 
                {
                    processes[i].response_time = current_time - processes[i].arrival_time;
                    processes[i].is_responded = true;
                }

                printf("P%d ", processes[i].process_id);
                executed_in_cycle = true;

                if (processes[i].remaining_time > time_quantum) 
                {
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } 
                else 
                {
                    current_time += processes[i].remaining_time;
                    processes[i].completion_time = current_time;
                    processes[i].remaining_time = 0;
                    completed++;
                }
            }
        }

        // Increment current time if no process was executed in this cycle
        if (!executed_in_cycle) 
        {
            current_time++;
        }
    }

    // Calculate turnaround time (TAT) and waiting time (WT)
    for (int i = 0; i < n; i++) 
    {
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

void display_results(Process processes[], int n) 
{
    printf("\n\nProcess Details:\n");
    printf("Process ID | Arrival Time | Burst Time | Completion Time | TAT | Waiting Time | Response Time\n");
    for (int i = 0; i < n; i++) 
    {
        printf("    P%d     |      %d       |     %d     |       %d        |  %d  |      %d      |      %d\n",
               processes[i].process_id,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].response_time);
    }

    // Calculate and display average TAT and WT
    double total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) 
    {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);
}

int main() 
{
    int n, time_quantum;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // Input arrival and burst times for each process
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) 
    {
        processes[i].process_id = i + 1;
        printf("Process P%d Arrival Time: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Process P%d Burst Time: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_responded = false; // Initialize response time flag
    }

    // Input time quantum
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    // Perform Round Robin scheduling
    round_robin(processes, n, time_quantum);

    // Display results
    display_results(processes, n);

    return 0;
}

