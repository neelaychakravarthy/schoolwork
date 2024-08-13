#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>

int n_threads=2, n; //two threads instea of two processes
void *thread_function(void *thread_id){
    int i, tid;
    tid = (int) (size_t)thread_id;
    for (i=0;i<10;i++) {
      if (tid)
        printf("\t \t \t");
        printf("I am thread %d displaying iteration %d \n", tid, i);
        usleep (n);
}
    return thread_id;
  }

int main(int argc, char *argv[]) {
  if (argc != 2){
printf ("Usage: %s <delay> \n",argv[0]);
exit(0);
}
    int i;
    n = 3000; // n is a delay in microseconds inserted in parent and child iterations

    pthread_t threads[n_threads];
    for(i=0;i<n_threads;i++){
        pthread_create(&threads[i], NULL, thread_function, (void *) (size_t) i);
    }
    for(i=0;i<n_threads;i++){
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}