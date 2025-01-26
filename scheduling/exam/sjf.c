#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;          // Process ID
    int arrivalTime; // Arrival time
    int burstTime;   // Burst time
    int waitingTime; // Waiting time
    int turnAroundTime; // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int completed = 0, time = 0;
    int minBurstTimeIndex;
    int isCompleted[n]; // Array to track if a process is completed
    for (int i = 0; i < n; i++) {
        isCompleted[i] = 0; // Initialize all processes as not completed
    }

    while (completed < n) {
        minBurstTimeIndex = -1;

        // Find the process with the shortest burst time among available processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= time && !isCompleted[i]) {
                if (minBurstTimeIndex == -1 || processes[i].burstTime < processes[minBurstTimeIndex].burstTime) {
                    minBurstTimeIndex = i;
                }
            }
        }

        if (minBurstTimeIndex != -1) {
            // Execute the selected process
            time += processes[minBurstTimeIndex].burstTime;
            processes[minBurstTimeIndex].turnAroundTime = time - processes[minBurstTimeIndex].arrivalTime;
            processes[minBurstTimeIndex].waitingTime = processes[minBurstTimeIndex].turnAroundTime - processes[minBurstTimeIndex].burstTime;
            isCompleted[minBurstTimeIndex] = 1; // Mark the process as completed
            completed++;
        } else {
            time++; // If no process is available, increment time
        }
    }
}

void printProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("PID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

        printf("%d\t%d\t%d\t%d\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
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
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}
