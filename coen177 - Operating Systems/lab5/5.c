#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MaxItems 10 // Maximum items a producer can produce or a consumer can consume
#define BufferSize 10 // Size of the buffer
#define P 3
#define C 2

pthread_cond_t empty;
pthread_cond_t full;
int in = 0; //initializing
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;
int counter = 0;

void *producer(void *pno)
{
    int item;
    for(int i = 0; i < MaxItems; i++) {
        item = rand()%20; // Produce an random item
        pthread_mutex_lock(&mutex);
        while(counter == BufferSize){
            pthread_cond_wait(&empty, &mutex);
        }
        buffer[in] = item;
        sleep(1);
        counter++;
        printf("Producer %d: Insert Item %d at %d\n", (int)(size_t)pno,buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
void *consumer(void *cno)
{
    for(int i = 0; i < MaxItems; i++) {
        pthread_mutex_lock(&mutex);
        while(counter == 0){
            pthread_cond_wait(&full, &mutex);
        }
        int item = buffer[out];
        sleep(1);
        counter--;
        printf("Consumer %d: Remove Item %d from %d\n",(int)(size_t)cno,item, out);
        out = (out+1)%BufferSize;
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main()
{

    pthread_t pro[P],con[C];
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&empty,NULL);
    pthread_cond_init(&full, NULL);

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

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&empty);
    pthread_cond_destroy(&full);

    return 0;

}