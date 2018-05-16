#include <stdbool.h>
#include <assert.h>
#include <memory.h>
#include "array.h"

const size_t INITIAL_CAPACITY = 4;
ArrayError arrayErr = eArray_noError;

#define fail_if(condition, errValue, do_return)                             \
    if (condition) {                                                        \
        arrayErr = errValue;                                                \
        if ((do_return))                                                    \
            return -1;                                                      \
    }


#define fail_return(c, e) fail_if(c, e, true)


#define validate_array(array, do_return)                                    \
    fail_if((array) == NULL, eArray_argumentCanNotBeNull, do_return)        \
    fail_if((array)->data == NULL, eArray_invalidData, do_return)           \
    fail_if((array)->size < 0, eArray_invalidSize, do_return)               \
    fail_if((array)->capacity < 0, eArray_invalidCapacity, do_return)       \
    fail_if((array)->elementSize < 0, eArray_invalidElementSize, do_return) \
    fail_if((array)->elementSize > (array)->capacity,                       \
            eArray_invalidState, do_return)       \


int array_construct(int elementSize, Array *array) {
    fail_if(array == NULL, eArray_allocationError, true);
    fail_return(elementSize <= 0, eArray_invalidArgument);

    void* data = malloc(INITIAL_CAPACITY*elementSize);
    fail_if(data == NULL, eArray_argumentCanNotBeNull, true);

    int size = 0;
    int capacity = INITIAL_CAPACITY;

    array->size = size;
    array->capacity = capacity;
    array->data = data;
    array->elementSize = elementSize;

    return 0;
}

int array_destruct(Array *array) {
    fail_if(array == NULL, eArray_argumentCanNotBeNull, true);

    array->size = 0;
    array->capacity = 0;
    free(array->data);
    array->data = NULL;
    array->elementSize = 0;

    return 0;
}

int array_realloc(Array *array, int new_capacity) {
    validate_array(array, true);
    fail_return(new_capacity < 0, eArray_invalidArgument);

    void* new_data = realloc(array->data, (size_t)new_capacity*array->elementSize);
    fail_if(new_data == NULL, eArray_allocationError, true);

    array->capacity = new_capacity;

    return 0;
}

int array_insert(Array* array, void *element) {
    validate_array(array, true);

    assert(array->size <= array->capacity);

    if (array->size == array->capacity) {
        array_realloc(array, array->capacity*2);
    }

    memcpy(array->data + (array->elementSize*array->size),
           element,
           (size_t)array->elementSize);

    array->size++;

    return 0;
}

void* array_get_at(Array* array, int index) {
    validate_array(array, true);
    fail_return(index >= array->size || index < 0, eArray_outOfRange);

    return array->data + index*array->elementSize;
}


