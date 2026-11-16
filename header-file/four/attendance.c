#include <stdio.h>
#include "config.h"
#include "attendance.h"

void print_attendance(const Student s[], int n) {
    int shortCount = 0;

    printf("--- Attendance (minimum: %d%%) ---\n", MIN_ATTENDANCE);
    for (int i = 0; i < n; i++) {
        int ok = s[i].attendance >= MIN_ATTENDANCE;
        if (!ok) shortCount++;
        printf("%-10s %3d%%  %s\n", s[i].name, s[i].attendance, ok ? "OK" : "SHORT");
    }
    printf("Below minimum: %d\n", shortCount);
}