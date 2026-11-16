#include <stdio.h>

int main(void) {
    //other modes -> read, append etc
    FILE *fp = fopen("greeting.txt", "w");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }    
    fprintf(fp, "Hello, NED University!\n");
    fprintf(fp, "File handling in C is easy.\n");
    fclose(fp);
    printf("Data written to greeting.txt\n");
    return 0;
}
