#include <stdio.h>

struct Process {
    int id;             
    int arrivalTime;    
    int burstTime;      
    int completionTime; 
    int waitingTime;    
    int turnAroundTime; // Turnaround time
};

void calculateTimes(struct Process processes[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (time < processes[i].arrivalTime) {
            time = processes[i].arrivalTime;
        }
        time += processes[i].burstTime;
        processes[i].completionTime = time; 
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
    }
}

void printProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    printf("\nPID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;

        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].id,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].completionTime,
               processes[i].waitingTime,
               processes[i].turnAroundTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("How many processes do you want to enter? ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter the Arrival Time and Burst Time of Process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    calculateTimes(processes, n);
    printProcesses(processes, n);

    return 0;
}