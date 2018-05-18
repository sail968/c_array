#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

#include "tests.h"

void print_array_error() {
    switch (arrayErr) {
        case eArray_noError:
            printf("eArray_noError");
            break;
        case eArray_allocationError:
            printf("eArray_allocationError");
            break;
        case eArray_argumentCanNotBeNull:
            printf("eArray_argumentCanNotBeNull");
            break;
        case eArray_invalidData:
            printf("eArray_invalidData");
            break;
        case eArray_invalidSize:
            printf("eArray_invalidSize");
            break;
        case eArray_invalidCapacity:
            printf("eArray_invalidCapacity");
            break;
        case eArray_invalidElementSize:
            printf("eArray_invalidElementSize");
            break;
        case eArray_invalidArgument:
            printf("eArray_invalidArgument");
            break;
        case eArray_internalError:
            printf("eArray_internalError");
            break;
        case eArray_invalidState:
            printf("eArray_invalidState");
            break;
        case eArray_outOfRange:
            printf("eArray_outOfRange");
            break;
        case eArray_notFound:
            printf("eArray_notFound");
            break;
        default:
            assert(false);
            break;

    }
}


void fill_10000(Array *array) {
    for (int i = 0; i < 10000; ++i) {
        int value = i;
        int result = array_push_back(array, &value);

        if (result != 0) {
            print_array_error();
        }
    }
}

void test_push_back() {
    Array array;
    array_construct(sizeof(int), &array);


    int i;
    for (i = 0; i < 10; ++i) {
        int x = i*2;
        int result = array_push_back(&array, &x);

        if (result != 0) {
            print_array_error();
            return;
        }

        assert(array.size == i+1);
    }

    for (i = 0; i < 10; ++i) {
        int* x = (int*)(array.data + i*sizeof(int));
        assert(*x == i*2);
    }

    array_destruct(&array);
}

void test_delete() {
    Array array;
    int success = array_construct(sizeof(int), &array);

    if (success != 0) {
        print_array_error();
        return;
    }

    fill_10000(&array);
    assert(array.size == 10000);

    int initial_size = array.size;
    int deleted_count = 0;

    for (int i = 9999; i >= 0; i -= 2) {
        success = array_delete_element(&array, i);

        if (success == 0) {
            deleted_count++;
        } else {
            print_array_error();
            return;
        }

        assert(array.size == initial_size - deleted_count);

    }

    assert(array.size == initial_size - deleted_count);

    for (int i = 0; i < array.size; ++i) {
        int* value = (int*)array_get_at(&array, i);
        assert(*value == i*2);
    }

    array_destruct(&array);

}

void test_find() {
    Array array;
    array_construct(sizeof(int), &array);

    fill_10000(&array);

    // поиск существующих элементов
    for (int el = 0; el < 10000; ++el) {

        int found = array_find_element(&array, &el);

        int elementRealIndex = el;
        assert(found == elementRealIndex);

        if (found == -1) {
            printf("on element %d : ", el);
            print_array_error();
            printf("\n");
        }
    }

    // поиск несуществующего элемента
    int item = -5;
    int found = array_find_element(&array, &item);

    assert(found == -1);
    assert(arrayErr == eArray_notFound);

    array_destruct(&array);

}

void run_all_tests() {
    test_push_back();
    test_delete();
    test_find();
    printf("all tests passed");
}
