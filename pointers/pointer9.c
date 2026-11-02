#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int candidates = 5;
    int votes[] = {2, 0, 4, 2, 1, 2, 4, 0};
    int total = sizeof(votes) / sizeof(votes[0]);

    int *count = calloc(candidates, sizeof(int));   // 5 ints, all 0
    if (count == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < total; i++) {
        count[votes[i]]++;          // safe: every counter starts at 0
    }

    for (int i = 0; i < candidates; i++) {
        printf("Candidate %d: %d votes\n", i, count[i]);
    }

    free(count);
    count = NULL;
    return 0;
}