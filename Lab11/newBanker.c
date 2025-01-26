#include <stdio.h>
#include <stdbool.h>

// Define constants for the number of processes and resource types
#define P 5 // Number of processes
#define R 3 // Number of resource types

// Function to calculate the "Need" matrix
void calculateNeed(int need[P][R], int max[P][R], int allocation[P][R]) {
    // Iterate over each process
    for (int i = 0; i < P; i++) {
        // Iterate over each resource type
        for (int j = 0; j < R; j++) {
            // Calculate the remaining resources needed by each process
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state
bool isSafe(int available[R], int max[P][R], int allocation[P][R]) {
    // Matrix to store the remaining resources needed by each process
    int need[P][R];
    calculateNeed(need, max, allocation); // Calculate the Need matrix

    // Array to track whether each process has finished executing
    bool finished[P] = {0}; // Initially, all processes are unfinished

    // Array to store the safe sequence of processes
    int safeSequence[P];

    // Array to track available resources during the simulation
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = available[i]; // Copy the available resources
    }

    // Counter for the number of processes added to the safe sequence
    int count = 0;

    // Loop until all processes are finished or the system is found unsafe
    while (count < P) {
        bool found = false; // Track if a process was found in this iteration

        // Iterate over all processes
        for (int i = 0; i < P; i++) {
            // Check if the process is unfinished
            if (!finished[i]) {
                int j;
                // Check if the process's need is less than or equal to available resources
                for (j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        break; // If any resource requirement is unmet, break
                    }
                }

                // If all resource needs are satisfied for process `i`
                if (j == R) {
                    // Add the process's allocated resources back to the available pool
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[i][k];
                    }
                    // Add this process to the safe sequence
                    safeSequence[count++] = i;

                    // Mark this process as finished
                    finished[i] = true;
                    found = true; // Indicate that a process was successfully executed
                }
            }
        }

        // If no unfinished process can be executed, the system is unsafe
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    // If all processes are executed, the system is safe
    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]); // Print the safe sequence
    }
    printf("\n");
    return true; // Indicate that the system is safe
}

// Main function to test the Banker's Algorithm
int main() {
    // Available resources
    int available[R] = {3, 3, 2};

    // Maximum resource demand of each process
    int max[P][R] = {
        {7, 5, 3},  // P0's maximum demand
        {3, 2, 2},  // P1's maximum demand
        {9, 0, 2},  // P2's maximum demand
        {2, 2, 2},  // P3's maximum demand
        {4, 3, 3}   // P4's maximum demand
    };

    // Currently allocated resources to each process
    int allocation[P][R] = {
        {0, 1, 0},  // P0's allocation
        {2, 0, 0},  // P1's allocation
        {3, 0, 2},  // P2's allocation
        {2, 1, 1},  // P3's allocation
        {0, 0, 2}   // P4's allocation
    };

    // Call the isSafe function to determine the system's state
    isSafe(available, max, allocation);
    return 0; // End the program
}
