#include "math_utils.h"

int add(int a, int b) {
    return a + b;
}

int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++)
        result *= i;
    return result;
}

int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return 0;
    return 1;
}

double circle_area(double r) {
    return PI * r * r;
}