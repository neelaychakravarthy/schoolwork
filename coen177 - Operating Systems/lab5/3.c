//Thread Synchronization - Semaphores
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define NTHREADS 10 //defining

void *go(void *arg);

pthread_t threads[NTHREADS];
pthread_mutex_t m;

int main() {
    pthread_mutex_init(&m, NULL);
    int i;
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++)
        pthread_join(threads[i],NULL);
    pthread_mutex_destroy(&m);
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)(unsigned long)arg);
    pthread_mutex_lock(&m);
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)(unsigned long)arg);
    pthread_mutex_unlock(&m);
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/