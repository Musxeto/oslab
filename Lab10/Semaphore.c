#include<stdio.h>
#include <unistd.h>

int semaphore =1;

void down(){
    while(semaphore<=0){
        //busy
    }
    semaphore--;
    printf("Resource Locked\n");
}


void up(){
    semaphore++;
    printf("Resource Unlocked\n");
}

int main(){
    printf("Performing Down OPeration\n");
    down();

    printf("Critical Section (Resource in use)\n");
    sleep(2);

    printf("Performing up OPeration\n");
    up();

    printf("Semaphore operations completed\n");
    return 0;
}