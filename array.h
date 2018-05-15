#ifndef C_ARRAY_ARRAY_H
#define C_ARRAY_ARRAY_H

#include <stdlib.h>

typedef enum ArrayError {
    eArray_noError,
    eArray_allocationError,
    eArray_argumentCanNotBeNull,
    eArray_invalidData,
    eArray_invalidSize,
    eArray_invalidCapacity,
    eArray_invalidElementSize,
    eArray_invalidArgument,
    eArray_internalError,
    eArray_invalidState
} ArrayError;

extern ArrayError arrayErr;

extern const size_t INITIAL_CAPACITY;

typedef struct Array {
    int elementSize;
    int size;
    int capacity;

    void* data;
} Array;


int array_construct(int elementSize, Array *array);

int array_destruct(Array* array);

int array_realloc(Array* array, int new_capacity);

int array_insert(Array* array, void* element);

#endif //C_ARRAY_ARRAY_H
