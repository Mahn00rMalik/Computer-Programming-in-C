/*
 * ============================================================
 *   STUDENT MANAGEMENT SYSTEM  (File Handling in C - Text File)
 * ============================================================
 *   Operations : Add, Show, Search, Update, Delete
 *   Storage    : Every record is saved as one line in the text
 *                file "students.txt", so data is kept after the
 *                program is closed. Open it in Notepad to see it.
 *
 *   Line format: roll|name|department|semester|cgpa
 *   Example    : 101|Ali Khan|CIS|3|3.45
 *   ('|' is used as separator so names may contain spaces)
 *
 *   Compile    : gcc student_management.c -o sms
 *   Run        : ./sms        (Windows: sms.exe)
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define DATA_FILE "students.txt"
#define TEMP_FILE "temp.txt"

/* ---------- one student record ---------- */
struct Student {
    int   roll;
    char  name[50];
    char  department[30];
    int   semester;
    float cgpa;
};

/* ---------- function prototypes ---------- */
void addStudent(void);
void showStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
int  readRecord(FILE *fp, struct Student *s);
void writeRecord(FILE *fp, struct Student s);
int  rollExists(int roll);
void inputDetails(struct Student *s);
void printHeader(void);
void printStudent(struct Student s);
void readString(char *str, int size);
int  readInt(void);
float readFloat(void);

/* ============================================================ */
int main(void) {
    int choice;

    do {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Show All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        choice = readInt();
        if (feof(stdin))          /* input ended (Ctrl+D / Ctrl+Z) */
            choice = 0;

        switch (choice) {
            case 1: addStudent();    break;
            case 2: showStudents();  break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}

/* ============================================================
 *        READ / WRITE ONE RECORD (ONE LINE) OF THE FILE
 * ============================================================ */

/* writes one student as one line: roll|name|dept|sem|cgpa */
void writeRecord(FILE *fp, struct Student s) {
    fprintf(fp, "%d|%s|%s|%d|%.2f\n",
            s.roll, s.name, s.department, s.semester, s.cgpa);
}

/* reads the next line into s; returns 1 on success, 0 at end */
int readRecord(FILE *fp, struct Student *s) {
    char line[200];

    while (fgets(line, sizeof(line), fp) != NULL) {
        /* %[^|] means "read everything up to the next |" */
        if (sscanf(line, "%d|%49[^|]|%29[^|]|%d|%f",
                   &s->roll, s->name, s->department,
                   &s->semester, &s->cgpa) == 5)
            return 1;
        /* a blank or broken line is skipped */
    }
    return 0;
}

/* ============================================================
 * 1. ADD  - open in append mode "a" and write at the end
 * ============================================================ */
void addStudent(void) {
    struct Student s;
    FILE *fp;

    printf("\n--- Add Student ---\n");
    printf("Roll No    : ");
    s.roll = readInt();

    if (s.roll <= 0) {
        printf("Roll number must be a positive number.\n");
        return;
    }
    if (rollExists(s.roll)) {
        printf("A student with roll no %d already exists.\n", s.roll);
        return;
    }

    inputDetails(&s);

    fp = fopen(DATA_FILE, "a");           /* append text */
    if (fp == NULL) {
        printf("Error: cannot open %s\n", DATA_FILE);
        return;
    }
    writeRecord(fp, s);
    fclose(fp);

    printf("Student added and saved to file.\n");
}

/* ============================================================
 * 2. SHOW - read every line from start to end
 * ============================================================ */
void showStudents(void) {
    struct Student s;
    int count = 0;
    FILE *fp = fopen(DATA_FILE, "r");     /* read text */

    printf("\n--- All Students ---\n");
    if (fp == NULL) {
        printf("No records found (file does not exist yet).\n");
        return;
    }

    printHeader();
    while (readRecord(fp, &s)) {
        printStudent(s);
        count++;
    }
    fclose(fp);

    if (count == 0)
        printf("No records found.\n");
    else
        printf("Total students: %d\n", count);
}

/* ============================================================
 * 3. SEARCH - by roll number or by (part of) name
 * ============================================================ */
void searchStudent(void) {
    struct Student s;
    int option, roll, found = 0;
    char key[50];
    FILE *fp = fopen(DATA_FILE, "r");

    printf("\n--- Search Student ---\n");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("1. Search by Roll No\n2. Search by Name\nChoice: ");
    option = readInt();

    if (option == 1) {
        printf("Enter Roll No: ");
        roll = readInt();
        while (readRecord(fp, &s)) {
            if (s.roll == roll) {
                printHeader();
                printStudent(s);
                found = 1;
                break;                    /* roll numbers are unique */
            }
        }
    } else if (option == 2) {
        printf("Enter Name (or part of it): ");
        readString(key, sizeof(key));
        while (readRecord(fp, &s)) {
            if (strstr(s.name, key) != NULL) {
                if (!found) printHeader();
                printStudent(s);
                found = 1;
            }
        }
    } else {
        printf("Invalid option.\n");
        fclose(fp);
        return;
    }
    fclose(fp);

    if (!found)
        printf("No matching student found.\n");
}

/* ============================================================
 * 4. UPDATE - lines in a text file have different lengths, so
 *             we cannot overwrite one in place. Instead we copy
 *             every record to a temp file, writing the NEW
 *             details for the matching student, then replace
 *             the old file with the temp file.
 * ============================================================ */
void updateStudent(void) {
    struct Student s;
    int roll, found = 0;
    FILE *fp, *temp;

    printf("\n--- Update Student ---\n");
    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll No to update: ");
    roll = readInt();

    temp = fopen(TEMP_FILE, "w");
    if (temp == NULL) {
        printf("Error: cannot create temporary file.\n");
        fclose(fp);
        return;
    }

    while (readRecord(fp, &s)) {
        if (s.roll == roll) {
            found = 1;
            printf("Current record:\n");
            printHeader();
            printStudent(s);

            printf("Enter new details (roll no stays %d)\n", s.roll);
            inputDetails(&s);
        }
        writeRecord(temp, s);             /* old or updated record */
    }
    fclose(fp);
    fclose(temp);

    if (found) {
        remove(DATA_FILE);                /* delete old file      */
        rename(TEMP_FILE, DATA_FILE);     /* temp becomes the new */
        printf("Record updated and saved to file.\n");
    } else {
        remove(TEMP_FILE);                /* nothing changed      */
        printf("Student with roll no %d not found.\n", roll);
    }
}

/* ============================================================
 * 5. DELETE - copy every record EXCEPT the one to delete into
 *             a temp file, then replace the old file with it
 * ============================================================ */
void deleteStudent(void) {
    struct Student s;
    int roll, found = 0;
    FILE *fp, *temp;

    printf("\n--- Delete Student ---\n");
    fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("Enter Roll No to delete: ");
    roll = readInt();

    temp = fopen(TEMP_FILE, "w");
    if (temp == NULL) {
        printf("Error: cannot create temporary file.\n");
        fclose(fp);
        return;
    }

    while (readRecord(fp, &s)) {
        if (s.roll == roll)
            found = 1;                    /* skip it = delete it */
        else
            writeRecord(temp, s);
    }
    fclose(fp);
    fclose(temp);

    if (found) {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("Student with roll no %d deleted.\n", roll);
    } else {
        remove(TEMP_FILE);
        printf("Student with roll no %d not found.\n", roll);
    }
}

/* ============================================================
 *                    HELPER FUNCTIONS
 * ============================================================ */

/* returns 1 if the roll number is already in the file */
int rollExists(int roll) {
    struct Student s;
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL)
        return 0;
    while (readRecord(fp, &s)) {
        if (s.roll == roll) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* asks for every field except the roll number */
void inputDetails(struct Student *s) {
    do {
        printf("Name       : ");
        readString(s->name, sizeof(s->name));
    } while (s->name[0] == '\0' || strchr(s->name, '|') != NULL);

    do {
        printf("Department : ");
        readString(s->department, sizeof(s->department));
    } while (s->department[0] == '\0' || strchr(s->department, '|') != NULL);

    printf("Semester   : ");
    s->semester = readInt();
    printf("CGPA       : ");
    s->cgpa = readFloat();
}

void printHeader(void) {
    printf("%-6s %-20s %-12s %-4s %-5s\n",
           "Roll", "Name", "Department", "Sem", "CGPA");
    printf("------------------------------------------------------\n");
}

void printStudent(struct Student s) {
    printf("%-6d %-20s %-12s %-4d %.2f\n",
           s.roll, s.name, s.department, s.semester, s.cgpa);
}

/* reads a whole line (spaces allowed) and removes the '\n' */
void readString(char *str, int size) {
    if (fgets(str, size, stdin) == NULL) {
        strcpy(str, "-");                 /* input ended */
        return;
    }
    str[strcspn(str, "\n")] = '\0';
}

/* reads an int safely; returns -1 for invalid input */
int readInt(void) {
    char line[32];
    int value;
    readString(line, sizeof(line));
    if (sscanf(line, "%d", &value) != 1)
        return -1;
    return value;
}

/* reads a float safely; returns 0 for invalid input */
float readFloat(void) {
    char line[32];
    float value;
    readString(line, sizeof(line));
    if (sscanf(line, "%f", &value) != 1)
        return 0.0f;
    return value;
}