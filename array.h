#ifndef C_ARRAY_ARRAY_H
#define C_ARRAY_ARRAY_H

#include <stdlib.h>

typedef enum ArrayError {
    eArray_noError = 0,
    eArray_mallocError,
    eArray_argumentCanNotBeNull,
} ArrayError;

extern ArrayError arrayErr;

extern const size_t INITIAL_CAPACITY;

typedef struct Array {
    size_t elementSize;
    size_t size;
    size_t capacity;

    void* data;
} Array;


int construct_array(size_t elementSize, Array* array );

int destruct_array(Array* array);

#endif //C_ARRAY_ARRAY_H
