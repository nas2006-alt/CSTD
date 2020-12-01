#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stdarg.h>
#include <malloc.h>
#include <math.h>
#include <stdint.h>

int nullHolder = 0;

typedef struct {
    double* data;
    int array_capacity;
    int top;
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
    v->top = (int)size;
    va_end(list);
    return v;
}

vector* create_empty_vector(int size) {
    vector* v = malloc(sizeof(vector));
    v->top = 0;
    v->array_capacity = size;
    v->data = malloc(size * sizeof(double));
    return v;
}

int full(vector* v) {
    return v->top == v->array_capacity;
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
    v->data[++v->top] = element;
    return v->top;
}

double pop(vector* v) {
    if (empty(v)) {
        fprintf(stderr, "Vector is empty!");
        return 0;
    }
    double toReturn = v->data[v->top];
    v->data[v->top] = 0;
    v->top--;
    v->array_capacity--;
    if (v->array_capacity == 0) {
        v->data = malloc(0);
        return toReturn;
    }
    v->data = reallocarray(v->data, v->array_capacity, sizeof(double));

    return toReturn;
}

double get(vector* v, int index) {
    return v->data[index];
}

void set(vector* v, int index, double new_value) {
    if (empty(v)) {
        fprintf(stderr, "Vector is empty!");
        return;
    }
    if (v->top < index) {
        fprintf(stderr, "Index too large!");
        return;
    }
    if (v->top < 0) {
        fprintf(stderr, "Index too small!");
        return;
    }
    if (v->top == index) {
        v->top++;
    }

    v->data[index] = new_value;
}

void forEach(vector* v, loopFunction function) {
    for (int i = 0; i < v->top; i++) {
        function(&(v->data[i]), i, v);
    }
}

int length(vector* v) {
    return (v->top);
}

double shift(vector* v) {
    double first = *v->data;
    v->data++;
    v->top--;

    return first;
}

void unshift(vector* v, double new_elem) {
    vector* newV = create_empty_vector(v->top + 1);
    set(newV, 0, new_elem);
    for (int i = 1; i < v->top + 1; i++) {
        set(newV, i, v->data[i - 1]);
    }

    *v = *newV;

}

vector* slice(vector* original, int start, int end) {

    int s = start;
    int e = end;

    if (s < 0) {
        s = length(original) + s;
    }
    if (e < 0) {
        e = length(original) + e;
    }

    vector* newV = create_empty_vector(e - s);

    for (int i = s; i < e; i++) {
        set(newV, i - s, get(original, i));
    }

    return newV;
}

#endif //VECTOR_VECTOR_H
