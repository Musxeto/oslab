#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    printf("Process is Terminated");
    exit(0);

    printf("Parent Process ID: %d\n",getpid());
    return 0; 
}
