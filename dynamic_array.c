#include "dynamic_array.h"
#include "color_print.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define DEFINE_INSERT(type) \
    type##Wp insert_##type(type##Wp arr, type elem) { \
        if (arr.count == arr.capacity) { \
            if (arr.capacity == SIZE_MAX) {print_redln("Tried to inser into max size and full array!"); exit(1);} \
            type* prev = arr.ptr; \
            size_t new_cap = arr.capacity * 2; \
            if (new_cap < arr.capacity) new_cap = SIZE_MAX; \
            type* new_ptr = calloc(new_cap, sizeof(type)); \
            memcpy(prev, new_ptr, arr.capacity * sizeof(type)); \
            free(prev); \
            arr.ptr = new_ptr; \
        } \
        arr.ptr[arr.count] = elem; \
        arr.count++; \
        return arr; \
    }

DEFAULT_TYPES(DEFINE_INSERT);


