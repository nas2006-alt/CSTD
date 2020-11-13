#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stdarg.h>
#include <malloc.h>
#include <math.h>

typedef struct {
    char** data;
    int array_capacity;
    int top;
} vector;

vector create_vector(size_t size, char* initial, ...) {
    vector v;
    va_list list;
    va_start(list, size);
    v.top = 0;
    v.array_capacity = size;
    v.data = malloc(sizeof(char*) * size);
    v.data[0] = initial;
    for (int i = 1; i < size; i++) {
        v.data[i] = va_arg(list, char*);
        v.top++;
    }
    va_end(list);
    return v;
}

vector create_empty_vector(size_t size) {
    vector v;
    v.top = 0;
    v.array_capacity = size;
    v.data = malloc(size * sizeof(char*));
    return v;
}

int full(vector v) {
    return v.top == v.array_capacity;
}

int empty(vector v) {
    return v.array_capacity == 0;
}

int push(vector v, char* element) {
    if (full(v)) {
        int new_cap = floor(pow(v.array_capacity, 1.5)) + 1;
        v.data = reallocarray(v.data, new_cap, sizeof(char*));
        v.array_capacity = new_cap;
    }
    v.data[++v.top] = element;
    return v.top;
}

char* pop(vector v) {
    if (empty(v)) {
        fprintf(stderr, "Vector is empty!");
        return "";
    }
    char* toReturn = v.data[v.top];
    v.data[v.top] = NULL;
    v.top--;
    v.array_capacity--;
    if (v.array_capacity == 0) {
        v.data = malloc(0);
        return toReturn;
    }
    v.data = reallocarray(v.data, v.array_capacity, sizeof(char*));

    return toReturn;
}

char* get(vector v, int index) {
    return v.data[index];
}

void set(vector v, int index, char* new_value) {
    if (empty(v)) {
        fprintf(stderr, "Vector is empty!");
        return;
    }
    if (v.top < index) {
        fprintf(stderr, "Index too large!");
        return;
    }
    if (v.top < 0) {
        fprintf(stderr, "Index too small!");
        return;
    }

    v.data[index] = new_value;
}

#endif //VECTOR_VECTOR_H
