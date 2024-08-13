#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Wrong Number of Inputs\n");
    }
    char buffer[10000];
    FILE *fp;
    fp = fopen(argv[1], "rb");
    while (fread(buffer, sizeof(buffer), 1, fp)){
    }
fclose(fp);
}