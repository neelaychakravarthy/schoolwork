#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>




int N, M, L;
double **matrixA, **matrixB, **matrixC;

// function to multiply matrices
void *multiply_matrices(void *arg) {
    // get x passed during thread creation
    int x = (int) (size_t) arg;
    for (int j = 0; j < L; j++) { // rows
        double temp = 0;
        for (int i = 0; i < M; i++) { // columns
            // multiply
            temp += matrixA[x][i] * matrixB[i][j];
            //printf("x = %d, i = %d, j = %d, temp = %f, matrixA = %f, matrixB = %f\n", x, i, j, temp, matrixA[x][i], matrixB[i][j]);
        }
        matrixC[x][j] = temp;
    }
    // return null pointer
    return NULL;
}

// main function
int main(int argc, char *argv[]) {

    if (argc != 4){
	    printf("Usage: %s <N><M><L> \n", argv[0]);
	    exit(1);
	}
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	L = atoi(argv[3]);

	int i, j, k = 0;

	matrixA = (double **)malloc(sizeof(double *) * N);
	for(i = 0; i < N; i++)
		matrixA[i] = (double *)malloc(M);

	matrixB = (double **)malloc(sizeof(double *) * M);
	for(i = 0; i < M; i++)
		matrixB[i] = (double *)malloc(L);

	matrixC = (double **)malloc(sizeof(double *) * N);
	for(i = 0; i < N; i++)
		matrixC[i] = (double *)malloc(L);

    // create N threads
    pthread_t threads[N];

    

    // seeding
    srand(time(NULL));

    // fill matrix A with random integer values
    for (int i = 0; i < N; i++) { // each row
        for (int j = 0; j < M; j++) { // each column
            matrixA[i][j] = rand() % 10; // get a random value and store at i,j in matrix
        }
    }


    // fill matrix A with random integer values
    printf("******************\n");
    printf("**** Matrix A ****\n");
    printf("******************\n");
    for (int i = 0; i < N; i++) { // each row
        for (int j = 0; j < M; j++) { // each column
            printf("%d\t", (int)matrixA[i][j]); // print the value at i, j
        }
        printf("\n");
    }
    printf("******************\n\n");

    // fill matrix B with random integer values
    for (int i = 0; i < M; i++) { // each row
        for (int j = 0; j < L; j++) { // each column
            matrixB[i][j] = rand() % 10; // get a random value and store at i,j in matrix
        }
    }

    // fill matrix B with random integer values
    printf("******************\n");
    printf("**** Matrix B ****\n");
    printf("******************\n");
    for (int i = 0; i < M; i++) { // each row
        for (int j = 0; j < L; j++) { // each column
            printf("%d\t", (int)matrixB[i][j]); // print the value at i, j
        }
        printf("\n");
    }
    printf("******************\n\n");

    // now make threads
    for (int i = 0; i < N; i++) {
        
        pthread_create(&threads[i], NULL, multiply_matrices, (void *) (size_t) i);
    }

    // join all threads and wait for the threads to finish task
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // display the result matrix C
    printf("******************\n");
    printf("**** Matrix C ****\n");
    printf("******************\n");
    for (int i = 0; i < N; i++) { // each row
        for (int j = 0; j < L; j++) // each column
            printf("%d\t\t", (int)matrixC[i][j]); // print the (i, j)th element
        printf("\n");
    }

    return 0;
}