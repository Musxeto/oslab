#include <stdio.h>
#include <pthread.h>

// Function that will be executed by the thread
void* print_a() {
    printf("A\n");
    return NULL;
}
void* print_b() {
    printf("B\n");
    return NULL;
}
int main() {
    pthread_t threadA;  // Thread identifier
    pthread_t threadB;  // Thread identifier
    // Create a thread
    pthread_create(&threadA, NULL, print_a, NULL);
    sleep(3);
    pthread_create(&threadB,NULL,print_b,NULL);
    // Wait for the thread to finish
    pthread_join(threadA,NULL);
    pthread_join(threadB,NULL);
    printf("Hello from the main thread!\n");

    return 0;
}
