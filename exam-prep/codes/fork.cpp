#include<stdio.h>
#include<unistd.h>

int main(){
    printf("Original PID: %d \n PPID: %d \n", getpid(), getppid());

    pid_t pid = fork();

    if(pid!=0){
        printf("Parent Process PID: %d \n PPID: %d\n", getpid(),getppid());
    } else {
        sleep(5);
        printf("Child Process with PID: %d \n PPID: %d\n", getpid(), getppid());
    }

    return 0;
}