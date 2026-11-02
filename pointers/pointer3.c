#include <stdio.h>

void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;            // only the local copies are swapped
}

void swapByPointer(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;           // the caller's variables are swapped
}

int main(void) {
    int x = 5, y = 9;

    swapByValue(x, y);
    printf("After swapByValue  : x = %d, y = %d\n", x, y);

    swapByPointer(&x, &y);
    printf("After swapByPointer: x = %d, y = %d\n", x, y);
    return 0;
}