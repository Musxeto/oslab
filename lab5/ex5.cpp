#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_processes>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
        if (pid == 0) { 
            printf("Child %d with pid %d\n", i + 1, getpid());
            return 0;
        }
    }
    
   
    for (int i = 0; i < n; i++) {
        wait(NULL);
    }
    
    return 0;
}
