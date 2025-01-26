#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
using namespace std;

int main() {
    int pipe_fd[2]; // file descriptors for the pipe (pipe_fd[0] - read end, pipe_fd[1] - write end)
    char buffer[100];

    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        close(pipe_fd[0]); // Close the read end of the pipe in the child process
        const char* message = "Hello from child process!";
        write(pipe_fd[1], message, strlen(message) + 1); // Write to the pipe
        close(pipe_fd[1]); // Close the write end
        _exit(0);
    } else { // Parent process
        close(pipe_fd[1]); // Close the write end of the pipe in the parent process
        wait(NULL); // Wait for the child process to finish
        read(pipe_fd[0], buffer, sizeof(buffer)); // Read from the pipe
        cout << "Parent received: " << buffer << endl;
        close(pipe_fd[0]); // Close the read end
    }

    return 0;
}
