#include <stdio.h>
#include "math_utils.h"

int main(void) {
    printf("3 + 4 = %d\n", add(3, 4));
    printf("5! = %d\n", factorial(5));
    printf("Is 17 prime? %s\n", is_prime(17) ? "Yes" : "No");
    printf("Area (r = 2): %.2f\n", circle_area(2.0));
    return 0;
}