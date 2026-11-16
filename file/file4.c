#include <stdio.h>

int main(void) {
    FILE *fp = fopen("greeting.txt", "a");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }
    
    fprintf(fp, "This line was appended.\n");

    fclose(fp);
    printf("Line appended\n");
    return 0;
}