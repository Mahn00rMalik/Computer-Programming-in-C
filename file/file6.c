#include <stdio.h>

int main(void) {
    int roll;
    char name[30];
    float marks;
    FILE *fp = fopen("marks.txt", "w");
    if (fp == NULL) return 1;

    /* write 3 records, one per line */
    fprintf(fp, "%d %s %.1f\n", 101, "Ali", 78.5);
    fprintf(fp, "%d %s %.1f\n", 102, "Sara", 91.0);
    fprintf(fp, "%d %s %.1f\n", 103, "Hamza", 66.5);
    fclose(fp);

    /* read them back */
    fp = fopen("marks.txt", "r");
    if (fp == NULL) return 1;
    printf("Roll  Name    Marks\n");
    while (fscanf(fp, "%d %29s %f", &roll, name, &marks) == 3) {
        printf("%-5d %-7s %.1f\n", roll, name, marks);
    }
    fclose(fp);
    return 0;
}