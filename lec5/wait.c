#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t pid=fork();
    if(pid ==0){
        printf("Child Process ID: %d\n",getpid());
        sleep(10);
    }
    else if(pid>0){
        printf("Parent PID: %d\n",getppid());
        printf("Parent Process Child ID: %d\n",pid);
        wait(NULL);
    }
    else{
        printf("FOrk FAiled");
    }
}