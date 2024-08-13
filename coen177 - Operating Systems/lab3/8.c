#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void* );
#define NTHREADS 10
pthread_t threads[NTHREADS];

int main() {
    int i;
    int it[10];
    for(i = 0; i < NTHREADS; i++) {
        it[i] = i;
        pthread_create(&threads[i], NULL,go,&it[i]);
    }
    for(i = 0; i < NTHREADS; i++) {
        printf("Thread %d returned\n", i);
        pthread_join(threads[i],NULL);
    }
    printf("Main thread done\n");
    return 0;
}

void *go(void *arg) {
    printf("Hello from thread %d with iteration %d\n", pthread_self(), *(int*)arg);
    return 0;
}