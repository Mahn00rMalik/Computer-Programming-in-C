#include <stdio.h>
#include <string.h>

struct Student {
    char  name[30];
    int   roll;
    float cgpa;
};

void updateCgpa(struct Student *s, float newCgpa) {
    s->cgpa = newCgpa;          // same as (*s).cgpa = newCgpa;
}

int main(void) {
    struct Student st = {"Ali", 101, 3.20f};
    struct Student *ptr = &st;

    printf("%s (%d): %.2f\n", ptr->name, ptr->roll, ptr->cgpa);
    updateCgpa(&st, 3.55f);
    printf("Updated CGPA: %.2f\n", st.cgpa);   // 3.55
    return 0;
}