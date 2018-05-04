#include "array.h"

const size_t INITIAL_CAPACITY = 4;
ArrayError arrayErr = eArray_noError;

#define fail_if(condition, errValue)\
    if (condition) {                        \
        arrayErr = errValue;                \
        return -1;                          \
    }

int construct_array(size_t elementSize, Array* array) {
    fail_if(array == NULL, eArray_mallocError);

    void* data = malloc(INITIAL_CAPACITY*elementSize);
    fail_if(data == NULL, eArray_argumentCanNotBeNull);

    size_t size = 0;
    size_t capacity = INITIAL_CAPACITY;

    array->size = size;
    array->capacity = capacity;
    array->data = data;
    array->elementSize = elementSize;

    return 0;
}

int destruct_array(Array* array) {
    fail_if(array == NULL, eArray_argumentCanNotBeNull);

    array->size = 0;
    array->capacity = 0;
    free(array->data);
    array->data = NULL;
    array->elementSize = 0;

    return 0;
}
