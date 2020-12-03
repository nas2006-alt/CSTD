#include "vector.h"

void loopF(const double* data, int index, vector* array) {
    printf("Index: %d, Value: %f, which is %f\n", index, get(array, index), *data); // Using index,
    // find(array, *data) wouldn't work because both 400's would show the first 400's position.
}

int main() {
    vector* v = create_vector(5, 100.f, 300.f, 600.f, 700.f, 400.f);
    vector* v2 = create_empty_vector(2);

    set(v2, 0, 100);
    set(v2, 1, 1000);

    join(v, v2); // {100, 300, 600, 700, 400, 100, 1000}

    shift(v); // {300, 600, 700, 400, 100, 1000}

    unshift(v, 900.f); // {900, 300, 600, 700, 400, 100, 1000}

    pop(v); // {900, 300, 600, 700, 400, 100}

    push(v, 400); // {900, 300, 600, 700, 400, 100, 400}

    sort(v, 0, length(v)-1); // {100, 300, 400, 400, 600, 700, 900}

    forEach(v, loopF); // Prints out all of them

    vector* sliced = slice(v, -3, 5); // Will be from arr[4] to arr[5], including arr[4] but excluding arr[5]

    printf("\nSliced:\n");
    forEach(sliced, loopF); // Prints out all sliced(which is just 1 element)

    printf("\n900 is in position: %d", find(v, 900)); // Demonstrates Find
}