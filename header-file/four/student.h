#ifndef STUDENT_H
#define STUDENT_H

#include "config.h"

typedef struct {
    char name[NAME_LEN];
    int  marks;
    int  attendance;   /* percentage */
} Student;

#endif