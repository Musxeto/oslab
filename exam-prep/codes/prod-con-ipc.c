#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define KEY_PATH "/tmp"     // Path for generating unique key
#define PROJECT_ID 65       // Project identifier for ftok()
#define MSG_SIZE 100        // Maximum message size

// Message buffer structure
struct msgbuf {
    long mtype;          // Message type (must be > 0)
    char mtext[MSG_SIZE]; // Message text (data payload)
};

void producer(int msgid) {
    struct msgbuf message;
    char input[MSG_SIZE];

    while (1) {
        printf("Producer: Enter a message (or 'exit' to quit): ");
        fgets(input, MSG_SIZE, stdin);

        input[strcspn(input, "\n")] = 0;  // Remove trailing newline
        if (strcmp(input, "exit") == 0)
            break;

        message.mtype = 1;               // Set message type
        strncpy(message.mtext, input, MSG_SIZE - 1);  // Copy input
        message.mtext[MSG_SIZE - 1] = '\0'; // Ensure null termination

        // Send message to queue
        if (msgsnd(msgid, &message, strlen(message.mtext) + 1, 0) == -1) {
            perror("Producer: msgsnd failed");
            exit(1);
        }

        printf("Producer: Sent message: %s\n", message.mtext);
    }
}

void consumer(int msgid) {
    struct msgbuf message;

    while (1) {
        // Receive message of type 1
        if (msgrcv(msgid, &message, MSG_SIZE, 1, 0) == -1) {
            perror("Consumer: msgrcv failed");
            exit(1);
        }

        printf("Consumer: Received message: %s\n", message.mtext);

        // Exit if the received message is "exit"
        if (strcmp(message.mtext, "exit") == 0)
            break;
    }
}

int main() {
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    if ((key = ftok(KEY_PATH, PROJECT_ID)) == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create or get the message queue
    if ((msgid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message Queue created with ID: %d\n", msgid);

    // Fork a process to run producer and consumer
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process - Consumer
        consumer(msgid);
        exit(0);
    } else {
        // Parent process - Producer
        producer(msgid);

        // Wait for child process to finish
        wait(NULL);

        // Remove the message queue
        if (msgctl(msgid, IPC_RMID, NULL) == -1) {
            perror("msgctl (IPC_RMID) failed");
            exit(1);
        }

        printf("Message Queue removed.\n");
    }

    return 0;
}
