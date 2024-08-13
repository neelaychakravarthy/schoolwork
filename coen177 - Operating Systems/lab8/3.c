#include <stdlib.h>
#include <stdio.h>
int size;
int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Wrong Number of Inputs\n");
    }
    FILE *fp;
    size = atoi(argv[2]);
    char buffer[size];
    fp = fopen(argv[1], "rb");
    while (fread(buffer, size, 1, fp)){
    }
fclose(fp);
}