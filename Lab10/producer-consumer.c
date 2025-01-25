#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];

int count=0;

sem_t empty;
sem_t full;

void *producer(void *arg){
    int item;
    for(int i=0;i<10;i++){
        item =1;
        sem_wait(&empty);
        buffer[count]= item;
        count++;
        printf("Produucer Produced: %d\n",item);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg){
    int item;
    for(int i=0;i<10;i++){
        
        sem_wait(&full);

        count--;
        item = buffer[count];
        printf("Consumer CONsumed: %d\n",item);
        sem_post(&full);
        sleep(2);
    }
    return NULL;
}

int main(){
    pthread_t prod_thread,cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0,0);
    pthread_create(&prod_thread,NULL,producer,NULL);
    pthread_create(&cons_thread,NULL,consumer,NULL);
    pthread_join(prod_thread,NULL);
    pthread_join(cons_thread,NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
