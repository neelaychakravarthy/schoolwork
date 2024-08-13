#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int N, M, L;
double **matrixA, **matrixB, **matrixC;

struct d {
	int row;
	int col;
};


void initializeMatrix(int r, int c, double **matrix);
void *multiplyRow(void* arg);
void printMatrix(int r, int c, double **matrix);

int main(int argc, char *argv[]){
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

	pthread_t threads[N*L];

	initializeMatrix(N, M, matrixA);
	initializeMatrix(M, L, matrixB);

	struct d *data;

	for(i=0;i<N;i++){
		for(j=0;j<L;j++){
			data = (struct d *) malloc(sizeof(struct d));
			data->row = i;
			data->col = j;
			pthread_create(&threads[i*L + j],NULL,multiplyRow,data);
		}
	}

	for(k=0;k<N;k++){
		pthread_join(threads[k],NULL);
	}

	printf("Printing Matrix A: \n");
	printMatrix(N,M,matrixA);
	printf("Printing Matrix B: \n");
	printMatrix(M,L,matrixB);
	printf("Printing Matrix C: \n");
	printMatrix(N,L,matrixC);

	return 0;
}

void initializeMatrix(int r, int c, double **matrix){
	srand(time(NULL));
	int i, j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			matrix[i][j]=rand()%5;
		}
	}
}

void* multiplyRow(void* arg){
	struct d *data = arg;
	int i, j, k;

	i = data->row;
	j = data->col;
	printf("Thread %d is multiplying %dth row by each column and adding them\n", i, j);
	double temp = 0;
	for(k=0; k < M; k++){
		temp += matrixA[i][k]*matrixB[k][j];
		matrixC[i][j] = temp;
	}
	pthread_exit(0);
}

void printMatrix(int r, int c, double **matrix){
	int i, j;
	for (i=0; i<r; i++){
		for (j=0; j<c; j++){
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
}