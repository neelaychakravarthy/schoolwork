#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


#define MaxItems 10 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 10 // Size of the buffer
#define P 3
#define C 2

sem_t * empty;
sem_t * full;
int in = 0; //initializing
int out = 0;
int buffer[BufferSize];
sem_t * mutex;

void *producer(void *pno)
{
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%20; // Produce an random item
        sem_wait(empty);
        sem_wait(mutex);
        buffer[in] = item;
        sleep(1);
        printf("Producer %d: Insert Item %d at %d\n", (int)(size_t)pno,buffer[in],in);
        in = (in+1)%BufferSize;
        sem_post(mutex);
        sem_post(full);
        sleep(1);
    }
    return NULL;
}
void *consumer(void *cno)
{
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(full);
        sem_wait(mutex);
        int item = buffer[out];
        sleep(1);
        printf("Consumer %d: Remove Item %d from %d\n",(int)(size_t)cno,item, out);
        out = (out+1)%BufferSize;
        sem_post(mutex);
        sem_post(empty);
        sleep(1);
    }
    return NULL;
}

int main()
{

    pthread_t pro[P],con[C];
    mutex = sem_open("mutex", O_CREAT, 0644, 1);
    empty = sem_open("empty", O_CREAT, 0644, BufferSize);
    full = sem_open("full", O_CREAT, 0644, 0);


    for(int i = 0; i < P; i++) {
        pthread_create(&pro[i], NULL, (void *)producer, (void*)(size_t)i);
    }
    for(int i = 0; i < C; i++) {
        pthread_create(&con[i], NULL, (void *)consumer, (void*)(size_t)i);
    }

    for(int i = 0; i < P; i++) {
        pthread_join(pro[i], NULL);
    }
    for(int i = 0; i < C; i++) {
        pthread_join(con[i], NULL);
    }

    sem_unlink("mutex");
    sem_unlink("full");
    sem_unlink("empty");

    return 0;

}