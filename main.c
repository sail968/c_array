#include <assert.h>
#include "array.h"

int main() {
    Array array;
    int result = construct_array(sizeof(int), &array);

    if (result != -1) {
        destruct_array(&array);
    }
    return 0;
}