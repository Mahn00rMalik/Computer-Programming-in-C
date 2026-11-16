#include <stdio.h>

int main(void) {
    char line[100];
    FILE *fp = fopen("greeting.txt", "r");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }
    //fgets returns a character pointer
    //It stops reading when it hits a newline (\n),
    //when the array is full, or when the file ends
    // fgets(line, sizeof(line), fp);
    // printf("%s", line);

    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);
    return 0;
}