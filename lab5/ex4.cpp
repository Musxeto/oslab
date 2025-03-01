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
        if (fork() == 0) { 
           
            printf("Process %d with pid %d\n", i + 1, getpid());
        } else { 
           
            wait(NULL);
            break;
        }
    }
    return 0;
}
