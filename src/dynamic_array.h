/**
 * array operations which take care of resizing
 * typedef struct { 
 *     size_t capacity;
 *     unsigned int size; 
 *     size_t count; 
 *     type* ptr; 
 *  } type##Wp; 
 *
 *  also defines corresponding result type
 *
 *  insert(wp, elem) -> res
 *  in case of inserting into a max full wp,
 *  does nothing and returns wp.
 */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "result.h"
#include "default_types.h"
#include "color_print.h"

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

#define DEFINE_INSERT(type) \
    type##WpRes insert_##type(type##Wp arr, type elem) { \
        size_t MAX = SIZE_MAX / arr.size; \
        type##WpRes ans = {FAILURE, arr}; \
        if (arr.count == arr.capacity) { \
            if (arr.capacity == MAX) { \
                err_redln("Tried to inser into max size and full array!"); \
                return ans; \
            } \
            type* prev = arr.ptr; \
            size_t new_cap = arr.capacity * 2; \
            if (new_cap < arr.capacity) new_cap = MAX; \
            type* new_ptr = calloc(new_cap, sizeof(type)); \
            memcpy(new_ptr, prev, arr.capacity * sizeof(type)); \
            free(prev); \
            arr.ptr = new_ptr; \
            arr.capacity = new_cap; \
        } \
        arr.ptr[arr.count] = elem; \
        arr.count++; \
        type##WpRes ans2 = {SUCCESS, arr}; \
        return ans2; \
    }


#endif



