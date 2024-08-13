#include <stdlib.h>
#include <stdio.h>
int size;
int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Wrong Number of Inputs\n");
    }
    size = atoi(argv[2]);
    char buffer[size];
    FILE *fp, *fw;
    fp = fopen(argv[1], "rb");
    fw = fopen("copyfile", "wb");
    while (fread(buffer, size, 1, fp)){
        fwrite(buffer, size, 1, fw);
    }
fclose(fp);
fclose(fw);
}