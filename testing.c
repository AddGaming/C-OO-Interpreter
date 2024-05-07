/**
* implementation of testing function
*/
#include <stdio.h>
#include "testing.h"

// char
// signed_char
// unsigned_char
// short
// unsigned_short
// int
// unsigned_int
// long
// unsigned_long
// long_long
// unsigned_long_long
// float
// double
// long_double

char test_costume(const void* real, const void* expected, const truthy equals, const stringify to_str, const char* message){
    if (equals(real, expected)) {
        printf("\x1B[32m%s\x1B[0m\n", to_str(expected));
        return 0;
    } else {
        printf("\x1B[31mexpected: %s\nreceived: %s\n%s\x1B[0m\n", to_str(expected), to_str(real), message);
        return 1;
    }  
}

char test_int(const int real, const int expected, const char* message){
    if (real == expected) {
        printf("\x1B[32m%d\x1B[0m\n", real);
        return 0;
    } else {
        printf("\x1B[31mexpected: %d\nreceived: %d\n%s\x1B[0m\n", expected, real, message);
        return 1;
    }  
}

char test_char(const char real, const char expected, const char* message){
    if (real == expected) {
        printf("\x1B[32m%c\x1B[0m\n", real);
        return 0;
    } else {
        printf("\x1B[31mexpected: %d\nreceived: %d\n%s\x1B[0m\n", expected, real, message);
        return 1;
    }  
}
