#include <pthread.h>>
#include <unistd.h>

int main(){
    pthread_t xyz_thread;
    pthread_create(&xyz_thread,NULL,thread_function,NULL);
    pthread_join(xyz_thread,NULL);
    printf("Inside Main Function\n");

    for (int j = 1; j < 5; j++)
    {
        printf("%d\n",&j);
        sleep(1);
    }
    
    return 0;
}

void *thread_function(void *arg){
    printf("Inside Thread Function");
    for (int i = 1; i < 5; i++)
    {
       printf("%d\n",&i);
        sleep(1);
    }`
    
}