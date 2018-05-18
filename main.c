#include <assert.h>
#include <stdio.h>
#include "array.h"

void test_insert() {
    Array array;
    array_construct(sizeof(int), &array);


    int i;
    for (i = 0; i < 10; ++i) {
        int x = i*2;
        int result = array_push_back(&array, &x);
        assert(result == 0);
    }

    for (i = 0; i < 10; ++i) {
        int* x = (int*)(array.data + i*sizeof(int));
        assert(*x == i*2);
    }
}

int main() {
    Array array;
    int result = array_construct(sizeof(int), &array);

    assert(array.size == 0);
    assert(array.capacity == 4);

    array_realloc(&array, 10);
    assert(array.capacity == 10);


    if (result != -1) {
        array_destruct(&array);
    }

    test_insert();

    return 0;
}