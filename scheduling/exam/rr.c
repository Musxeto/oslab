#include <stdio.h>

struct Process {
    int id;             // Process ID
    int arrivalTime;    // Arrival time
    int burstTime;      // Burst time
    int remainingTime;  // Remaining burst time
    int completionTime; // Completion time
    int waitingTime;    // Waiting time
    int turnAroundTime; // Turnaround time
    int responseTime;   // Response time
    int firstResponseTime; // First response time (for response time calculation)
};

void calculateTimes(struct Process processes[], int n, int timeQuantum) {
    int time = 0,completed = 0;
    
    while(completed < n){
        for(int i=0;i<n;i++){

            if(processes[i].arrivalTime <= time && processes[i].remainingTime > 0){
                if(processes[i].firstResponseTime == -1){
                    processes[i].firstResponseTime = time;
                    processes[i].responseTime = processes[i].firstResponseTime -processes[i].arrivalTime;
                }

                if(processes[i].remainingTime <= timeQuantum){
                    time +=processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].completionTime = time;
                    processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;
                    completed++;    
                    printf("P%d ", processes[i].id);
                } else {
                    processes[i].remainingTime -=timeQuantum;
                    time+=timeQuantum;
                     printf("P%d ", processes[i].id);
                }               
            }
            
        }
    }
    printf("\n");
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
    printf("Average Response Time: %.2f\n", totalResponseTime / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].firstResponseTime = -1; // Initialize to -1
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime; // Initialize remaining time
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    calculateTimes(processes, n, timeQuantum);
    printProcesses(processes, n);

    return 0;
}
