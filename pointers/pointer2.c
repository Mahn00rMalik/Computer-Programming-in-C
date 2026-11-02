#include <stdio.h>

int main(void) {
    int x = 10;
    int *p = &x;          // p now holds the address of x

    printf("x        = %d\n", x);
    printf("&x       = %p\n", &x);
    printf("p        = %p\n", p);   // same as &x
    printf("*p       = %d\n", *p);          // value at that address: 10
    printf("&p       = %p\n", &p);  // p has its own address too

    *p = 25;              // change x THROUGH the pointer
    printf("x is now %d\n", x);             // 25

    return 0;
}