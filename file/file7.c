#include <stdio.h>
#include <string.h>

int main(void) {
    char line[100];
    int roll, count = 0, searchRoll, found = 0;
    char name[30], topName[30] = "";
    float marks, total = 0;
    FILE *fp;

    /* ---------- write 3 records, one per line ---------- */
    fp = fopen("marks.txt", "w");
    if (fp == NULL) return 1;
    fprintf(fp, "%d %s %.1f\n", 101, "Ali", 78.5);
    fprintf(fp, "%d %s %.1f\n", 102, "Sara", 91.0);
    fprintf(fp, "%d %s %.1f\n", 103, "Hamza", 66.5);
    fclose(fp);

    /* ---------- 1. DISPLAY: print each whole line ---------- */
    fp = fopen("marks.txt", "r");
    if (fp == NULL) return 1;
    printf("--- File contents ---\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
    fclose(fp);

    /* ---------- 2. AVERAGE: read values ---------- */
    fp = fopen("marks.txt", "r");
    if (fp == NULL) return 1;
    while (fscanf(fp, "%d %29s %f", &roll, name, &marks) == 3) {
        total += marks;
        count++;
    }
    fclose(fp);

    if (count > 0) {
        printf("Average marks: %.2f\n", total / count);
    }

    /* ---------- 3. SEARCH BY ROLL: read values ---------- */
    printf("\nEnter roll no to search: ");
    if (scanf("%d", &searchRoll) != 1) return 1;

    fp = fopen("marks.txt", "r");
    if (fp == NULL) return 1;
    while (fscanf(fp, "%d %29s %f", &roll, name, &marks) == 3) {
        if (roll == searchRoll) {
            printf("Found: %s scored %.1f\n", name, marks);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Roll no %d not found.\n", searchRoll);

    return 0;
}