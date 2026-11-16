#include <stdio.h>

int main(void) {
    int ch, lines = 0;    /* ch is int so it can hold EOF */
    FILE *fp = fopen("greeting.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n')
            lines++;
    }
    fclose(fp);
    printf("Lines: %d\n", lines);
    return 0;
}