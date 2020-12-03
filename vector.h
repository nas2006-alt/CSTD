#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stdarg.h>
#include <malloc.h>
#include <math.h>
#include <stdint.h>

typedef struct {
    double* data;
    int array_capacity;
    int highest_set;
} vector;

typedef void(*loopFunction)(const double* item, int index, vector* arr);

vector* create_vector(double size, ...) {
    vector* v = malloc(sizeof(vector));
    va_list list;
    va_start(list, (int)size);
    v->array_capacity = (int)size;
    v->data = (double*)malloc(sizeof(double) * size);
    for (int i = 0; i < size; i++) {
        double d = va_arg(list, double);
        v->data[i] = d;
    }
    v->highest_set = (int)size - 1;
    va_end(list);
    return v;
}

vector* create_empty_vector(int size) {
    vector* v = malloc(sizeof(vector));
    v->highest_set = 0;
    v->array_capacity = size;
    v->data = malloc(size * sizeof(double));
    return v;
}

int full(vector* v) {
    return v->highest_set + 1 == v->array_capacity;
}

int empty(vector* v) {
    return v->array_capacity == 0;
}

int push(vector* v, double element) {
    if (full(v)) {
        int new_cap = (int)floor(pow(v->array_capacity, 1.5)) + 1;
        v->data = reallocarray(v->data, new_cap, sizeof(double));
        v->array_capacity = new_cap;
    }
    v->data[++v->highest_set] = element;
    return v->highest_set + 1;
}

double pop(vector* v) {
    if (empty(v)) {
        fprintf(stderr, "Vector is empty!");
        return 0;
    }
    double toReturn = v->data[v->highest_set];
    v->data[v->highest_set] = 0;
    v->highest_set--;
    v->array_capacity--;
    if (v->array_capacity == 0) {
        v->data = malloc(0);
        return toReturn;
    }
    v->data = (double*)realloc(v->data, v->array_capacity * sizeof(double));

    return toReturn;
}

double get(vector* v, int index) {
    return v->data[index];
}

void set(vector* v, int index, double new_value) {

    int i = index;

    if (index < 0) {
        i += v->highest_set;
    }

    if (empty(v)) {
        fprintf(stderr, "Vector is empty!");
        return;
    }
    if (v->highest_set < index) {
        fprintf(stderr, "Index too large!");
        return;
    }
    if (i < 0) {
        fprintf(stderr, "Index too small!");
        return;
    }
    if (v->highest_set == index) {
        v->highest_set++;
    }

    v->data[index] = new_value;
}

void forEach(vector* v, loopFunction function) {
    for (int i = 0; i < v->highest_set; i++) {
        function(&(v->data[i]), i, v);
    }
}

int length(vector* v) {
    return (v->highest_set + 1);
}

double shift(vector* v) {
    double first = *v->data;
    v->data++;
    v->highest_set--;

    return first;
}

void unshift(vector* v, double new_elem) {
    vector* newV = create_empty_vector(length(v) + 1);
    set(newV, 0, new_elem);
    for (int i = 1; i < v->highest_set + 1; i++) {
        set(newV, i, v->data[i - 1]);
    }

    *v = *newV;

}

vector* slice(vector* original, int start, int end) {

    int s = start;
    int e = end;

    if (s < 0) {
        s = length(original) - 1 + s;
    }
    if (e < 0) {
        e = length(original) - 1 + e;
    }

    vector* newV = create_empty_vector(e - s);

    for (int i = s; i < e; i++) {
        set(newV, i - s, get(original, i));
    }

    return newV;
}

void swap(vector* v, int pos1, int pos2) {
    double temp = v->data[pos1];
    v->data[pos1] = v->data[pos2];
    v->data[pos2] = temp;
}

void sort(vector* v, int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        double pivot = v->data[high];    // pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j <= high; j++)
        {
            // If current element is smaller than the pivot
            if (v->data[j] < pivot) {
                i++;    // increment index of smaller element
                swap(v, i, j);
            }
        }
        swap(v, i + 1, high);
        int pi = i + 1;

        // Separately sort elements before
        // partition and after partition
        sort(v, low, pi - 1);
        sort(v, pi + 1, high);
    }
}

vector* copy(vector* v) {
    vector* newV = malloc(sizeof(vector));
    newV->highest_set = v->highest_set;
    newV->array_capacity = v->array_capacity;

    newV->data = malloc(v->array_capacity * sizeof(double));
    for (int i = 0; i <= v->highest_set; i++) {
        newV->data[i] = v->data[i];
    }

    return newV;
}

int binarySearch(vector* v, int begin, int end, double element, int newSort) {

    vector* sorted;
    if (newSort) {
        sorted = copy(v);
        sort(sorted, 0, length(sorted) - 1);
    } else {
        sorted = v;
    }

    if (end >= begin) {
        int mid = begin + (end - begin) / 2;

        //printf("Sorted Data %d:%f\n", mid, sorted->data[mid]);

        // Return mid if element in mid
        if (sorted->data[mid] == element) {
            free(sorted);
            return mid;
        }

        // If smaller than mid, its left of mid
        if (sorted->data[mid] > element)
            return binarySearch(sorted, begin, mid - 1, element, 0);

        // If bigger than mid, its right of mid
        return binarySearch(sorted, mid + 1, end, element, 0);
    }

    // Returns -1 on failure
    return -1;
}

int find(vector* v, double item) {
    return binarySearch(v, 0, length(v), item, 1);
}

void join(vector* original, vector* added) {
    for (int i = 0; i < length(added); i++) {
        push(original, get(added, i));
    }
}

#endif //VECTOR_VECTOR_H
