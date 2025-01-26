#include <stdio.h>

struct Process {
    int id;            // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int priority;      // Priority (lower value indicates higher priority)
    int completionTime; // Completion time
    int waitingTime;    // Waiting time
    int turnAroundTime; // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int completed = 0, time = 0, minPriorityIndex;
    
    // Sort the processes by arrival time first, then by priority (ascending)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime || 
                (processes[i].arrivalTime == processes[j].arrivalTime && processes[i].priority > processes[j].priority)) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    while (completed < n) {
        minPriorityIndex = -1;
        
        // Find the process with the highest priority (smallest priority value) that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].completionTime == 0) {
                if (minPriorityIndex == -1 || processes[i].priority < processes[minPriorityIndex].priority) {
                    minPriorityIndex = i;
                }
            }
        }

        if (minPriorityIndex != -1) {
            // Process the selected process (it runs to completion as it's non-preemptive)
            time += processes[minPriorityIndex].burstTime;
            processes[minPriorityIndex].completionTime = time;
            processes[minPriorityIndex].turnAroundTime = processes[minPriorityIndex].completionTime - processes[minPriorityIndex].arrivalTime;
            processes[minPriorityIndex].waitingTime = processes[minPriorityIndex].turnAroundTime - processes[minPriorityIndex].burstTime;

            completed++;
        } else {
            time++;  // If no process can be executed, just increment time
        }
    }
}

void printProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("PID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].completionTime,
               processes[i].waitingTime,
               processes[i].turnAroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}
