#include <stdio.h>
//Arrays and pointer arithmetic

int main(void) {
    int arr[5] = {10, 20, 30, 40, 50};
    int *p = arr;                 // same as p = &arr[0]

    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d   *(p + %d) = %d   address = %p\n",
               i, arr[i], i, *(p + i), (p + i));
    }

    p++;                          // move to the next int
    printf("After p++, *p = %d\n", *p);   // 20
    return 0;
}