/**
 * Testing functions 
 *
 * All test functions return 1 for failing, and 0 for success
 */

typedef char (*truthy)(const void*, const void*);
typedef char* (*stringify)(const void*);

char test_costume(
    const void* real, 
    const void* expected, 
    const truthy equals, 
    const stringify to_str, 
    const char* message
);

char test_int(const int real, const int expected, const char* message);
char test_char(const char real, const char expected, const char* message);

