#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int capacity = 2, size = 0, value;
    int *marks = malloc(capacity * sizeof(int));
    if (marks == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter marks (-1 to stop):\n");
    //scanf returns a number: how many items it successfully read and stored.
    while (scanf("%d", &value) == 1 && value != -1) {
        if (size == capacity) {                  // array is full
            capacity *= 2;
            //Case 1: the block grew in place. There was free memory right
            // after the old block, so realloc just extended it.
            //marks → 0x1000   [45][67]
            //temp  → 0x1000   [45][67][  ][  ]
            //The address didn’t change, so marks = temp; changes nothing
            // in practice. It’s harmless.
            //Case 2: the block moved. There wasn’t enough room after the 
            //old block, so realloc allocated a new block somewhere else, 
            //copied 45 and 67 into it, and freed the old block.
            //marks → 0x1000   (freed — no longer yours)
            //temp  → 0x2000   [45][67][  ][  ]
            int *temp = realloc(marks, capacity * sizeof(int));
            if (temp == NULL) {                  // resize failed
                printf("Memory allocation failed\n");
                free(marks);                     // old block is still valid
                return 1;
            }
            //The following line copies an address, not data. After it runs,
            //marks and temp hold the same address, so both point to the 
            //resized block. No array elements are copied here; realloc 
            //already did any copying that was needed.
            marks = temp;                        // use the resized block
            printf("  (array grown to %d elements)\n", capacity);
        }
        marks[size++] = value;
    }

    printf("You entered %d marks:", size);
    for (int i = 0; i < size; i++) {
        printf(" %d", marks[i]);
    }
    printf("\n");

    free(marks);
    marks = NULL;
    return 0;
}