#include <stdio.h>

int myStrlen(const char *s) {
    const char *start = s;
    while (*s != '\0') {
        s++;
    }
  
    return (int)(s - start);   // pointer subtraction = number of chars
}

int main(void) {
    char name[] = "NED";        // modifiable array: {'N','E','D','\0'}
    const char *msg = "Hello";  // pointer to a read-only string literal

    name[0] = 'B';              // OK -> "BED"
    // msg[0] = 'J';            // WRONG: modifying a literal is undefined behaviour

    printf("%s has %d chars\n", name, myStrlen(name));   // BED has 3 chars
    printf("%s has %d chars\n", msg, myStrlen(msg));     // Hello has 5 chars
    return 0;
}
