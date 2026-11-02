#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("How many marks? ");
    scanf("%d", &n);

    int *marks = malloc(n * sizeof(int));
    if (marks == NULL) {                 // always check!
        printf("Memory allocation failed\n");
        return 1;
    }

    int total = 0;
    for (int i = 0; i < n; i++) {
        printf("Mark %d: ", i + 1);
        scanf("%d", &marks[i]);          // or: marks + i
        total += marks[i];
    }
    printf("Average = %.2f\n", (float)total / n);

    free(marks);                         // release the memory
    marks = NULL;                        // avoid a dangling pointer
    return 0;
}