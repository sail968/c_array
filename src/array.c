#include <stdbool.h>
#include <memory.h>
#include "array.h"

const size_t INITIAL_CAPACITY = 4;
ArrayError arrayErr = eArray_noError;

#define fail_if(condition, errValue, return_value)                          \
    if (condition) {                                                        \
        arrayErr = errValue;                                                \
        return return_value;                                                \
    }


#define validate_array(array, return_value)                                    \
    fail_if((array) == NULL, eArray_argumentCanNotBeNull, return_value)        \
    fail_if((array)->data == NULL, eArray_invalidData, return_value)           \
    fail_if((array)->size < 0, eArray_invalidSize, return_value)               \
    fail_if((array)->capacity < 0, eArray_invalidCapacity, return_value)       \
    fail_if((array)->elementSize < 0, eArray_invalidElementSize, return_value) \
    fail_if((array)->size > (array)->capacity,                       \
            eArray_invalidState, return_value)       \


int array_construct(int elementSize, Array *array) {
    fail_if(array == NULL, eArray_argumentCanNotBeNull, -1);
    fail_if(elementSize <= 0, eArray_invalidArgument, -1);

    void* data = malloc(INITIAL_CAPACITY*elementSize);
    fail_if(data == NULL, eArray_allocationError, -1);

    int size = 0;
    int capacity = INITIAL_CAPACITY;

    array->size = size;
    array->capacity = capacity;
    array->data = data;
    array->elementSize = elementSize;

    return 0;
}

int array_destruct(Array *array) {
    fail_if(array == NULL, eArray_argumentCanNotBeNull, -1);

    array->size = 0;
    array->capacity = 0;
    free(array->data);
    array->data = NULL;
    array->elementSize = 0;

    return 0;
}

int array_realloc(Array *array, int new_capacity) {
    validate_array(array, -1);
    fail_if(new_capacity < 0, eArray_invalidArgument, -1);

    void* new_data = realloc(array->data, (size_t)new_capacity*array->elementSize);
    fail_if(new_data == NULL, eArray_allocationError, -1);

    array->data = new_data;

    if (array->size > array->capacity) {
        array->size = array->capacity;
    }

    array->capacity = new_capacity;

    return 0;
}

int array_push_back(Array *array, void *item) {
    return array_insert_element(array, array->size, item);
}

void* array_get_at(Array* array, int index) {
    arrayErr = eArray_noError;
    validate_array(array, NULL);
    fail_if(index >= array->size || index < 0, eArray_outOfRange, NULL);

    return array->data + index*array->elementSize;
}

int array_find_element(Array* array, void* item) {
    validate_array(array, -1);
    for (int i = 0; i < array->size; ++i) {
        if (memcmp(item, array->data + i*array->elementSize, array->elementSize) == 0) {
            return i;
        }
    }

    arrayErr = eArray_notFound;
    return -1;
}

int array_delete_element(Array* array, int index) {
    validate_array(array, -1);

    if (index < 0 || index >= array->size) {
        arrayErr = eArray_outOfRange;
        return -1;
    }

    for (int i = index; i < array->size - 1; ++i) {
        void*   dest = array->data + i*array->elementSize;
        void*   source = array->data + (i+1)*array->elementSize;

        memcpy(dest, source, array->elementSize);
    }

    array->size--;

    return 0;
}

int array_insert_element(Array *array, int index, void *item) {
    validate_array(array, -1);

    if (index > array->size) {
        arrayErr = eArray_outOfRange;
        return -1;
    }

    if (array->size == array->capacity) {
        array_realloc(array, array->capacity*2);
    }

    for (int i = array->size; i >= index+1; --i) {
        void* source = array->data + (i-1)*array->elementSize;
        void* dest = array->data + i*array->elementSize;

        memcpy(dest, source, array->elementSize);

    }

    memcpy(array->data + index*array->elementSize, item, array->elementSize);
    array->size++;

    return 0;

}
