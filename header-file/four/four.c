#include <stdio.h>
#include "config.h"
#include "student.h"
#include "results.h"
#include "attendance.h"

int main(void) {
    Student cls[MAX_STUDENTS] = {
        {"Ayesha", 78, 92},
        {"Bilal",  45, 80},
        {"Hamza",  62, 70},
        {"Sana",   88, 95},
        {"Usman",  50, 74}
    };
    int n = 5;

    printf("%s - Class Report\n", UNIVERSITY);
    printf("Students: %d (capacity %d)\n\n", n, MAX_STUDENTS);

    print_results(cls, n);
    print_attendance(cls, n);
    return 0;
}