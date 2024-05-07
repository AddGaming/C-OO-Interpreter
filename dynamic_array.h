/**
 * array operations which take care of resizing
 */
#include <stddef.h>

#ifndef TYPE_CONCATS
#define TYPE_CONCATS
typedef signed char signed_char;
typedef unsigned char unsigned_char;
typedef unsigned short unsigned_short;
typedef unsigned int unsigned_int;
typedef unsigned long unsigned_long;
typedef long long long_long;
typedef unsigned long long unsigned_long_long;
typedef long double long_double;
#endif

#ifndef DEFAULT_TYPES
#define DEFAULT_TYPES(macro) \
    macro(char) \
    macro(signed_char) \
    macro(unsigned_char) \
    macro(short) \
    macro(unsigned_short) \
    macro(int) \
    macro(unsigned_int) \
    macro(long) \
    macro(unsigned_long) \
    macro(long_long) \
    macro(unsigned_long_long) \
    macro(float) \
    macro(double) \
    macro(long_double)

#define DEFINE_WP(type) \
    typedef struct { \
        size_t capacity; \
        unsigned int size; \
        size_t count; \
        type* ptr; \
    } type##Wp; \
    type##Wp insert_##type(type##Wp arr, type elem); 

DEFAULT_TYPES(DEFINE_WP);

#define new_wp(name, type, capacity) \
    type##Wp name = {capacity, sizeof(type), 0, calloc(capacity, sizeof(type))}; \

#endif