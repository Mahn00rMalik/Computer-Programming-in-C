#include <stdio.h>
#include "config.h"
#include "results.h"

void print_results(const Student s[], int n) {
    int passed = 0;

    printf("--- Results (pass mark: %d) ---\n", PASSING_MARKS);
    for (int i = 0; i < n; i++) {
        int ok = s[i].marks >= PASSING_MARKS;
        if (ok) passed++;
        printf("%-10s %3d  %s\n", s[i].name, s[i].marks, ok ? "PASS" : "FAIL");
    }
    printf("Passed: %d of %d\n\n", passed, n);
}