#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thread_function(void *arg){
    printf("Inside Thread Function");
    for (int i = 1; i < 5; i++)
    {
       printf("%d\n",i);
        sleep(1);
    }
}

int main(){
    pthread_t xyz_thread;
    pthread_create(&xyz_thread,NULL,thread_function,NULL);
    // pthread_join(xyz_thread,NULL);
    printf("Inside Main Function\n");

    for (int j = 10; j < 15; j++)
    {
        printf("%d\n",j);
        sleep(1);
    }
    return 0;
}

