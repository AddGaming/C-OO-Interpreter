/**
 * array operations which take care of resizing
 */
#include <stddef.h>
#include "result.h"
#include "default_types.h"

#ifndef DEFINE_WP
#define DEFINE_WP(type) \
    typedef struct { \
        size_t capacity; \
        unsigned int size; \
        size_t count; \
        type* ptr; \
    } type##Wp; \
    DEFINE_RESULT(type##Wp); \
    type##WpRes insert_##type(type##Wp arr, type elem); 

DEFAULT_TYPES(DEFINE_WP);

#define new_wp(name, type, capacity) \
    type##Wp name = {capacity, sizeof(type), 0, calloc(capacity, sizeof(type))}; \

#endif



