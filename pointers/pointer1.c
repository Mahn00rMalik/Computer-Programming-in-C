#include <stdio.h>

int main(void) {
    int age = 21;
    printf("Value of age   : %d\n", age);
    printf("Address of age : %p\n", &age);
    printf("Size of age    : %d bytes\n", sizeof(age));
    return 0;
}