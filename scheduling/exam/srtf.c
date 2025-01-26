#include <stdio.h>

// Define a large constant value instead of INT_MAX
#define MAX_TIME 10000

// Structure to represent a process
struct Process {
    int id;               // Process ID
    int arrivalTime;      // Arrival time
    int burstTime;        // Burst time
    int remainingTime;    // Remaining time
    int completionTime;   // Completion time
    int waitingTime;      // Waiting time
    int turnAroundTime;   // Turnaround time
    int responseTime;     // Response time (new)
    int firstResponseTime; // Time when process is first selected
};

void calculateTimes(struct Process processes[], int n) {
    int completed = 0, time = 0, minRemainingIndex;
    int minRemainingTime;

    // Initialize remaining times for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].responseTime = -1;  // -1 indicates the process hasn't been selected yet
        processes[i].firstResponseTime = -1; // -1 indicates no first response time recorded
    }

    while (completed < n) {
        minRemainingIndex = -1;
        minRemainingTime = MAX_TIME;

        // Find the process with the shortest remaining time that has arrived and is not yet completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && processes[i].remainingTime > 0 &&
                processes[i].remainingTime < minRemainingTime) {
                minRemainingTime = processes[i].remainingTime;
                minRemainingIndex = i;
            }
        }

        if (minRemainingIndex != -1) {
            // Record the first response time if it's the first time the process is selected
            if (processes[minRemainingIndex].firstResponseTime == -1) {
                processes[minRemainingIndex].firstResponseTime = time;
            }

            // Execute the selected process for 1 unit of time
            processes[minRemainingIndex].remainingTime--;
            time++;

            // If the process is completed
            if (processes[minRemainingIndex].remainingTime == 0) {
                completed++;
                processes[minRemainingIndex].completionTime = time;
                processes[minRemainingIndex].turnAroundTime =
                    processes[minRemainingIndex].completionTime - processes[minRemainingIndex].arrivalTime;
                processes[minRemainingIndex].waitingTime =
                    processes[minRemainingIndex].turnAroundTime - processes[minRemainingIndex].burstTime;
                // Calculate response time
                processes[minRemainingIndex].responseTime =
                    processes[minRemainingIndex].firstResponseTime - processes[minRemainingIndex].arrivalTime;
            }
        } else {
            // If no process is ready to execute, increment time
            time++;
        }
    }
}

void printProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnAroundTime = 0, totalResponseTime = 0;

    printf("PID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
        totalResponseTime += processes[i].responseTime;

        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].waitingTime,
               processes[i].turnAroundTime,
               processes[i].responseTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
    printf("Average Response Time: %.2f\n", totalResponseTime / n);  // Display average response time
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}
