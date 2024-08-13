#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void *fileWrite(void *arg);
int size;
int NTHREADS;
char storage[20];
int main(int argc, char *argv[]) {
    int i;
    if(argc != 4) {
        printf("Wrong Number of Inputs\n");
    }
    strcpy(storage, argv[1]);
    size = atoi(argv[2]);
    NTHREADS = atoi(argv[3]);
    pthread_t threads[NTHREADS];
    for (i = 0; i < NTHREADS; i++){
            pthread_create(&threads[i], NULL, fileWrite, (void *)(size_t)i);
    }
    for (i = 0; i < NTHREADS; i++){
            pthread_join(threads[i], NULL);
    }
    return 0;
}

void *fileWrite(void *arg){
    char fout[20];
    char buffer[size];
    sprintf(fout, "output%d.txt", arg);
    FILE *fp, *fw;
    fp = fopen(storage, "rb");
    fw = fopen(fout, "wb");
    while (fread(buffer, size, 1, fp)){
        fwrite(buffer, size, 1, fw);
    }
    fclose(fp);
    fclose(fw);
    return NULL;
}