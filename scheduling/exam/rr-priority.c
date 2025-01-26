#include <stdio.h>

struct Process {
    int id;            // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int priority;      // Priority (lower value indicates higher priority)
    int remainingTime; // Remaining burst time
    int completionTime; // Completion time
    int waitingTime;    // Waiting time
    int turnAroundTime; // Turnaround time
    int responseTime;   // Response time
    int firstResponseTime; // First response time
};

void calculateTimes(struct Process processes[], int n) {
    int completed = 0, time = 0, minPriorityIndex;
    
    // Sort processes by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    while (completed < n) {
        minPriorityIndex = -1;

        // Find the process with the highest priority that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0) {
                if (minPriorityIndex == -1 || processes[i].priority < processes[minPriorityIndex].priority) {
                    minPriorityIndex = i;
                }
            }
        }

        if (minPriorityIndex != -1) {
            // If this is the first time the process is running, set its response time
            if (processes[minPriorityIndex].firstResponseTime == -1) {
                processes[minPriorityIndex].firstResponseTime = time;
                processes[minPriorityIndex].responseTime = processes[minPriorityIndex].firstResponseTime - processes[minPriorityIndex].arrivalTime;
            }

            // Process the selected process (reduce its remaining burst time by 1)
            processes[minPriorityIndex].remainingTime--;
            time++;

            // If the process is completed, update its completion time and calculate waiting and turnaround times
            if (processes[minPriorityIndex].remainingTime == 0) {
                processes[minPriorityIndex].completionTime = time;
                processes[minPriorityIndex].turnAroundTime = processes[minPriorityIndex].completionTime - processes[minPriorityIndex].arrivalTime;
                processes[minPriorityIndex].waitingTime = processes[minPriorityIndex].turnAroundTime - processes[minPriorityIndex].burstTime;
                completed++;
            }
        } else {
            time++;  // If no process can be executed, just increment time
        }
    }
}

void printProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;

    printf("PID\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalResponseTime += processes[i].responseTime;

        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].completionTime,
               processes[i].waitingTime,
               processes[i].turnAroundTime,
               processes[i].responseTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Response Time: %.2f\n", totalResponseTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].firstResponseTime = -1; // Initialize first response time to -1
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time to burst time
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}
